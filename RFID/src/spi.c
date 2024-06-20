#include "spi.h"

void RFID_RC522_Config(){	   
	   RCC_APB2PeriphClockCmd(MFRC522_SPI_GPIO_RCC | MFRC522_SPI_RCC, ENABLE);
	
	   GPIO_InitTypeDef GPIO_InitStruct;
	   GPIO_InitStruct.GPIO_Pin = MFRC522_SCK_PIN | MFRC522_MISO_PIN | MFRC522_MOSI_PIN | MFRC522_CS_PIN;
	   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	   GPIO_Init(MFRC522_SPI_GPIO, &GPIO_InitStruct);
	
	   	
	   GPIO_InitStruct.GPIO_Pin = MFRC522_RST_PIN;
	   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	   GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	   GPIO_Init(MFRC522_SPI_GPIO, &GPIO_InitStruct);
	
	   SPI_InitTypeDef SPI_InitStructure;
	   SPI_InitStructure.SPI_Mode = SPI_Mode_Master; 
	   SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	   SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
	   SPI_InitStructure.SPI_CPOL = SPI_CPOL_High; 
	   SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge; 
	   SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b; 
	   SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; 
	   SPI_InitStructure.SPI_CRCPolynomial = 7; 
	   SPI_InitStructure.SPI_NSS = SPI_NSS_Soft; 
		 
	   SPI_Init(MFRC522_SPI, &SPI_InitStructure);
	   SPI_Cmd(MFRC522_SPI, ENABLE);
}

