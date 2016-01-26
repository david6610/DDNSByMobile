
#include "global.h"

/**********************************************************************
 *函数原型：    GetDataToBuf1()
 *参数说明：	u8 *ch
 *返 回 值：	temp
 *说    明：	从串口缓冲区接收一个字符
 *********************************************************************/
static u8 GetDataToBuf1(u8 *ch)
{
	

	if((u8 *)inRx1Buf == (u8 *)outRx1Buf) 	 return 0;			  // 数据接收Buff地址和数据读取Buff地址一致表示收完数据

	*ch = *outRx1Buf;											  // 将数据读出内容赋值给函数参数
	outRx1Buf++;					                              // 数据被读走，读指针加1

	if((u8 *)outRx1Buf == Rx1Buf + BUF1_LEN) 					  // 读出指针指向位置，+ Buff1长度 = 接收数据指针指向位置
	outRx1Buf = Rx1Buf;                                           // 如果读指针到缓冲区尾部,那么重新让其指向到头部

	return 1;
}

/**********************************************************************
 *函数原型：    GetDataToBuf2()
 *参数说明：	u8 *ch
 *返 回 值：	temp
 *说    明：	从串口缓冲区接收一个字符
 *********************************************************************/
/*
static u8 GetDataToBuf2(u8 *ch)
{
	USART_ITConfig(USART2,USART_IT_RXNE,DISABLE);				  // 关中断，停止数据接收

	if((u8 *)inRx2Buf == (u8 *)outRx2Buf) 					      // 数据接收Buff地址和数据读取Buff地址一致表示Buff1已经满了
	{
		USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);		      // 打开接收中断，继续接收数据
	    return 0;
	}
	
	*ch = *outRx2Buf;											  // 将数据读出内容赋值给函数参数
	outRx2Buf++;					                              // 数据被读走，读指针加1

	if((u8 *)outRx2Buf == Rx2Buf + BUF2_LEN) 					  // 读出指针指向位置，+ Buff1长度 = 接收数据指针指向位置
	outRx2Buf = Rx2Buf;                                           // 如果读指针到缓冲区尾部,那么重新让其指向到头部
	
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	return 1;
}
*/
/**********************************************************************
 *函数原型：    Usart1_Command
 *入口参数:		com_len
 *出口参数:		无
 *返 回 值：	无
 *功能说明:		接收上位机数据,等待一帧数据结束处理
 **********************************************************************/

u16 Rcv_Usart1_To_Array(void)
{
    unsigned int dat_len = 0;
    unsigned char ch;

    while(GetDataToBuf1(&ch))
    {
        rcv_usart1_array[dat_len] = ch;			   //从环形缓冲区读数据
        dat_len++;
       
	    if(dat_len == array_maxlen) 
		{
		  dat_len=0;	
		  return array_maxlen;
		}
    }
	return dat_len;
} 
/*-------------------------------------------------
u16 Rcv_Usart1_To_Array(void)
{
    unsigned int dat_len = 0;
    unsigned char ch;

    while(GetDataToBuf1(&ch))
    {
        rcv_usart1_array[dat_len] = ch;			   //从环形缓冲区读数据
        dat_len++;
       
	    if(dat_len == array_maxlen) 
		{
		  dat_len=0;	
		  return array_maxlen;
		}
    }
	return dat_len;
} 
----------------------------------------------------*/
/*
u16 Rcv_Usart2_To_Array(void)
{
    unsigned int dat_len = 0;
    unsigned char ch;

    while(GetDataToBuf2(&ch))
    {
        rcv_usart2_array[dat_len] = ch;			   //从环形缓冲区读数据
        dat_len++;
       
	    if(dat_len == array_maxlen) 
		{
		  dat_len=0;	
		  return array_maxlen;
		}
    }
	return dat_len;
} 
*/
