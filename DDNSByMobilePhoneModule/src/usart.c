
/*! \file usart.c
 *	\brief usart configure file.
 */

#include "global.h"


GPIO_InitTypeDef        GPIO_InitStructure;
USART_InitTypeDef       USART_InitStructure;
USART_ClockInitTypeDef  USART_ClockInitStructure;

/*! \fn USART_Configuration(void)
 *	\brief in this function, we need to configure each usart individually, also the usart buf.
 */
void USART_Configuration(void)
{
    USART1_Configuration();
//    USART2_Configuration();
  //USART3_Configuration();
   	BUF_INIT(1);
//	BUF_INIT(2); 
}

/*! \fn USART1_Configuration(void)
 *  \brief USART1_Configuration
 *
 *   prepared for L04 commands.
 */
void USART1_Configuration(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |       
                           RCC_APB2Periph_AFIO	|
						   RCC_APB2Periph_USART1 ,
                           ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		     //Pushpull out-TX			 A9 USART1_Tx
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //In floating in-RX         A10 USART1_Rx
    GPIO_Init(GPIOA, &GPIO_InitStructure);


    USART_InitStructure.USART_BaudRate = 57600;//115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
    USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
    USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
    USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;

    USART_ClockInit(USART1, &USART_ClockInitStructure);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	        	//usart1 interrupt enable

    USART_Init(USART1, &USART_InitStructure);
    
    USART_Cmd(USART1, ENABLE);
   

}

/*!  \fn void USART2_Configuration(void)
 *	 \brief void USART2_Configuration(void)
 *   prepared for incommer device commands.
 */
void USART2_Configuration(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB2Periph_GPIOA |
                           RCC_APB2Periph_AFIO  |
						   RCC_APB1Periph_USART2, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;					 // A2 --T2X
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;					 // A3 --R2X
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;	 //stm32 偶校验时必须要9位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;		 
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
    USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
    USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
    USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;

    USART_ClockInit(USART2, &USART_ClockInitStructure);
    USART_Init(USART2, &USART_InitStructure);

    USART_Cmd(USART2, ENABLE);
    USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);		  
}
/*USART3*/
void USART3_Configuration(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB |
                           RCC_APB2Periph_AFIO, ENABLE);
    
    RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART3, ENABLE);		   

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				// B10 --T3X	   
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				// B11 --R3X	   
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
    USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
    USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
    USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;

    USART_ClockInit(USART3, &USART_ClockInitStructure);
    USART_Init(USART3, &USART_InitStructure);

    USART_Cmd(USART3, ENABLE);
    USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);		     //usart3 interrupt enable

}

/*!  \fn USART1_Put_Char(unsigned char c)
 *	 \brief USART1 put char out.
 *   \param c char need to put out.
 */
void USART1_Put_Char(unsigned char c)
{
    RS485_1_TX;
    delay_ms(1);
    USART_SendData(USART1, c);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );
    delay_ms(1);					  // the delay time is very importent in RS485 mode
	RS485_1_RX;
}
/*!  \fn USART1_Put_Data(unsigned char * str, unsigned int len)
 *	 \brief USART2 put char out.
 *   \param str string's pointer, which need to be put out.
 */
void USART1_Put_Data(unsigned char * str, unsigned int len)
{
    RS485_1_TX;
    delay_ms(1);
    while(len)
    {
        USART_SendData(USART1, *str++); 
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
		len--;
    }
    delay_ms(1);
    RS485_1_RX;
}

/**********************************************************************
**函数原型：    void USART1_Put_String(unsigned char  *str)
**参数说明：	string：	字符串的起始地址
**返 回 值：	无      
**说    明：	向串口发送字符串，碰到0x00结束
************************************************************************/
void USART1_Put_String(unsigned char  *str)
{
    RS485_1_TX;
    delay_ms(1);
    while(*str!=0)
    {
        USART_SendData(USART1, *str++); 
        while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    }
    delay_ms(1);
    RS485_1_RX;
}


/*!  \fn USART2_Put_Char(unsigned char c)
 *	 \brief USART2 put char out.
 *   \param c char need to put out.
 */
void USART2_Put_Char(unsigned char c)
{
  	RS485_2_TX;
    delay_ms(1);
    USART_SendData(USART2, c);
    while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET );
 	delay_ms(1);
    RS485_2_RX;
}

/**********************************************************************
**函数原型：    void USART2_Put_String(unsigned char  *str)
**参数说明：	string：	字符串的起始地址
**返 回 值：	无      
**说    明：	向串口发送字符串，碰到0x00结束
************************************************************************/
void USART2_Put_String(unsigned char  *str)
{
    RS485_2_TX;
    delay_ms(1);
    while(*str!=0)
    {
        USART_SendData(USART2, *str++); 
        while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
    }
    delay_ms(1);
    RS485_2_RX;
}




/*!  \fn USART2_Put_Data(unsigned char * str, unsigned int len)
 *	 \brief USART2 put char out.
 *   \param str string's pointer, which need to be put out.
 */
void USART2_Put_Data(unsigned char * str, unsigned int len)
{
    RS485_2_TX;
    delay_ms(1);
    while(len)
    {
        USART_SendData(USART2, *str++); 
        while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
		len--;
    }
    delay_ms(1);
    RS485_2_RX;

}
void USART3_Put_Char(unsigned char c)
{
    RS485_3_TX;
    delay_ms(1);
    USART_SendData(USART3, c);
    while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET );
    delay_ms(1);
    RS485_3_RX;
}
void USART3_Put_Data(unsigned char * str, unsigned int len)
{
    RS485_3_TX;
    delay_ms(1);
    while(len)
    {
        USART_SendData(USART3, *str++); 
        while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
		len--;
    }
    delay_ms(1);
    RS485_3_RX;

}




