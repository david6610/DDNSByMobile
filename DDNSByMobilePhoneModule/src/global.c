#include "global.h"

unsigned int  volatile  Sys_Dog_start=0;        //软狗标记
unsigned int  volatile  Sys_Dog_Count=0;        //软狗计数器

unsigned int  volatile  GSM_Heartbeat_Count=0;        // GSM 定时检测心跳包周期
u8 volatile  GSM_timing_wakeup  = 0;			// GSM模块 唤醒标志			             

unsigned int  volatile  Get_IP_Req_Timer=0;        // GSM 定时读信息计时器
u8 volatile  IP_Req_wakeup	= 0;			// GSM模块 定时读唤醒			             

char caNewString[1024];	            //注意定义在函数内部容易堆栈溢出 此值的范围不能小于最后一次查询的内存位置
char HexTable[]={"0123456789ABCDEF"};    //ascii－>hex的转换表
char HEXStr[32];	                     //数据转换临时内存
char sssStr[5];		                     //数据转换临时内存

/*usart1 send start and end flags & send dwell time counter */
u8 volatile  rcv_usart1_str_flag   = 0;		//串口数据接收启动标记
u8 volatile  rcv_usart1_end_flag   = 0;		//串口数据接收结束标记			             
u8 volatile  rcv_usart1_over_count = 0;		//数据接收时间溢出标记
u8           rcv_usart1_array[BUF1_LEN];
u8  volatile rcv_usart1_data_flg   = 0;
u16 volatile rcv_usart1_data_len   = 0;


u8 volatile rcv_usart2_str_flag    = 0;		//串口数据接收启动标记
u8 volatile  rcv_usart2_end_flag   = 0;		//串口数据接收结束标记			             
u8 volatile  rcv_usart2_over_count = 0;		//数据接收时间溢出标记
u8           rcv_usart2_array[BUF2_LEN];
u8  volatile rcv_usart2_data_flg   = 0;
u16 volatile rcv_usart2_data_len   = 0;

u8 *inTx1Buf;
u8 *outTx1Buf; 
u8 *inRx1Buf;
u8 *outRx1Buf;                      //收发缓冲区读写指针中断函数中用到,作为全局变量

u8 Tx1Buf[BUF1_LEN];
u8 Rx1Buf[BUF1_LEN];                // 收发缓冲区实体


//u8 send_buffer2[BUF2_LEN];

u8 *inTx2Buf;
u8 *outTx2Buf; 
u8 *inRx2Buf;
u8 *outRx2Buf;                      //收发缓冲区读写指针中断函数中用到,作为全局变量

u8 Tx2Buf[BUF2_LEN];
u8 Rx2Buf[BUF2_LEN];                // 收发缓冲区实体
		                   


/*Communication err flag*/

u8  volatile led_red_sel = 0;
u8  volatile led_blue_sel = 0;


/*! \ Hex2HexStr
 *
 */
void Hex2HexStr(unsigned char hex) 
{
  char  *Str;
  char  ch;
  memset(HEXStr,0,sizeof(HEXStr));

  Str=HEXStr;

  ch  =hex>>4;
  *Str++=HexTable[ch];

  ch  =hex&0x0F;
  *Str++=HexTable[ch];

}
/*! \ Hex2Str
 *
 */
void Hex2Str(unsigned char hex) 
{
   char *Str;
   unsigned char x,y,k;
   
   memset(HEXStr,0,sizeof(HEXStr));
   Str = HEXStr;

    x=hex;
    if(x>99)
	{
      y=x/100;*Str++=y+'0';
      x=x-100*y;y=x/10;*Str++=y+'0';
      x=x-10*y;*Str++=x+'0';
    }
    else if(x>9)
	{
      y=x/10;*Str++=y+'0';
      x=x-10*y;*Str++=x+'0';
    }
    else
	{
      *Str++=x+'0';
    }

	for(k=0;k<3;k++)
	{
	  if(HEXStr[k]==0)
	  {
		if(k==0){};
	    if(k==1){memmove(HEXStr+2,HEXStr,1);HEXStr[0]=0x30;HEXStr[1]=0x30;}
		if(k==2){memmove(HEXStr+1,HEXStr,2);HEXStr[0]=0x30; }
	  }
	}
   
}

/**********************************************************************
**函数原型：    void 	int2Str(unsigned int portnum)
**入口参数:     unsigned int portnum		:UDP或TCP端口
**出口参数:		无
**返 回 值：	无       
**说    明：	实现端口号到字符串的转换,字符串存放在PortStr[5]字符串中
************************************************************************/
void U16_2Str(unsigned int portnum)    
{
    unsigned int  x;
	unsigned char y;
	unsigned char *Str;
    Str = (unsigned char *)sssStr;
	x = portnum;
	if(x>9999)
	{
        y=x/10000;*Str++=y+'0';
        x=x-10000*y;y=x/1000;*Str++=y+'0';
        x=x-1000*y;y=x/100;*Str++=y+'0';
		x=x-100*y;y=x/10;*Str++=y+'0';
		x=x-10*y;*Str++=x+'0';
		*Str++='\0';
 	}
    else if(x>999)
	{
		y=x/1000;*Str++=y+'0';
       	x=x-1000*y;y=x/100;*Str++=y+'0';
		x=x-100*y;y=x/10;*Str++=y+'0';
		x=x-10*y;*Str++=x+'0';
		*Str++='\0';
    }
    else if(x>99)
	{
        y=x/100;*Str++=y+'0';
       	x=x-100*y;y=x/10;*Str++=y+'0';
		x=x-10*y;*Str++=x+'0';
		*Str++='\0';
	}
	else
	{
		y=x/10;*Str++=y+'0';
		x=x-10*y;*Str++=x+'0';
		*Str++='\0';
	}    
	
}
/*! \ ReplaceStr
 *
 */
int ReplaceStr(char *sSrc, char *sSubStr, char *sReplaceStr)
{
    int  StringLen;

//	char caNewString[1024];	 //注意定义在函数内部容易堆栈溢出 此值的范围不能小于最后一次查询的内存位置
	
    char *FindPos = strstr(sSrc, sSubStr);
    if( (!FindPos) || (!sSubStr) )
        return -1;
    
    while( FindPos )
    {
        memset(caNewString, 0, sizeof(caNewString));
        StringLen = FindPos - sSrc;
        strncpy(caNewString, sSrc, StringLen);//0x14F 最远的位置
        strcat(caNewString, sReplaceStr);
        strcat(caNewString, FindPos + strlen(sSubStr));
        strcpy(sSrc, caNewString);
        
        FindPos = strstr(sSrc, sSubStr);
    }
    
    return 0;
}

/*
 * 函数名：itoa
 * 描述  ：将整形数据转换成字符串
 * 输入  ：-radix =10 表示10进制，其他结果为0
 *         -value 要转换的整形数
 *         -buf 转换后的字符串
 *         -radix = 10
 * 输出  ：无
 * 返回  ：无
 * 调用  ：被USART1_printf()调用
 */
char *itoa(int value, char *string, int radix)
{
    int     i, d;
    int     flag = 0;
    char    *ptr = string;

    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }

    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }

    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';

        /* Make the value positive. */
        value *= -1;
    }

    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;

        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }

    /* Null terminate the string. */
    *ptr = 0;

    return string;

} /* NCL_Itoa */

