/**
 * \addtogroup apps
 * @{
 */

/**
 * \defgroup webclient Web client
 * @{
 *
 * This example shows a HTTP client that is able to download web pages
 * and files from web servers. It requires a number of callback
 * functions to be implemented by the module that utilizes the code:
 * webclient_datahandler(), webclient_connected(),
 * webclient_timedout(), webclient_aborted(), webclient_closed().
 */

/**
 * \file
 * Implementation of the HTTP client.
 * \author Adam Dunkels <adam@dunkels.com>
 */

/*
 * Copyright (c) 2002, Adam Dunkels.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above
 *    copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided
 *    with the distribution.
 * 3. The name of the author may not be used to endorse or promote
 *    products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * This file is part of the uIP TCP/IP stack.
 *
 * $Id: webclient.c,v 1.2 2006/06/11 21:46:37 adam Exp $
 *
 */

#include "uip.h"
#include "uiplib.h"
#include "webclient.h"
#include "..\resolv\resolv.h"

#include <string.h>


#define ISO_nl       0x0a
#define ISO_cr       0x0d
#define ISO_space    0x20

static struct webclient_state WebLnkS;

/*-----------------------------------------------------------------------------------*/
// by david 
extern char *itoa(int value, char *string, int radix);
extern void debug_info_show(char *info, u16_t len) ;

/*-----------------------------------------------------------------------------------*/
char *
webclient_mimetype(void)
{
  return WebLnkS.mimetype;
}
/*-----------------------------------------------------------------------------------*/
char *
webclient_filename(void)
{
  return WebLnkS.file;
}
/*-----------------------------------------------------------------------------------*/
char *
webclient_hostname(void)
{
  return WebLnkS.host;
}
/*-----------------------------------------------------------------------------------*/
unsigned short
webclient_rport(void)
{
  return WebLnkS.rport;
}

unsigned short
webclient_lport(void)
{
  return WebLnkS.lport;
}
/*-----------------------------------------------------------------------------------*/
void
webclient_init(void)
{
	//init_connection();
//	if(webclientconn != NULL )	{

//	}

}
/*-----------------------------------------------------------------------------------*/
static void	init_connection(void)
{
  WebLnkS.state = WEBCLIENT_STATE_STATUSLINE;
  

  WebLnkS.getrequestleft = sizeof(http_get) - 1 +
    strlen(WebLnkS.file) + 1 +
    sizeof(http_11) - 1 +
    sizeof(http_crnl) - 1 +
    sizeof(http_host) - 1 +
	strlen(WebLnkS.host)        +
    sizeof(http_crnl) - 1 +
    sizeof(http_crnl) - 1 ;
//    strlen(http_user_agent_fields);
  	
  WebLnkS.getrequestptr = 0;

  WebLnkS.httpheaderlineptr = 0;
}
/*-----------------------------------------------------------------------------------*/
void
webclient_close(void)
{
  WebLnkS.state = WEBCLIENT_STATE_CLOSE;
}
/*-----------------------------------------------------------------------------------*/
unsigned char
webclient_get(char *host, u16_t rport, char *file)
{
  //---by david
  struct uip_conn *conn;
  
  uip_ipaddr_t *ipaddr;
  static uip_ipaddr_t addr;

  /* First check if the host is an IP addresWebLnkS. */
  ipaddr = &addr;
  if(uiplib_ipaddrconv(host, (unsigned char *)addr) == 0) {
    ipaddr = (uip_ipaddr_t *)resolv_lookup(host);
    
    if(ipaddr == NULL) {
      return 0;
    }
  }
  conn = uip_connect(ipaddr, htons(rport));
  
  if(conn == NULL) {
	 //------------------------
		char info[70];
		char  CErrInfo[] = " cannot be connect.\r\n";
		u8_t	len  = 0;

		IpU16ToStr(ipaddr, info);
		len = strlen(info);

		memcpy(info + len, CErrInfo , strlen(CErrInfo));
		len += strlen(CErrInfo);
		info[len ] ='\0';

		debug_info_show(info,len);
  	//-------------------------
    	return 0;
  }
  else {
	char info[70];
	char  COkInfo[] = " is connecting..\r\n";
	u8_t	len  = 0;

	lport2ripStr(htons(conn->lport) , conn->ripaddr, htons(conn->rport), info);
	len = strlen(info);

	memcpy(info + len, COkInfo , strlen(COkInfo));
	len += strlen(COkInfo);
	info[len ] ='\0';

	debug_info_show(info,len);
  }	  

  WebLnkS.rport = rport;
  WebLnkS.lport = conn->lport;

  strncpy(WebLnkS.file, file, sizeof(WebLnkS.file));
  strncpy(WebLnkS.host, host, sizeof(WebLnkS.host));
    
  init_connection();

  return 1;
}
/*-----------------------------------------------------------------------------------*/
static unsigned char *copy_string(unsigned char *dest,
	    const unsigned char *src, unsigned char len)
{
  strncpy((char*)dest, (char*)src, len);
  return dest + len;
}
/*-----------------------------------------------------------------------------------*/
static void
senddata(void)
{
  u16_t len;
  unsigned char *getrequest;
  unsigned char *cptr;
  
  if(WebLnkS.getrequestleft > 0) {
    cptr = getrequest = (unsigned char *)uip_appdata;

    cptr = copy_string((unsigned char*)cptr, (const unsigned char *)http_get, sizeof(http_get) - 1);
    cptr = copy_string((unsigned char*)cptr, (const unsigned char *)WebLnkS.file, strlen(WebLnkS.file));
    *cptr++ = ISO_space;

    cptr = copy_string((unsigned char*)cptr, (const unsigned char *)http_11, sizeof(http_11) - 1);

    cptr = copy_string((unsigned char*)cptr, (const unsigned char *)http_crnl, sizeof(http_crnl) - 1);
    
    cptr = copy_string((unsigned char*)cptr, (const unsigned char *)http_host, sizeof(http_host) - 1);
    cptr = copy_string((unsigned char*)cptr, (const unsigned char *)WebLnkS.host, strlen(WebLnkS.host));
    cptr = copy_string((unsigned char*)cptr, (const unsigned char *)http_crnl, sizeof(http_crnl) - 1);
    cptr = copy_string((unsigned char*)cptr, (const unsigned char *)http_crnl, sizeof(http_crnl) - 1);

	/*
    cptr = copy_string((unsigned char*)cptr, (const unsigned char *)http_user_agent_fields,
		       strlen(http_user_agent_fields));
    */

    *cptr = '\0';
	
    len = WebLnkS.getrequestleft > uip_mss()?	uip_mss(): WebLnkS.getrequestleft;

	//--------------------------
	// by david 
	//len = strlen(request_frame_web1);
	//debug_info_show(request_frame_web1,len);
	//len = strlen(request_frame_web2);
	//debug_info_show(request_frame_web2,len);
	
	//-----------------------------
	debug_info_show((char*)getrequest,strlen(getrequest));
	//--------------------------

    //uip_send(&(getrequest[WebLnkS.getrequestptr]), len);
    uip_send((char*)getrequest,strlen(getrequest));
  }
}
/*-----------------------------------------------------------------------------------*/
static void
acked(void)
{
  u16_t len;
  
  if(WebLnkS.getrequestleft > 0) {
    len = WebLnkS.getrequestleft > uip_mss()?
      uip_mss():
      WebLnkS.getrequestleft;
    WebLnkS.getrequestleft -= len;
    WebLnkS.getrequestptr += len;
  }
}
/*-----------------------------------------------------------------------------------*/
static u16_t
parse_statusline(u16_t len)
{
  char *cptr;
  
  while(len > 0 && WebLnkS.httpheaderlineptr < sizeof(WebLnkS.httpheaderline)) {
    WebLnkS.httpheaderline[WebLnkS.httpheaderlineptr] = *(char *)uip_appdata;
    ++((char *)uip_appdata);
    --len;
    if(WebLnkS.httpheaderline[WebLnkS.httpheaderlineptr] == ISO_nl) {

      if((strncmp(WebLnkS.httpheaderline, http_11,
		  sizeof(http_11) - 1) == 0) ||
	 (strncmp(WebLnkS.httpheaderline, http_11,
		  sizeof(http_11) - 1) == 0)) {
	cptr = &(WebLnkS.httpheaderline[9]);
	WebLnkS.httpflag = HTTPFLAG_NONE;
	if(strncmp(cptr, http_200, sizeof(http_200) - 1) == 0) {
	  /* 200 OK */
	  WebLnkS.httpflag = HTTPFLAG_OK;
	} else if(strncmp(cptr, http_301, sizeof(http_301) - 1) == 0 ||
		  strncmp(cptr, http_302, sizeof(http_302) - 1) == 0) {
	  /* 301 Moved permanently or 302 Found. Location: header line
	     will contain thw new location. */
	  WebLnkS.httpflag = HTTPFLAG_MOVED;
	} else {
	  WebLnkS.httpheaderline[WebLnkS.httpheaderlineptr - 1] = 0;
	}
      } else {
	uip_abort();
	webclient_aborted();
	return 0;
      }
      
      /* We're done parsing the status line, so we reset the pointer
	 and start parsing the HTTP headers.*/
      WebLnkS.httpheaderlineptr = 0;
      WebLnkS.state = WEBCLIENT_STATE_HEADERS;
      break;
    } else {
      ++WebLnkS.httpheaderlineptr;
    }
  }
  return len;
}
/*-----------------------------------------------------------------------------------*/
static char
casecmp(char *str1, const char *str2, char len)
{
  static char c;
  
  while(len > 0) {
    c = *str1;
    /* Force lower-case characters. */
    if(c & 0x40) {
      c |= 0x20;
    }
    if(*str2 != c) {
      return 1;
    }
    ++str1;
    ++str2;
    --len;
  }
  return 0;
}
/*-----------------------------------------------------------------------------------*/
static u16_t
parse_headers(u16_t len)
{
  char *cptr;
  static unsigned char i;
  
  while(len > 0 && WebLnkS.httpheaderlineptr < sizeof(WebLnkS.httpheaderline)) {
    WebLnkS.httpheaderline[WebLnkS.httpheaderlineptr] = *(char *)uip_appdata;
    ++((char *)uip_appdata);
    --len;
    if(WebLnkS.httpheaderline[WebLnkS.httpheaderlineptr] == ISO_nl) {
      /* We have an entire HTTP header line in WebLnkS.httpheaderline, so
	 we parse it. */
      if(WebLnkS.httpheaderline[0] == ISO_cr) {
	/* This was the last header line (i.e., and empty "\r\n"), so
	   we are done with the headers and proceed with the actual
	   data. */
	WebLnkS.state = WEBCLIENT_STATE_DATA;
	return len;
      }

      WebLnkS.httpheaderline[WebLnkS.httpheaderlineptr - 1] = 0;
      /* Check for specific HTTP header fields. */
      if(casecmp(WebLnkS.httpheaderline, http_content_type,
		     sizeof(http_content_type) - 1) == 0) {
	/* Found Content-type field. */
	cptr = strchr(WebLnkS.httpheaderline, ';');
	if(cptr != NULL) {
	  *cptr = 0;
	}
	strncpy(WebLnkS.mimetype, WebLnkS.httpheaderline +
		sizeof(http_content_type) - 1, sizeof(WebLnkS.mimetype));
      } else if(casecmp(WebLnkS.httpheaderline, http_location,
			    sizeof(http_location) - 1) == 0) {
	cptr = WebLnkS.httpheaderline +
	  sizeof(http_location) - 1;
	
	if(strncmp(cptr, http_http, 7) == 0) {
	  cptr += 7;
	  for(i = 0; i < WebLnkS.httpheaderlineptr - 7; ++i) {
	    if(*cptr == 0 ||
	       *cptr == '/' ||
	       *cptr == ' ' ||
	       *cptr == ':') {
	      WebLnkS.host[i] = 0;
	      break;
	    }
	    WebLnkS.host[i] = *cptr;
	    ++cptr;
	  }
	}
	strncpy(WebLnkS.file, cptr, sizeof(WebLnkS.file));
	/*	WebLnkS.file[WebLnkS.httpheaderlineptr - i] = 0;*/
      }


      /* We're done parsing, so we reset the pointer and start the
	 next line. */
      WebLnkS.httpheaderlineptr = 0;
    } else {
      ++WebLnkS.httpheaderlineptr;
    }
  }
  return len;
}
/*-----------------------------------------------------------------------------------*/
static void
newdata_WClt(void)
{
  u16_t len;

  len = uip_datalen();

  if(WebLnkS.state == WEBCLIENT_STATE_STATUSLINE) {
    len = parse_statusline(len);
  }
  
  if(WebLnkS.state == WEBCLIENT_STATE_HEADERS && len > 0) {
    len = parse_headers(len);
  }

  if(len > 0 && WebLnkS.state == WEBCLIENT_STATE_DATA &&
     WebLnkS.httpflag != HTTPFLAG_MOVED) {
    webclient_datahandler((char *)uip_appdata, len);
  }
}
/*-----------------------------------------------------------------------------------*/
void
webclient_appcall(void)
{

  if(uip_connected()) {
    WebLnkS.timer = 0;
    WebLnkS.state = WEBCLIENT_STATE_STATUSLINE;
    webclient_connected();
    senddata();
    return;
  }

  if(WebLnkS.state == WEBCLIENT_STATE_CLOSE) {
    webclient_closed();
    uip_abort();
    return;
  }

  if(uip_aborted()) {
    webclient_aborted();
  }
  if(uip_timedout()) {
    webclient_timedout();
  }

  
  if(uip_acked()) {
    WebLnkS.timer = 0;
    acked();
  }
  if(uip_newdata()) {
    WebLnkS.timer = 0;
    newdata_WClt();
  }
  if(uip_rexmit() ||
     uip_newdata() ||
     uip_acked()) {
    senddata();
  } else if(uip_poll()) {
    ++WebLnkS.timer;
    if(WebLnkS.timer == WEBCLIENT_TIMEOUT) {
      webclient_timedout();
      uip_abort();
      return;
    }
        /*    senddata();*/
  }

  if(uip_closed()) {
    if(WebLnkS.httpflag != HTTPFLAG_MOVED) {
      /* Send NULL data to signal EOF. */
      webclient_datahandler(NULL, 0);
    } else {
      if(resolv_lookup(WebLnkS.host) == NULL) {
		resolv_query(WebLnkS.host);
      }
      webclient_get(WebLnkS.host, WebLnkS.rport, WebLnkS.file);
    }
  }
}
/*-----------------------------------------------------------------------------------*/
/** @} */
/** @} */
