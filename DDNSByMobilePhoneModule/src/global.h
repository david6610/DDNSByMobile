
#ifndef __GLOBAL_H__
#define __GLOBAL_H__

/* include files  */
#include "stdlib/stm32f10x.h"
#include "stdlib/stm32f10x_flash.h"
#include "platform_init.h"	
#include "gpio.h"
#include "usart.h"
#include "usart_app.h"
#include "exti.h"
#include "timer.h"	
#include "delay.h"
#include "main.h"
#include "stm32f10x_it.h"
#include "string.h"
#include "spi_enc28j60.h"
#include "enc28j60.h"
#include "uip.h"
#include "uip_arp.h"
#include "uipopt.h"
#include "clock-arch.h"
#include "uip_timer.h"
#include "tapdev.h"
#include "dhcpc.h"


char *itoa(int value, char *string, int radix);
void Hex2Str(unsigned char hex);
void Hex2HexStr(unsigned char hex);
void U16_2Str(unsigned int portnum);
int  ReplaceStr(char *sSrc, char *sSubStr, char *sReplaceStr);


#define  RST_CPU()      (*((u32*)0xE000ED0C)=0x05fa0004) /*系统软复位*/


/********************************* debug define ********************************************/
#define  CPU_DOG		     0	 //jlink仿真时不可以开启
#define  CPU_DEBUG_TIMER     0	 //UIP的时间溢出调试
#define  CPU_DEBUG_KEEPALIVE 0	 //服务器保活时间调试
#define  CPU_DEBUG           0	 //系统信息打印调试
#define  TCP_LOOKBACK        0   //以太网TCP协议回传,主要用于测试性能的应用
#define  TCP2UART1           1   //以太网TCP转发UART1
#define  TCP2UART2           0   //以太网TCP转发UART2
#define  UIP_STATIC_IP_ADDR      //启用DHCP功能时候注销即可

// --- by david 
#define GSM_DEBUG			1							//调试阶段，把UART数据通过以太网传输出去供调试
#define ETH_DEBUG			1							//调试阶段，把ETH数据通过 UART 传输出去供调试
#define WEBCLIENT_DEBUG		1							//通过外网获取IP地址调试阶段；

/********************************* debug define ********************************************/
/********************************* private define ********************************************/
#define  SOCKET_COMM_ON		 0	 //通信中或者准备中
#define  SOCKET_COMM_OFF	 1	 //需要关闭 socket
/********************************* private define ********************************************/

/*! \brief Buf1 that store usart1's data, this macro indicates the buffer volume.
 */
#define  BUF1_LEN            1024	         // the dimension of the buufer used in usart1  
/*! \brief Buf2 that store usart2's data, this macro indicates the buffer volume.
 */
#define  BUF2_LEN            255	         // the dimension of the buufer used in usart1  


#define  array_maxlen        1024			 //	the length of the array which store the data from buffer



/********************************* private typedef ********************************************/

/*Flags for instruction's*/

typedef struct
{
	u8 event;
	u8 send_times;
	u8 send_str;
	u8 send_end;
	u8 send_count;
	u8 send_ok;

}flags_typedef;


extern unsigned char  volatile  sys_year;
extern unsigned char  volatile  sys_month;
extern unsigned char  volatile  sys_date;
extern unsigned char  volatile  sys_hour;
extern unsigned char  volatile  sys_minute;
extern unsigned char  volatile  sys_second;


/********************************* global variables ******************************************/
extern unsigned int  volatile  Sys_Dog_start;      
extern unsigned int  volatile  Sys_Dog_Count;        
extern unsigned int  volatile  GSM_Heartbeat_Count;   
extern unsigned int  volatile  Get_IP_Req_Timer;   

extern u8 volatile 		GSM_timing_wakeup;
extern u8 volatile 		IP_Req_wakeup;
     
extern __IO int32_t time_1000ms;
extern char caNewString[1024];	        
extern char HexTable[];                          
extern char HEXStr[32];	                                       
extern char sssStr[5];	
/*usart1*/
extern u8 volatile rcv_usart1_str_flag;
extern u8 volatile rcv_usart1_end_flag;					             
extern u8 volatile rcv_usart1_over_count;
extern u8          rcv_usart1_array[BUF1_LEN];
extern u8 volatile rcv_usart1_data_flg;
extern u16 volatile rcv_usart1_data_len;

extern u8 *inTx1Buf;
extern u8 *outTx1Buf; 
extern u8 *inRx1Buf;
extern u8 *outRx1Buf; 
extern u8 Tx1Buf[BUF1_LEN];
extern u8 Rx1Buf[BUF1_LEN]; 
                            

/*usart2*/
/*
extern u8 volatile rcv_usart2_str_flag;
extern u8 volatile rcv_usart2_end_flag;					             
extern u8 volatile rcv_usart2_over_count;
extern u8          rcv_usart2_array[BUF2_LEN ];
extern u8 volatile rcv_usart2_data_flg;
extern u16 volatile rcv_usart2_data_len;

extern u8 *inTx2Buf;
extern u8 *outTx2Buf; 
extern u8 *inRx2Buf;
extern u8 *outRx2Buf; 
extern u8 Tx2Buf[BUF2_LEN];
extern u8 Rx2Buf[BUF2_LEN]; 
*/ 
 	


/*Communication err flag*/

extern u8 volatile led_red_sel;
extern u8 volatile led_blue_sel;

#endif
