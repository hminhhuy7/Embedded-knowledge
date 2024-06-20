#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_tim.h"
#include "kalman.h"
#include "stdint.h"


void RCC_Config(){
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA| RCC_APB2Periph_ADC1, ENABLE);
     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

void GPIO_Config(){
     GPIO_InitTypeDef GPIO_InitStruct;
     GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
     GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
     GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void TIM_Config(){
	  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; // 72Mhz /(1, 2, 4) = ...
	  TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1; // scaling again 72Mhz / 7200 = ... 
	  TIM_TimeBaseInitStructure.TIM_Period = 0xFFFF - 1; // using in interupt for overflow time
	  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	  
	  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	  TIM_Cmd(TIM2, ENABLE);
	  
}


void ADC_Config(){
	  ADC_InitTypeDef ADC_InitStruct;
	  ADC_InitStruct.ADC_Mode = ADC_Mode_Independent; // don kenhh hay da kenh hay dung trigger
	  ADC_InitStruct.ADC_NbrOfChannel = 1; // so kenh duoc su dung
	  ADC_InitStruct.ADC_ScanConvMode = DISABLE; // quet qua tat ca cac kenh don kenh k dung
	  ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None; // dung trigger khong
    ADC_InitStruct.ADC_ContinuousConvMode = ENABLE; // doc du lieu chuyen doi lien tuc or 1 lan
	  ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right; // 12 bit ben trai hay phai
	
	  ADC_Init(ADC1, &ADC_InitStruct);
	  ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5); // thoi gian lay mau va thu tu 
    ADC_Cmd(ADC1, ENABLE);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	
}

void delay_ms(int timedelay){
	  TIM_SetCounter(TIM2,0);
	  while (TIM_GetCounter(TIM2) < timedelay*10) {};	// 1x = 0.1ms => timedelay*10 <=> ms
}

uint16_t val = 0, valupdate = 0;
float sum = 0;
int main(){
	  RCC_Config();
	  TIM_Config();
	  GPIO_Config();
	  ADC_Config();
	  //SimpleKalmanFilter(1, 2, 0.001);
	  while(1){
       for(int i=0; i<10; i++){
       val = ADC_GetConversionValue(ADC1);
       delay_ms(10);
       sum += val;
        }
        sum = sum / 10;
				delay_ms(100);
				sum = 0;
				
//				val = ADC_GetConversionValue(ADC1);
//        valupdate = (float)updateEstimate((float)val);
//        delay_ms(100);
				
				
}
	
	
}