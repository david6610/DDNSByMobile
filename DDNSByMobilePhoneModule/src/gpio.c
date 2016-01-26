#include "global.h"

/*GPIO configuration*/
void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	
	/*RS485 control PA.0 PA.1*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;			 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);


	/*LED GREEN*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB, GPIO_Pin_9);	 // turn off green led

}

void LED_Green_ON(void)
{
   GPIO_ResetBits(GPIOB, GPIO_Pin_9);	 // turn off green led
}
void LED_Green_OFF(void)
{
   GPIO_SetBits(GPIOB, GPIO_Pin_9);	 // turn off green led
}
void LED_Green_FLASH(void)
{
   GPIOB->ODR^=GPIO_Pin_9;
}

/////////////////////////////////////									 
void LED_Red_FLASH(void)
{
   GPIOB->ODR^=GPIO_Pin_11;
}
///////////////////////////////////////
void LED1_ON(void)
{
	GPIO_ResetBits(GPIOB, GPIO_Pin_9);	 // turn off led1
}
void LED1_OFF(void)
{
   	GPIO_SetBits(GPIOB, GPIO_Pin_9);	 // turn off led1
}
void LED1_FLASH(void)
{
   	GPIOB->ODR^=GPIO_Pin_9;
}

void LED2_ON(void)
{
   GPIO_ResetBits(GPIOC, GPIO_Pin_11);	 // turn off led2
}
void LED2_OFF(void)
{
   GPIO_SetBits(GPIOC, GPIO_Pin_11);	 // turn off led2
}
void LED2_FLASH(void)
{
   GPIOC->ODR^=GPIO_Pin_11;
}


