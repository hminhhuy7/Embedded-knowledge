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

void TIMPWM_Config(){
	   RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

	
	   GPIO_InitTypeDef GPIO_InitStruct;
	   GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	   GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	   //TIM1
	  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; // 72Mhz /(1, 2, 4) = ...
	  TIM_TimeBaseInitStructure.TIM_Prescaler = 71; // scaling again 72Mhz / 7200 = ... 
	  TIM_TimeBaseInitStructure.TIM_Period = 20000 - 1; // using in interupt for overflow time
	  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	  
	  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure); //timer tuong ung
	  //TIM_Cmd(TIM1, ENABLE);
	
	  //CH1
	  TIM_OCInitTypeDef TIM_OCInitStruct;
	  TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1; // kenh tuong ung moi chan se co 1 timer va 1 kenh tuong ung 
		TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCInitStruct.TIM_Pulse = 1000;
		TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
		
		TIM_OC1Init(TIM1, &TIM_OCInitStruct);
		TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable); // tu dong nap lai
		//TIM_ARRPreloadConfig(TIM1, ENABLE);
		TIM_Cmd(TIM1, ENABLE);
	  TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

void delay_ms(int timedelay){
	  TIM_SetCounter(TIM2, 0);
	   while (TIM_GetCounter(TIM2) < timedelay*10) {};
}

void set_pwm(uint16_t angle){
	  TIM_SetCompare1(TIM1, angle); 
}


void blinkLed(int timedelay){
	  GPIO_SetBits(GPIOC, GPIO_Pin_13); // Ghi 1 ra
		delay_ms(timedelay);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		delay_ms(timedelay);		
}

