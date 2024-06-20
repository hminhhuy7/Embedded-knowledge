#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"

#define TX_Pin GPIO_Pin_9
#define RX_Pin GPIO_Pin_10
#define UART_GPIO GPIOA

void RCC_Config(){
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_USART1, ENABLE);
     RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

void GPIO_Config(){
     GPIO_InitTypeDef GPIOInitStruct;
     GPIOInitStruct.GPIO_Pin = RX_Pin;
     GPIOInitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
     GPIO_Init(GPIOA, &GPIOInitStruct);
//
     GPIOInitStruct.GPIO_Pin = TX_Pin;
     GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
     GPIOInitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
     GPIO_Init(GPIOA, &GPIOInitStruct);
}

void UART_Config(){
	   USART_InitTypeDef USART_InitStructure;
	   USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; // che do
	   USART_InitStructure.USART_BaudRate = 9600; // toc do baud
	   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // dung them dong bo nhung khong dung UART
	   USART_InitStructure.USART_WordLength = USART_WordLength_8b; // cau hinh so bit truyen
	   USART_InitStructure.USART_StopBits = USART_StopBits_1; // bit stop keo len 1 trong khoang
	   USART_InitStructure.USART_Parity = USART_Parity_No; // bit chan le
	   
	   USART_Init(USART1, &USART_InitStructure);
     USART_Cmd(USART1,ENABLE);	   
}

void UART_SendChar(USART_TypeDef *USARTx, char data){
     USARTx->DR = 0x00;
     USART_SendData(USARTx, data); //
     while(!USART_GetFlagStatus(USARTx, USART_FLAG_TXE));
}

void UART_SendString(USART_TypeDef *USARTx, char *str){
     while(*str)
     {
        UART_SendChar(USARTx, *str);
        str++;
     }
}
char UART_ReceiveChar(USART_TypeDef *USARTx){
     USARTx->DR = 0x00;
     char tmp = 0x00;
     tmp = USART_ReceiveData(USARTx);
      while(USART_GetFlagStatus(USARTx, USART_FLAG_RXNE)==RESET);
     return tmp;
}
int main(void){
	  RCC_Config();
	  GPIO_Config();
	  UART_Config();
	  while (1){
			UART_SendChar(USART1,'a');
			
			
		}
	  
	
	
}
