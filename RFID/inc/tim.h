
#ifndef TIM_H
#define TIM_H

#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"


void TIM_Config();
void delay_ms(int timedelay);
void blinkLed(int timedelay);
#endif