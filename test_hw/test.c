#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"

void delay_ms(int timedelay){
	  TIM_SetCounter(TIM2,0);
	  while (TIM_GetCounter(TIM2) < timedelay*10) {};	// 1x = 0.1ms => timedelay*10 <=> ms
}


//Cau hinh RCC cap xung cac bus lien ket voi ngoai vi
void RCC_Config(){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA, ENABLE);	
}

//Cai hinh TIM
void TIM_Config(){
	  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; // 72Mhz /(1, 2, 4) = ...
	  TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1; // scaling again 72Mhz / 7200 = ... 
	  TIM_TimeBaseInitStructure.TIM_Period = 0xFFFF - 1; // using in interupt for overflow time
	  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	  
	  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	  TIM_Cmd(TIM2, ENABLE);
	  
}

//Cau hinh GPIO
void GPIO_Config(){
	  GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
    GPIO_Init(GPIOC, &GPIO_InitStructure);	
	  
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5
                                  | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 
	                                 | GPIO_Pin_12 | GPIO_Pin_15 ; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5
                                  | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 
	                                 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 ; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
}

int main(){	
	RCC_Config();
	TIM_Config();
	GPIO_Config();

	while(1){
		GPIO_SetBits(GPIOA, GPIO_Pin_0);
	  GPIO_SetBits(GPIOA, GPIO_Pin_1);
	  GPIO_SetBits(GPIOA, GPIO_Pin_2);
	  GPIO_SetBits(GPIOA, GPIO_Pin_3);
	  GPIO_SetBits(GPIOA, GPIO_Pin_4);
	  GPIO_SetBits(GPIOA, GPIO_Pin_5);
	  GPIO_SetBits(GPIOA, GPIO_Pin_6);
	  GPIO_SetBits(GPIOA, GPIO_Pin_7);
	  GPIO_SetBits(GPIOA, GPIO_Pin_8);
	  GPIO_SetBits(GPIOA, GPIO_Pin_9);
	  GPIO_SetBits(GPIOA, GPIO_Pin_10);
	  GPIO_SetBits(GPIOA, GPIO_Pin_11);
	  GPIO_SetBits(GPIOA, GPIO_Pin_12);
	  GPIO_SetBits(GPIOA, GPIO_Pin_15);
		
		GPIO_SetBits(GPIOB, GPIO_Pin_0);
	  GPIO_SetBits(GPIOB, GPIO_Pin_1);	  
	  GPIO_SetBits(GPIOB, GPIO_Pin_3);
	  GPIO_SetBits(GPIOB, GPIO_Pin_4);
	  GPIO_SetBits(GPIOB, GPIO_Pin_5);
	  GPIO_SetBits(GPIOB, GPIO_Pin_6);
	  GPIO_SetBits(GPIOB, GPIO_Pin_7);
	  GPIO_SetBits(GPIOB, GPIO_Pin_8);
	  GPIO_SetBits(GPIOB, GPIO_Pin_9);
	  GPIO_SetBits(GPIOB, GPIO_Pin_10);
	  GPIO_SetBits(GPIOB, GPIO_Pin_11);
	  GPIO_SetBits(GPIOB, GPIO_Pin_12);
	  GPIO_SetBits(GPIOB, GPIO_Pin_13);
	  GPIO_SetBits(GPIOB, GPIO_Pin_14);
	  GPIO_SetBits(GPIOB, GPIO_Pin_15);

    GPIO_SetBits(GPIOC, GPIO_Pin_13);
	  GPIO_SetBits(GPIOC, GPIO_Pin_14);
	  GPIO_SetBits(GPIOC, GPIO_Pin_15);
		
		
	}
	

	
}
