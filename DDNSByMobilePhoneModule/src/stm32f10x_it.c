#include "global.h"

__IO int32_t g_RunTime = 0; 
__IO int32_t time_1000ms = 0; 


void SysTick_Handler(void) 
{
 
}
/*usart1*/
void USART1_IRQHandler(void)
{
    unsigned char *t1;										   //  *t1 新定义指针，指向Buf1

    if(USART_GetITStatus(USART1, USART_IT_RXNE)==SET)		   //  判断，一旦接收到数据
    {
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);		   //  清除中断标志位

        rcv_usart1_str_flag=1;					               //  串口数据接收标志置1
        rcv_usart1_over_count=0;			                   //  每来一字节溢出计数标志清0

        t1 = inRx1Buf;							   			   //  两个指针,一个用来收,一个用来读
        (u8 *)t1++;				                               //  保留指针位置

        if((u8 *)t1 == Rx1Buf + BUF1_LEN) 			   		   //  判断是否到缓冲区末尾
		{
            t1 = Rx1Buf;	                                   //  如果到缓冲区末尾,则返回缓冲区头

		}
        if((u8 *)t1 == (u8 *)outRx1Buf)						   //  如果相等,说明缓冲区满了,RxBuf Full
        {
         
        }

        *inRx1Buf = USART_ReceiveData(USART1);
        inRx1Buf  = t1;
    }
    /*溢出-如果发生溢出需要先读SR,再读DR寄存器 则可清除不断入中断的问题*/
    if(USART_GetFlagStatus(USART1,USART_FLAG_ORE)==SET)
    {
        USART_ClearFlag(USART1,USART_FLAG_ORE);
        USART_ReceiveData(USART1);
    }
}

/*usart1*/

/*
void USART2_IRQHandler(void)
{
    unsigned char *t2;										   //  t1 新定义指针，指向Buf1

    if(USART_GetITStatus(USART2, USART_IT_RXNE)==SET)		   //  判断，一旦接收到数据
    {
        USART_ClearITPendingBit(USART2,USART_IT_RXNE);		   //  清除中断标志位

        rcv_usart2_str_flag=1;					               //  串口数据接收标志置1
        rcv_usart2_over_count=0;			                   //  每来一字节溢出计数标志清0

        t2 = inRx2Buf;							   			   //  两个指针,一个用来收,一个用来读
        (u8 *)t2++;				                               //  保留指针位置

        if((u8 *)t2 == Rx2Buf + BUF2_LEN) 			   		   //  判断是否到缓冲区末尾
            t2 = Rx2Buf;	                                   //  如果到缓冲区末尾,则返回缓冲区头

        if((u8 *)t2 == (u8 *)outRx2Buf)						   //  如果相等,说明缓冲区满了,RxBuf Full
        { 
            //溢出-如果发生溢出需要先读SR,再读DR寄存器 则可清除不断入中断的问题
            if(USART_GetFlagStatus(USART2,USART_FLAG_ORE)==SET)
            {
                USART_ClearFlag(USART2,USART_FLAG_ORE);	//读SR
                USART_ReceiveData(USART2);				//读DR
            }
        }

        *inRx2Buf = USART_ReceiveData(USART2);
        inRx2Buf  = t2;
    }
    //溢出-如果发生溢出需要先读SR,再读DR寄存器 则可清除不断入中断的问题
    if(USART_GetFlagStatus(USART2,USART_FLAG_ORE)==SET)
    {
		USART_ClearFlag(USART2,USART_FLAG_ORE);
        USART_ReceiveData(USART2);
    }
}
*/


/*tim2*/
void TIM2_IRQHandler(void)
{
	static u8  s_count = 0; 
	static u16 u16SubCounter    =0;
	static u16 u16Tim_flg_200ms =0;
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

	   	if(CPU_DOG) IWDG_ReloadCounter();  /*喂STM32内置硬件狗*/
	   	if(Sys_Dog_start == 1)
	   	{
	     	if((++Sys_Dog_Count) > 3000)	           /*软狗system  DOG 3000ms over*/
         	{
		  		Sys_Dog_Count = 0;
		  		if(CPU_DEBUG) USART1_Put_String("[system info]:system  DOG 3000ms over=:( \r\n");			  
          		*((u32*)0xE000ED0C)=0x05fa0004; /*系统软复位*/ 
         	}
			//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	     	if((++GSM_Heartbeat_Count) > 15000)	               /*GSM模块 定时发送AT命令 查看是否激活在线 3000ms over*/
         	{
		  		GSM_Heartbeat_Count = 0;
				GSM_timing_wakeup =1 ;
          	}
	     	if((++Get_IP_Req_Timer) > 20000)	           		/*在接到查询IP地址后，向服务器发出请求，如果一次请求不能获得，在一定时间后再发送请求*/
         	{
		  		Get_IP_Req_Timer = 0;
				IP_Req_wakeup =1 ;
          	}
			//■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
	   	}

		if(++u16SubCounter > 1000)
		{
			u16SubCounter = 0;
			time_1000ms = 1;								//  1s时间到	 
		}

        if(rcv_usart1_str_flag)					           	//  接收了串口数据
        {
            if(rcv_usart1_over_count < 2)
            {
                rcv_usart1_over_count++;			       	//  2ms串口接收结束
            }
            else
            {
                rcv_usart1_str_flag = 0;
                rcv_usart1_end_flag=1;				       //  置位标记rcv_end_flag
            }
        } 
		/*
        if(rcv_usart2_str_flag)					           //  接收了串口数据
        {
            if(rcv_usart2_over_count < 2)
            {
                rcv_usart2_over_count++;			       //  2ms串口接收结束
            }
            else
            {
                rcv_usart2_str_flag=0;
                rcv_usart2_end_flag=1;				       //  置位标记rcv_end_flag
            }
        }
		*/
		u16Tim_flg_200ms++;
		if(u16Tim_flg_200ms == 200)
		{
			u16Tim_flg_200ms=0;
		  	//LED_Green_FLASH();
		}      
        
       	if (++s_count >= 10)  
       	{  
          	s_count = 0;  
          	g_RunTime++;    /* 全局运行时间每10ms增1 */  
          	if (g_RunTime == 0x80000000)  
          	{  
             	g_RunTime = 0;  
          	}
       	}
    }
}



void HardFault_Handler(void)
{
    *((u32 *)0xE000ED0C) = 0x05FA0004;
}
void BusFault_Handler(void)
{
    *((u32 *)0xE000ED0C) = 0x05FA0004;
}
void UsageFault_Handler(void)
{
    *((u32 *)0xE000ED0C) = 0x05FA0004;
}
