

#ifndef SPI_H
#define SPI_H

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"



#define MFRC522_CS_GPIO		GPIOA
#define MFRC522_CS_PIN		GPIO_Pin_4
#define MFRC522_CS_RCC		RCC_APB2Periph_GPIOA

#define MFRC522_RST_GPIO	GPIOA
#define MFRC522_RST_PIN		GPIO_Pin_3
#define MFRC522_RST_RCC		RCC_APB2Periph_GPIOA

#define MFRC522_SPI							SPI1
#define MFRC522_SPI_GPIO				GPIOA					// 
#define MFRC522_SCK_PIN					GPIO_Pin_5		// SCK
#define MFRC522_MISO_PIN				GPIO_Pin_6		// MISO
#define MFRC522_MOSI_PIN				GPIO_Pin_7		// MOSI
#define MFRC522_SPI_GPIO_RCC		RCC_APB2Periph_GPIOA
#define MFRC522_SPI_RCC					RCC_APB2Periph_SPI1


void RFID_RC522_Config();
#endif