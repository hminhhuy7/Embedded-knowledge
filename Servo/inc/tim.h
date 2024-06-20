

#ifndef TIM_H
#define TIM_H

#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_pwr.h"




void TIM_Config();
void TIMPWM_Config();
void delay_ms(int timedelay);
void set_pwm(uint16_t angle);
void blinkLed(int timedelay);
#endif