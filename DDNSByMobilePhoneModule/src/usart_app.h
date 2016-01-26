/*! \file usart_app.h
 *
 */
#ifndef __USART_APP_H__
#define __USART_APP_H__


#define BUF_INIT(n)		{  \
                           inRx##n##Buf  = Rx##n##Buf;  \
                           outRx##n##Buf = Rx##n##Buf;  \
						   inTx##n##Buf  = Tx##n##Buf;  \
						   outTx##n##Buf = Tx##n##Buf;  \
						}

u16  Rcv_Usart1_To_Array(void);
//u16  Rcv_Usart2_To_Array(void);


#endif
