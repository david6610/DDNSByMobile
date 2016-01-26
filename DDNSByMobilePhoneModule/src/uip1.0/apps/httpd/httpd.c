//*****************************************************************************
// HTTP server.
// Adam Dunkels <adam@dunkels.com>
//
// Copyright (c) 2001, Adam Dunkels.
// All rights reserved. 
//
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions 
// are met: 
// 1. Redistributions of source code must retain the above copyright 
//    notice, this list of conditions and the following disclaimer. 
// 2. Redistributions in binary form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimer in the 
//    documentation and/or other materials provided with the distribution. 
// 3. The name of the author may not be used to endorse or promote
//    products derived from this software without specific prior
//    written permission.  
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS
// OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
// GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  
//
// This file is part of the uIP TCP/IP stack.
//
//*****************************************************************************

#include "uip.h"
#include "httpd.h"
#include "string.h"	   //包含NULL
#include "pt.h"
#include "main.h"

//*****************************************************************************
//
// Macro for easy access to buffer data
//
//*****************************************************************************
#define BUF_APPDATA ((u8_t *)uip_appdata)
extern  bit     Rev_End_Flag;          /*串口数据到来*/
extern  bit 	ComTxdBufempty;
extern u16_t  Rev_Count;          /*串口接收计数*/
extern u8_t   xdata  ComRxdBuf[];      //串口的接收缓冲区
//*****************************************************************************
//
// Definitions of HTTP Server States
//
//*****************************************************************************
#define HTTP_NOGET      0
#define HTTP_FILE       1
#define HTTP_TEXT       2
#define HTTP_FUNC       3
#define HTTP_END        4

//*****************************************************************************
//
// Global for keeping up with web server state.
//
//*****************************************************************************
struct httpd_state *hs;
u16_t pass_flag;
static struct uip_udp_conn *udp_set_conn = NULL;

//*****************************************************************************
void
httpd_init(void)
{
    //
    // Listen to port 80.
    // 
	
    uip_listen(HTONS(80));
    uip_unlisten(HTONS(80));
}
//*****************************************************************************

//*****************************************************************************
//
// HTTP Application Callback Function
//
//*****************************************************************************
void
httpd_appcall(void)
{
       u16_t ii; 

	   hs = (struct httpd_state *)&(uip_conn->appstate);

	    if(uip_connected())
	    {
	      hs->count = 0;
	      uip_send(BUF_APPDATA,0);
		  return;
	    }

		if(uip_newdata()||uip_rexmit())
		{
		    if(uip_datalen()>0)
			{
			     #ifdef RS485
	             DE=1;	   /*使能发送*/
                 RE=1;
	             #else
	             ;
	             #endif
      
	            for(ii=0;ii<uip_datalen();ii++)
		        {
	          	  Printf_Char(BUF_APPDATA[ii]);//发到串口
		        }
  	            while(!ComTxdBufempty);
      
	           #ifdef RS485
               DE=0;	   /*使能发送*/
               RE=0;
	           #else
	           ;
	           #endif
		   }
		   else
		   {
			  ;
		   }
		}
	
	    if (uip_poll())			 
	    {
			  if(pass_flag)
			  {
			    pass_flag=0;
	   	        BUF_APPDATA="Adam Dunkels <adam@dunkels.com> Copyright (c) 2001, Adam Dunkels. All rights reserved.";
		        uip_len=sizeof("Adam Dunkels <adam@dunkels.com> Copyright (c) 2001, Adam Dunkels. All rights reserved.");
			    hs->count = 0;
			    uip_send(BUF_APPDATA,uip_len);
			    return;
			  }

			  if(Rev_End_Flag)
			  {
			      Rev_End_Flag=0;
				  if(Rev_Count>0)
				  {
				    uip_len=Rev_Count;
				    memcpy(BUF_APPDATA,ComRxdBuf,Rev_Count);
					uip_send(BUF_APPDATA,uip_len);
				  }
				  Rev_Count=0;
			  }
	    }
	    
	     	  
}






