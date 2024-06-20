
#ifndef UART_H
#define UART_H

#include "stm32f10x_usart.h"


void UART2_Config(void);
void USART_SendChar(char data);
void USART_SendString(char *str);


#endif