#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_tim.h"
#include "stdint.h"


#define SPI1_NSS GPIO_Pin_4
#define SPI1_SCK GPIO_Pin_5
#define SPI1_MISO GPIO_Pin_6
#define SPI1_MOSI GPIO_Pin_7
#define SPI1_GPIO GPIOA

void RCC_Config(void);
void GPIO_Cofig(void);
void TIM_Config(void);
void SPI_Config(void);
uint8_t SPI_Receive1Byte(void);
void delay_ms(int timedelay);
uint8_t array[7];


void RCC_Config(void){
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE);
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

void GPIO_Cofig(void){
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = SPI1_NSS| SPI1_SCK| SPI1_MISO| SPI1_MOSI;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	
    GPIO_Init(SPI1_GPIO, &GPIO_InitStructure);
}

void TIM_Config(void){
	  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; // 72Mhz /(1, 2, 4) = ...
	  TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1; // scaling again 72Mhz / 7200 = ... 
	  TIM_TimeBaseInitStructure.TIM_Period = 0xFFFF - 1; // using in interupt for overflow time
	  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	  
	  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	  TIM_Cmd(TIM2, ENABLE);
	  
}

void SPI_Config(void){
	  SPI_InitTypeDef SPI_InitStructure;
	  SPI_InitStructure.SPI_Mode = SPI_Mode_Slave; 
	  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64; // scale 72Mhz cua STM32
	  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High; // Quy dinh SCK 0/1
	  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; // 0: dua bit truoc roi goi xung, 1: goi cung roi dua bit vao
	  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; // Kich thuoc data
	  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; // chuyen du lieu theo trong so cao hay thap
	  SPI_InitStructure.SPI_CRCPolynomial = 7; // bit kiem tra do toan ven cua data
	  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; // SS bang Soft/ Hard
	
	  SPI_Init(SPI1, &SPI_InitStructure);
	  SPI_Cmd(SPI1, ENABLE);
}

uint8_t SPI_Receive1Byte(void){
    uint8_t temp;
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY)== 1);
      temp = (uint8_t)SPI_I2S_ReceiveData(SPI1);
    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE)== 0);
    return temp;
}


void delay_ms(int timedelay){
	  TIM_SetCounter(TIM2,0);
	  while (TIM_GetCounter(TIM2) < timedelay*10) {}	// 1x = 0.1ms => timedelay*10 <=> ms
}

int main(void){
	  RCC_Config();
	  GPIO_Cofig();
	  SPI_Config();
    TIM_Config();	
	  //while(1){
      while(GPIO_ReadInputDataBit(SPI1_GPIO, SPI1_NSS));
      if(GPIO_ReadInputDataBit(SPI1_GPIO, SPI1_NSS)==0){
         for(int i = -2; i < 8; i++){					
          array[i] = SPI_Receive1Byte();
       }
     // }
   }
}
