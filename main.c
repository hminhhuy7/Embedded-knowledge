#include "stm32f10x.h"

void TIM1_CH1_PWM_Config(void) {
    // B?t Clock cho TIM1 và GPIOA
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

    // C?u hình PA8 cho d?u ra PWM
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // C?u hình Timer
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_Prescaler = 72 - 1; // 72 MHz / (719 + 1) = 100 kHz
    TIM_TimeBaseInitStruct.TIM_Period = 20000 - 1; // 20 ms period for PWM
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);

    // C?u hình kênh PWM
    TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse = 500 - 1; // Mid-position (1.5 ms pulse)
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
    TIM_OC4Init(TIM2, &TIM_OCInitStruct);

    // B?t Timer và d?u ra PWM
    TIM_Cmd(TIM2, ENABLE);
    TIM_CtrlPWMOutputs(TIM2, ENABLE);
}

void set_pwm(uint16_t angle) {
    TIM_SetCompare4(TIM2, angle);
}

void delay_ms(int ms) {
    // Hàm delay don gi?n
    for (int i = 0; i < ms * 8000; i++) {
        __NOP();
    }
}

int main(void) {
    TIM1_CH1_PWM_Config();

    while (1) {
        // Ði?u ch?nh giá tr? PWM d? di?u khi?n servo
        set_pwm(1000); // 1 ms pulse (0 degrees)
        delay_ms(1000);

        //set_pwm(1500); // 1.5 ms pulse (90 degrees, mid-position)
        //delay_ms(1000);

        set_pwm(2000); // 2 ms pulse (180 degrees)
        delay_ms(1000);
    }
}
