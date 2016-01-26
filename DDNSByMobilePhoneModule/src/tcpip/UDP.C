//-----------------------------------------------------------------------------
// Copyright (c) 2002 Jim Brady
// Do not use commercially without author's permission
// Last revised August 2002
// Net UDP.C
//
// This module handles UDP messages
// Refer to RFC 768, 1122
// Also RFC 862 echo, RFC 867 daytime, and RFC 868 time
//-----------------------------------------------------------------------------
#include <string.h>
#include <stdlib.h>
#include "ip.h"
#include "cksum.h"
#include "icmp.h"
#include "udp.h"

extern unsigned char  debug;
extern unsigned long  my_ipaddr;
       unsigned int   sender_udpport;
static unsigned long  sender_ipaddr;
extern char text[];


//------------------------------------------------------------------------
//	UDP Echo service - see RFC 862
// This simply echos what it received back to the sender
//------------------------------------------------------------------------
void udp_echo_service(unsigned char * inbuf, unsigned int len)
{
   if (debug)
   {
      serial_send("ECHO: Nr chars = ");
      memset(text, 0, 10);
      itoa(len, text, 10);
      serial_send(text);
	  serial_send("\r");
   }
	udp_send(inbuf, ECHO_PORT, len);      
}



//------------------------------------------------------------------------
//	This handles outgoing UDP messages
// See "TCP/IP Illustrated, Volume 1" Sect 11.1 - 11.3
//------------------------------------------------------------------------
void udp_send(unsigned char * inbuf, unsigned int port, unsigned int len)
{
	unsigned long sum;
  	unsigned int  result;
  	unsigned char * outbuf;
  	UDP_HEADER    * udp;
    IP_HEADER     * ip;
   	
   // Allocate memory for entire outgoing message including
   // eth & IP headers. Total ethernet message length is:
   // 14 byte eth header + 20 byte IP header + 8 byte UDP header
   // + length of this data 
   outbuf = (unsigned char  *)malloc(42 + len);
   if (outbuf == NULL)
   {
      if (debug) serial_send("UDP: Oops, out of memory\r");
      return;
   }
   
   udp = (UDP_HEADER  *)(outbuf + 34);
   ip = (IP_HEADER  *)(outbuf + 14);
   
   // Direct message back to the senders port. 
	udp->dest_port = sender_udpport;
	udp->source_port = port;
	udp->length = 8 + len;
	udp->checksum = 0;
		
	// Fill in data
   // Important do not free receive buffer prior to this
   memcpy(&udp->msg_data, (inbuf + 42), len); 
	
	
	// Compute checksum including 12 bytes of pseudoheader
	// Must pre-fill 2 items in outbuf to do this
	// Direct message back to senders ip address
	ip->dest_ipaddr = sender_ipaddr;
	ip->source_ipaddr = my_ipaddr;
	 
	
	// Sum source_ipaddr, dest_ipaddr, and entire UDP message 
	sum = (unsigned long)cksum(outbuf + 26, 8 + udp->length);
			
	// Add in the rest of pseudoheader which is
	// zero, protocol id, and UDP length
	sum += (unsigned long)0x0011;
	sum += (unsigned long)udp->length;

	// In case there was a carry, add it back around
	result = (unsigned int)(sum + (sum >> 16));
	udp->checksum = ~result;
    if (debug) serial_send("UDP: Sending msg to IP layer\r");
	ip_send(outbuf, sender_ipaddr, UDP_TYPE, udp->length);
}



//------------------------------------------------------------------------
// This handles incoming UDP messages
// See "TCP/IP Illustrated, Volume 1" Sect 11.1 - 11.3
//------------------------------------------------------------------------
void udp_rcve(unsigned char * inbuf, unsigned int len)
{
   unsigned int result;
   UDP_HEADER  * udp;
   IP_HEADER   * ip;
   unsigned long sum;
      
	// Total of eth & IP headers = 34 bytes      
   udp = (UDP_HEADER *)(inbuf + 34);
   ip = (IP_HEADER *)(inbuf + 14);
			
	// The IP length "len" should be the same as the redundant length
	// udp->length.  TCP/IP Illustrated, Vol 2, Sect 23.7 says to use the
	// UDP length, unless IP length < UDP length, in which case the frame
	// should be discarded.
   if (len < udp->length) return;
		   
	// If the checksum is zero it means that the sender did not compute
	// it and we should not try to check it.
	if (udp->checksum == 0)
	{
		if (debug) serial_send("UDP: Sender did not compute cksum\r");
	}
	else
	{
		// Compute UDP checksum including 12 byte pseudoheader
		// Sum source_ipaddr, dest_ipaddr, and entire UDP message 
		sum = (ULONG)cksum(inbuf + 26, 8 + udp->length);
		
		// Add in the rest of pseudoheader which is
		// zero, protocol id, and UDP length
		sum += (unsigned long)0x0011;     
		sum += (unsigned long)udp->length;

		// In case there was a carry, add it back around
		result = (unsigned int)(sum + (sum >> 16));
		
		if (result != 0xFFFF)
		{
	  		if (debug) serial_send("UDP: Error, bad cksum\r");
			return;
		}
	
		if (debug) serial_send("UDP: Msg rcvd with good cksum\r");
	}
		
	// Capture sender's port number and ip_addr
	// to send return message to
	sender_udpport = udp->source_port;
   sender_ipaddr = ip->source_ipaddr;
				      
	// See if any applications are on any ports
	switch (udp->dest_port)
	{
		case ECHO_PORT:
		// Pass it the payload length
		udp_echo_service(inbuf, udp->length - 8);
		break;

		default:
		// If no application is registered to handle incoming
		// UDP message then send ICMP destination unreachable
		dest_unreach_send(inbuf, ip->source_ipaddr);
		break;
	}
}

