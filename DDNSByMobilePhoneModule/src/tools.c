#include "global.h"


char HexTable[]={"0123456789ABCDEF"}; //ascii－>hex的转换表
char HEXStr[32];	//数据转换临时内存
char sssStr[5];		//数据转换临时内存
char caNewString[1024];	 //注意定义在函数内部容易堆栈溢出 此值的范围不能小于最后一次查询的内存位置
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
    Str = sssStr;
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
static char *itoa(int value, char *string, int radix)
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

/*! \ Get_SerialNum
 *
 */
void Get_SerialNum(void) 
{ 
  u32 Device_Serial0, Device_Serial1, Device_Serial2;   
  Device_Serial0 = *(vu32*)(0x1FFFF7E8); 
  Device_Serial1 = *(vu32*)(0x1FFFF7EC); 
  Device_Serial2 = *(vu32*)(0x1FFFF7F0);
  mymac[3]=(u8 )(Device_Serial0>>1);
  mymac[4]=(u8 )(Device_Serial1>>2);
  mymac[5]=(u8 )(Device_Serial2>>3);    	   /*MAC最后3字节利用STM的唯一ID计算，特别注意此方法可能存在重复*/
}