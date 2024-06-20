#include "stm32f10x.h"
#include "tim.h"

int main (){
	
	 TIM_Config();
	 TIMPWM_Config();
	while(1){
		
		
		set_pwm(1000);
		delay_ms(500);
	
		set_pwm(2000);
		delay_ms(1000);		
	}
}