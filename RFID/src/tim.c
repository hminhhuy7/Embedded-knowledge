#include "tim.h"

void TIM_Config(){
	   RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	
	
	  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; // 72Mhz /(1, 2, 4) = ...
	  TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1; // scaling again 72Mhz / 7200 = ... 
	  TIM_TimeBaseInitStructure.TIM_Period = 0xFFFF - 1; // using in interupt for overflow time
	  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	  
	  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	  TIM_Cmd(TIM2, ENABLE);
	
	  GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
    GPIO_Init(GPIOC, &GPIO_InitStructure);	
	
	  
}

void delay_ms(int timedelay){
	  TIM_SetCounter(TIM2, 0);
	   while (TIM_GetCounter(TIM2) < timedelay*10) {};
}
void blinkLed(int timedelay){
	  GPIO_SetBits(GPIOC, GPIO_Pin_13); // Ghi 1 ra
		delay_ms(timedelay);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		delay_ms(timedelay);		
}

