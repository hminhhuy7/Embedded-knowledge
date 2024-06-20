#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_tim.h"
#include "stdint.h""

#define I2C_SCL GPIO_Pin_6
#define I2C_SDA GPIO_Pin_7
#define I2C1_GPIO GPIOB
uint8_t data[7] = {3, 5, 7, 9, 2, 4, 6};

void RCC_Config(void){
	   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	   RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);
}


void GPIO_Config(void) {
   GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void I2C_Config(void){
	  I2C_InitTypeDef I2C_InitStructure;
	  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C; // Fast mode
	  I2C_InitStructure.I2C_ClockSpeed = 200000; // Cau hinh toc do Slow max 100khz, Fast max 400khz
	  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2; // Cau hinh chu ki xung thap/cao = ...
	  I2C_InitStructure.I2C_OwnAddress1 = 0x00; // Cau hinh dia chi cho slave muon giao tiep master = 0x00
	  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable; // Su dung Ack hay khong
	  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit; // cau hinh dia chi slave 7 or 10 bit	 

    I2C_Init(I2C1, &I2C_InitStructure);
	  I2C_Cmd(I2C1, ENABLE);	  
}

void Send_I2C_Data(uint8_t data){
     I2C_SendData(I2C1, data);
     while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
}

uint8_t Read_I2C_Data(){
    uint8_t data = I2C_ReceiveData(I2C1);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));
    return data;
}

int main(void){
	  RCC_Config();
	  GPIO_Config();
	  I2C_Config();
	  
	  while(1){
			I2C_GenerateSTART(I2C1, ENABLE);
     //Waiting for flag
      while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
      I2C_Send7bitAddress(I2C1, 0x01, I2C_Direction_Transmitter);			
      //And check the transmitting
      while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
			for (int i = 0; i < 8; i++){
				Send_I2C_Data(data[i]);
			}
	  }
	  
	
}
