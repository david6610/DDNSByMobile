#ifndef __PLATFORM_INIT_H__
#define __PLATFORM_INIT_H__


/*LED private define*/


/*RS485 private define*/
#define RS485_1_RX  	GPIO_ResetBits(GPIOA, GPIO_Pin_0)
#define RS485_1_TX  	GPIO_SetBits(GPIOA, GPIO_Pin_0)

#define RS485_2_RX  	GPIO_ResetBits(GPIOA, GPIO_Pin_1)
#define RS485_2_TX  	GPIO_SetBits(GPIOA, GPIO_Pin_1)

#define RS485_3_RX  
#define RS485_3_TX  
/*platform initialization declaration*/
void Platform_Init(void);

void RCC_Configuration(void);
void NVIC_Configuration(void);
void IWDG_Configuration(u16 time);

#endif
