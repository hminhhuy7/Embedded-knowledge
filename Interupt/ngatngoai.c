#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"

void RCC_Config(){
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); // chuc nang thay the
}

void GPIO_Config(){
     GPIO_InitTypeDef GPIOInitStruct;
//
     GPIOInitStruct.GPIO_Mode = GPIO_Mode_IPU;
     GPIOInitStruct.GPIO_Pin = GPIO_Pin_0;
     GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
     GPIO_Init(GPIOA, &GPIOInitStruct);
}

void EXTI_Config(){ // cau hinh vector ngat ngoai
	  EXTI_InitTypeDef EXTI_InitStruct;
	  EXTI_InitStruct.EXTI_Line = EXTI_Line0; // chon line ngat
	  EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt; // thuc thi ham ngat hoac su kien
	  EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling; // canh ngat cao hay thap
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
}

void NVIC_Config(){ // cau hinh tham so ngat va trinh quan ly ngat 
	  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // do uu tien 4 bits 2-2
	  NVIC_InitTypeDef NVIC_InitStruct;
	  NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn; // cau hinh line ngat 
	  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x01; // cang thap do uu tien cang cao
	  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
}

void EXTI0_IRQHandler(){ // ham thuc hien ngat
	   if(EXTI_GetITStatus(EXTI_Line0) != RESET) //kiem tra co co ngat hay khong
     { 
			 // do something;
		 }
     EXTI_ClearITPendingBit(EXTI_Line0); // xoa co ngat de thuc hien cac lan tiep theo
	 }
int main(){

}