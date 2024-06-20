#include "stm32f10x.h"
#include "spi.h"
#include "rfid_rc522.h"
#include "uart.h"
#include "tim.h"
#include "stdio.h"

#define BLOCK_ADDR 8 
#define	uchar	uint8_t
uchar status;
uchar str[MAX_LEN];
uchar blockData[16];
uchar newData[16];
uchar i ;

int main(){
	  RFID_RC522_Config();
	  UART2_Config();
	  MFRC522_Init();
	  TIM_Config();
	   while (1) {
        // Tìm th?
        status = MFRC522_Request(PICC_REQIDL, str);
        if (status == MI_OK) {
            // Phát hi?n th?, th?c hi?n ch?ng va ch?m
            status = MFRC522_Anticoll(str);
            if (status == MI_OK) {
                // Ch?n th?
                status = MFRC522_SelectTag(str);
                if (status != 0) {
                    // Xác th?c th? v?i key A
                    uchar defaultKey[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
                    status = MFRC522_Auth(PICC_AUTHENT1A, BLOCK_ADDR, defaultKey, str);
                    if (status == MI_OK) {
                        // Ð?c d? li?u t? kh?i
                        status = MFRC522_Read(BLOCK_ADDR, blockData);
                        if (status == MI_OK) {
                            // Hi?n th? d? li?u ban d?u qua UART
                            USART_SendString("Original Data: ");
                            for (i = 0; i < 16; i++) {
                                char buffer[4]; // Buffer d? ch?a giá tr? du?i d?ng chu?i
                                snprintf(buffer, sizeof(buffer), "%02X ", blockData[i]);
                                USART_SendString(buffer);
                            }
                            USART_SendString("\r\n");

                            // Thay d?i d? li?u, ví d?: tang giá tr? byte d?u tiên
                            memcpy(newData, blockData, 16);
                            newData[0] += 1;

                            // Ghi d? li?u m?i vào th?
                            status = MFRC522_Write(BLOCK_ADDR, newData);
                            if (status == MI_OK) {
                                // Ð?c l?i d? li?u sau khi ghi
                                status = MFRC522_Read(BLOCK_ADDR, blockData);
                                if (status == MI_OK) {
                                    // Hi?n th? d? li?u m?i qua UART
                                    USART_SendString("Modified Data: ");
                                    for (i = 0; i < 16; i++) {
                                        char buffer1[4]; // Buffer d? ch?a giá tr? du?i d?ng chu?i
                                         snprintf(buffer1, sizeof(buffer1), "%02X ", blockData[i]);
                                      USART_SendString(buffer1);
                                    }
                                    USART_SendString("\r\n");
                                } else {
                                    USART_SendString("Error reading block after write.\r\n");
                                }
                            } else {
                                USART_SendString("Error writing block.\r\n");
                            }
                        } else {
                            USART_SendString("Error reading block.\r\n");
                        }
                    } else {
                        USART_SendString("Authentication error.\r\n");
                    }
                } else {
                    USART_SendString("Card selection error.\r\n");
                }
            } else {
                USART_SendString("Anti-collision error.\r\n");
            }
        }

        // Delay for a while
        delay_ms(1000); // Gi? d?nh b?n dã có hàm delay_ms
    }
}
	  


