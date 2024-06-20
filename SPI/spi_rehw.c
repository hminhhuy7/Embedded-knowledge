#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_tim.h"
#include "stdint.h"


#define SPI_NSS_Pin GPIO_Pin_0
#define SPI_SCK_Pin GPIO_Pin_1
#define SPI_MISO_Pin GPIO_Pin_2
#define SPI_MOSI_Pin GPIO_Pin_3
#define SPI_GPIO GPIOA
#define SPI_RCC RCC_APB2Periph_GPIOA
uint8_t array[7];


void RCC_Config(void){
    RCC_APB2PeriphClockCmd(SPI_RCC, ENABLE);
    //RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

void GPIO_Config(){
   GPIO_InitTypeDef GPIO_InitStructure;
   GPIO_InitStructure.GPIO_Pin = SPI_NSS_Pin ;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(SPI_GPIO, &GPIO_InitStructure);
	
   GPIO_InitStructure.GPIO_Pin = SPI_SCK_Pin | SPI_MOSI_Pin ;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(SPI_GPIO, &GPIO_InitStructure);
}

//void delay_ms(int timedelay){
//    TIM_SetCounter(TIM2,0);
//	  while (TIM_GetCounter(TIM2) < timedelay*10) {}	// 1x = 0.1ms => timedelay*10 <=> ms
//}

//void Clock(){
//   GPIO_WriteBit(SPI_GPIO, SPI_SCK_Pin, Bit_SET);
//   delay_ms(4);
//   GPIO_WriteBit(SPI_GPIO, SPI_SCK_Pin, Bit_RESET);
//   delay_ms(4);
//}

//void SPI_Init(){
//   GPIO_WriteBit(SPI_GPIO, SPI_SCK_Pin, Bit_RESET);
//   GPIO_WriteBit(SPI_GPIO, SPI_NSS_Pin, Bit_SET);
//   GPIO_WriteBit(SPI_GPIO, SPI_MISO_Pin, Bit_RESET);
//   GPIO_WriteBit(SPI_GPIO, SPI_MOSI_Pin, Bit_RESET);
//}

uint8_t SPI_Slave_Receive(){
   //uint8_t u8Mask = 0x80;
   uint8_t dataReceive =0x00;
   uint8_t temp = 0x00, i=0;
   while(GPIO_ReadInputDataBit(SPI_GPIO, SPI_NSS_Pin));
   while(!GPIO_ReadInputDataBit(SPI_GPIO, SPI_SCK_Pin));
   for(i=0; i<8;i++)
   {
      if(GPIO_ReadInputDataBit(SPI_GPIO, SPI_SCK_Pin)){
      while (GPIO_ReadInputDataBit(SPI_GPIO, SPI_SCK_Pin))
      temp = GPIO_ReadInputDataBit(SPI_GPIO, SPI_MOSI_Pin);	
      dataReceive = dataReceive << 1;	
			dataReceive = dataReceive | temp;			
					
      
			
   }
   while(!GPIO_ReadInputDataBit(SPI_GPIO, SPI_SCK_Pin));
   }
    return dataReceive;
}

int main(){
    RCC_Config();
    GPIO_Config();
    //SPI_Init();
    while(1)
    {      
			//if(GPIO_ReadInputDataBit(SPI_GPIO, SPI_NSS_Pin) == 0){
			for(int i=0; i < 7; i++){
        array[i] = SPI_Slave_Receive();
        //delay_ms(10);
			}
     }
	 //}	
}
