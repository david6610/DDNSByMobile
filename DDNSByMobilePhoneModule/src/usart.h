#ifndef __USART_H__
#define __USART_H__

#include "global.h"

    void USART_Configuration(void);
    void USART1_Configuration(void);
    void USART2_Configuration(void);
    void USART3_Configuration(void);

	void USART1_Put_Char(unsigned char c);
	void USART1_Put_Data(unsigned char *str, unsigned int len);
	void USART1_Put_String(unsigned char  *str);

	void USART2_Put_Char(unsigned char c);
	void USART2_Put_Data(unsigned char *str, unsigned int len);
	void USART2_Put_String(unsigned char  *str);
#endif
