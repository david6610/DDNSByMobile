/**
 * \addtogroup apps
 * @{
 */

/**
 * \defgroup smtp SMTP E-mail sender
 * @{
 *
 * The Simple Mail Transfer Protocol (SMTP) as defined by RFC821 is
 * the standard way of sending and transfering e-mail on the
 * Internet. This simple example implementation is intended as an
 * example of how to implement protocols in uIP, and is able to send
 * out e-mail but has not been extensively tested.
 */

/**
 * \file
 * SMTP example implementation
 * \author Adam Dunkels <adam@dunkels.com>
 */

/*
 * Copyright (c) 2004, Adam Dunkels.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * This file is part of the uIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 * $Id: smtp.c,v 1.4 2006/06/11 21:46:37 adam Exp $
 */
#include "smtp.h"

#include "smtp-strings.h"
#include "psock.h"
#include <uip.h>

#include "global.h"
#include <string.h>

static struct smtp_state SmtpS;

static char *localhostname;
static uip_ipaddr_t smtpserver;

#define ISO_nl 0x0a
#define ISO_cr 0x0d

#define ISO_period 0x2e

#define ISO_2  0x32
#define ISO_3  0x33
#define ISO_4  0x34
#define ISO_5  0x35

#define ISO_AUTH_PASS  "235"		//用户验证成功
#define ISO_E1  "334"				//等待用户输入验证信息
#define ISO_E2  "454"				//临时认证失败
#define ISO_E3	"553"				//邮箱名不可用，要求的操作未执行（例如邮箱格式错误）  


#define user	"dXNlcm"       		//user base64


extern void debug_info_show(char *info, u16_t len);
extern char *itoa(int value, char *string, int radix);
extern void lport2ripStr(u16_t lport , uip_ipaddr_t ripaddr, u16_t rport ,char *port_ip_str);
/*---------------------------------------------------------------------------*/
static
PT_THREAD(smtp_thread(void))
{
  PSOCK_BEGIN(&SmtpS.ps);

  PSOCK_READTO(&SmtpS.ps, ISO_nl);
   
  if(strncmp(SmtpS.inputbuffer, smtp_220, 3) != 0) {   //S：220
    PSOCK_CLOSE(&SmtpS.ps);							   //   221 Bye OK queued as smtp7

    smtp_done(2, SmtpS.inputbuffer);				   
    PSOCK_EXIT(&SmtpS.ps);
  }
  
/*
client send :
	EHLO weidanghui.ut.cn

server send :
	220 163.com Anti-spam GT for Coremail System (163com[20121016])
	250-mail
	250-PIPELINING
	250-AUTH LOGIN PLAIN
	250-AUTH=LOGIN PLAIN
	250-coremail 1Uxr2xKj7kG0xkI17xGrU7I0s8FY2U3Uj8Cz28x1UUUUU7Ic2I0Y2UriMQbOUCa0xDrUUUUj
	250-STARTTLS
	250 8BITMIME
*/

  PSOCK_SEND_STR(&SmtpS.ps, (char *)smtp_ehlo); //C: ehlo +主机名
  PSOCK_SEND_STR(&SmtpS.ps, localhostname);
  PSOCK_SEND_STR(&SmtpS.ps, (char *)smtp_crnl);


  	PSOCK_READTO(&SmtpS.ps, ISO_nl);			//250-mail
  	PSOCK_READTO(&SmtpS.ps, ISO_nl);			//250-PIPELINING
  	PSOCK_READTO(&SmtpS.ps, ISO_nl);			//250-AUTH LOGIN PLAIN
  	PSOCK_READTO(&SmtpS.ps, ISO_nl);			//250-AUTH=LOGIN PLAIN
  	PSOCK_READTO(&SmtpS.ps, ISO_nl);			//250-coremail 1Uxr2xKj7kG0xkI17xGrU7I0s8FY2U3Uj8Cz28x1UUUUU7Ic2I0Y2UriMQbOUCa0xDrUUUUj
  	PSOCK_READTO(&SmtpS.ps, ISO_nl);			//250-STARTTLS
  	PSOCK_READTO(&SmtpS.ps, ISO_nl);			//250 8BITMIME

  if(strncmp(SmtpS.inputbuffer, smtp_250, 3) != 0) {   //S：250
    PSOCK_CLOSE(&SmtpS.ps);
    smtp_done(3,SmtpS.inputbuffer);
    PSOCK_EXIT(&SmtpS.ps);
  }

  PSOCK_SEND_STR(&SmtpS.ps, (char *)smtp_auth_login);				//C: AUTH LOGIN
  PSOCK_SEND_STR(&SmtpS.ps, (char *)smtp_crnl);
  PSOCK_READTO(&SmtpS.ps, ISO_nl);
  
  if(memcmp(SmtpS.inputbuffer, ISO_E1, strlen(ISO_E1))!=0) {		//S: 334 dXNlcm5hbWU6      // dXNlcm5hbWU6是username:的BASE64编码
    PSOCK_CLOSE(&SmtpS.ps);
    smtp_done(4,SmtpS.inputbuffer);
    PSOCK_EXIT(&SmtpS.ps);
  }
  //----user------------------------------------------
  PSOCK_SEND_STR(&SmtpS.ps, smtp_user);						//C: 用户名
  PSOCK_SEND_STR(&SmtpS.ps, (char *)smtp_crnl);
  PSOCK_READTO(&SmtpS.ps, ISO_nl);

 
  if(memcmp(SmtpS.inputbuffer, ISO_E1, strlen(ISO_E1))!=0) {		//S: 334 UGFzc3dvcmQ6 是Password:的BASE64编码
    PSOCK_CLOSE(&SmtpS.ps);
    smtp_done(5,SmtpS.inputbuffer);
    PSOCK_EXIT(&SmtpS.ps);
  }
  //----password------------------------------------------
  PSOCK_SEND_STR(&SmtpS.ps, smtp_pw);						//C: passward；注意各个邮件系统的密码长度要求
  PSOCK_SEND_STR(&SmtpS.ps, (char *)smtp_crnl);						//超过长度的密码要被截取掉，不要发出
  PSOCK_READTO(&SmtpS.ps, ISO_nl);
  
  if(memcmp(SmtpS.inputbuffer, ISO_AUTH_PASS, strlen(ISO_AUTH_PASS))!=0) {	//S: 235 Authentication successful.
    PSOCK_CLOSE(&SmtpS.ps);
    smtp_done(6,SmtpS.inputbuffer);
    PSOCK_EXIT(&SmtpS.ps);
  }
  //------------------------------------------------------
  PSOCK_SEND_STR(&SmtpS.ps, (char *)smtp_mail_from);				//C: from
  PSOCK_SEND_STR(&SmtpS.ps, SmtpS.from);
  PSOCK_SEND_STR(&SmtpS.ps, (char *)smtp_crnl);

  PSOCK_READTO(&SmtpS.ps, ISO_nl);

  if(SmtpS.inputbuffer[0] != ISO_2) {
    PSOCK_CLOSE(&SmtpS.ps);
    smtp_done(7,SmtpS.inputbuffer);
    PSOCK_EXIT(&SmtpS.ps);
  }

  PSOCK_SEND_STR(&SmtpS.ps, (char *)smtp_rcpt_to);				  //C: to
  PSOCK_SEND_STR(&SmtpS.ps, SmtpS.to);
  PSOCK_SEND_STR(&SmtpS.ps, (char *)smtp_crnl);

  PSOCK_READTO(&SmtpS.ps, ISO_nl);
  
  if(SmtpS.inputbuffer[0] != ISO_2) {
    PSOCK_CLOSE(&SmtpS.ps);
    smtp_done(8,SmtpS.inputbuffer);
    PSOCK_EXIT(&SmtpS.ps);
  }
  
  if(SmtpS.cc != 0) {
    PSOCK_SEND_STR(&SmtpS.ps, (char *)smtp_rcpt_to);
    PSOCK_SEND_STR(&SmtpS.ps, SmtpS.cc);
    PSOCK_SEND_STR(&SmtpS.ps, (char *)smtp_crnl);

    PSOCK_READTO(&SmtpS.ps, ISO_nl);
  
    if(SmtpS.inputbuffer[0] != ISO_2) {
      PSOCK_CLOSE(&SmtpS.ps);
      smtp_done(9,SmtpS.inputbuffer);
      PSOCK_EXIT(&SmtpS.ps);
    }
  }
  
  PSOCK_SEND_STR(&SmtpS.ps, (char *)smtp_data);
  
  PSOCK_READTO(&SmtpS.ps, ISO_nl);
  
  if(SmtpS.inputbuffer[0] != ISO_3) {
    PSOCK_CLOSE(&SmtpS.ps);
    smtp_done(10,SmtpS.inputbuffer);
    PSOCK_EXIT(&SmtpS.ps);
  }

  PSOCK_SEND_STR(&SmtpS.ps, (char *)smtp_to);
  PSOCK_SEND_STR(&SmtpS.ps, SmtpS.to);
  PSOCK_SEND_STR(&SmtpS.ps, (char *)smtp_crnl);
  
  if(SmtpS.cc != 0) {
    PSOCK_SEND_STR(&SmtpS.ps, (char *)smtp_cc);
    PSOCK_SEND_STR(&SmtpS.ps, SmtpS.cc);
    PSOCK_SEND_STR(&SmtpS.ps, (char *)smtp_crnl);
  }
  
  PSOCK_SEND_STR(&SmtpS.ps, (char *)smtp_from);
  PSOCK_SEND_STR(&SmtpS.ps, SmtpS.from);
  PSOCK_SEND_STR(&SmtpS.ps, (char *)smtp_crnl);
  
  PSOCK_SEND_STR(&SmtpS.ps, (char *)smtp_subject);
  PSOCK_SEND_STR(&SmtpS.ps, SmtpS.subject);
  PSOCK_SEND_STR(&SmtpS.ps, (char *)smtp_crnl);
  //----email format ------------------------
  // "Content-Type: text/html ;charset=\"gb2312\""
  // 
  /*
  PSOCK_SEND_STR(&SmtpS.ps, "Content-Type: text/html ;charset=\"gb2312\"");
  PSOCK_SEND_STR(&SmtpS.ps, (char *)smtp_crnl);
  PSOCK_SEND_STR(&SmtpS.ps, (char *)smtp_crnl);
  PSOCK_SEND_STR(&SmtpS.ps, (char *)smtp_crnl);
  */
  //-----------------------------------------
  PSOCK_SEND(&SmtpS.ps, SmtpS.msg, SmtpS.msglen);
  
  PSOCK_SEND_STR(&SmtpS.ps, (char *)smtp_crnlperiodcrnl);

  PSOCK_READTO(&SmtpS.ps, ISO_nl);
  if(SmtpS.inputbuffer[0] != ISO_2) {
    PSOCK_CLOSE(&SmtpS.ps);
    smtp_done(11,SmtpS.inputbuffer);
    PSOCK_EXIT(&SmtpS.ps);
  }

  PSOCK_SEND_STR(&SmtpS.ps, (char *)smtp_quit);
  //----------------------
  //smtp_done(SMTP_ERR_OK);
  PSOCK_READTO(&SmtpS.ps, ISO_nl);
  smtp_done(SMTP_ERR_OK, SmtpS.inputbuffer);
  //----------------------				   
  PSOCK_END(&SmtpS.ps);

}
/*---------------------------------------------------------------------------*/
void smtp_connected(void)
{
	char  info[70];
	char  OkInfo[] = " connect succeed.\r\n";
	u8_t	len  = 0;

	lport2ripStr(htons(uip_conn->lport) , uip_conn->ripaddr, htons(uip_conn->rport), info);
	len = strlen(info);

	memcpy(info + len, OkInfo , strlen(OkInfo));
	len += strlen(OkInfo);
	info[len ] ='\0';

	debug_info_show(info,len);
}


void  smtp_appcall(void)
{
  //---- by david-----
  if(uip_connected()) {
    smtp_connected();
    return;
  }
  //------------------
  if(uip_closed()) {
    SmtpS.connected = 0;
    return;
  }
  if(uip_aborted() || uip_timedout()) {
    SmtpS.connected = 0;
    smtp_done(1,"time out");
    return;
  }
  smtp_thread();
}
/*---------------------------------------------------------------------------*/
/**
 * Specificy an SMTP server and hostname.
 *
 * This function is used to configure the SMTP module with an SMTP
 * server and the hostname of the host.
 *
 * \param lhostname The hostname of the uIP host.
 *
 * \param server A pointer to a 4-byte array representing the IP
 * address of the SMTP server to be configured.	  //139	[113.108.212.80]
 */
void
smtp_configure(char *lhostname, u16_t *server)
{
  localhostname = lhostname;
  uip_ipaddr_copy(smtpserver, server);
}
/*---------------------------------------------------------------------------*/
/**
 * Send an e-mail.
 *
 * \param to The e-mail address of the receiver of the e-mail.
 * \param cc The e-mail address of the CC: receivers of the e-mail.
 * \param from The e-mail address of the sender of the e-mail.
 * \param subject The subject of the e-mail.
 * \param msg The actual e-mail message.
 * \param msglen The length of the e-mail message.
 */
unsigned char
smtp_send(char *to, char *cc, char *from,
	  char *subject, char *msg, u16_t msglen)
{
  struct uip_conn *conn;

  conn = uip_connect(&smtpserver, HTONS(25));
  if(conn == NULL) {
  //------------------------
		char info[70];
		char  ErrInfo[] = " cannot be connect.\r\n";
		u8_t	len  = 0;

		IpU16ToStr(smtpserver, info);
		len = strlen(info);

		memcpy(info + len, ErrInfo , strlen(ErrInfo));
		len += strlen(ErrInfo);
		info[len ] ='\0';

		debug_info_show(info,len);
  	//-------------------------
    return 0;
  }
  else {
	char  info[70];
	char  OkInfo[] = " is connecting..\r\n";
	u8_t	len  = 0;

	lport2ripStr(htons(conn->lport) , conn->ripaddr, htons(conn->rport), info);
	len = strlen(info);

	memcpy(info + len, OkInfo , strlen(OkInfo));
	len += strlen(OkInfo);
	info[len ] ='\0';

	debug_info_show(info,len);
  }
  SmtpS.connected = 1;
  SmtpS.to = to;
  SmtpS.cc = cc;
  SmtpS.from = from;
  SmtpS.subject = subject;
  SmtpS.msg = msg;
  SmtpS.msglen = msglen;
  //------	
  SmtpS.lport = conn->lport ;	
  //------	

  PSOCK_INIT(&SmtpS.ps, SmtpS.inputbuffer, sizeof(SmtpS.inputbuffer));
  
  return 1;
}
/*---------------------------------------------------------------------------*/

unsigned short
smtp_lport(void)
{
  return SmtpS.lport;
}

void
smtp_init(void)
{
    SmtpS.connected = 0;
}

void smtp_done(unsigned char ErrNum, char *ErrInfo)
{

	char info[70];
	char ErrStr[5];
	u8_t	len  = 0;

	lport2ripStr(htons(uip_conn->lport) , uip_conn->ripaddr, htons(uip_conn->rport), info);
	len = strlen(info);

	memcpy(info+len,  "\r\n", 2);
	len += 2;

	itoa( ErrNum , ErrStr, 10) ;

	memcpy(info+len,  ErrStr, strlen(ErrStr));
	len += strlen(ErrStr);

	memcpy(info+len,  ":", 1);
	len += 1;

	memcpy(info + len, ErrInfo , strlen(ErrInfo));
	len += strlen(ErrInfo);
	info[len ] ='\0';

	debug_info_show(info,len);
}
/*---------------------------------------------------------------------------*/
/** @} */
/** @} */
