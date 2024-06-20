   #include "main.h"
#include "defines.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_fatfs.h"

#define MAX_LEN 16
#define MAX_CARDS 5

uchar status;
uchar str[MAX_LEN]; // Max_LEN = 16
uchar serNum[5];
char myString[100];
uchar check,check2;
uchar Key_Cards[MAX_CARDS][5]; // Mang luu tru du lieu the tu the SD
uchar test [5] ={0xf3, 0xfa, 0x9c, 0xf7, 0x62};
FATFS FatFs;
FIL fil;
FRESULT fr;

// Ham so sanh hai mang
int compareArrays(const uchar *arr1, const uchar *arr2, int size) {
    for (int i = 0; i < size; ++i) {
        if (arr1[i] != arr2[i]) {
            return 0; // Hai mang khong giong nhau
        }
    }
    return 1; // Hai mang giong nhau
}

// Ham hien thi noi dung cua tep
void showFileContent() {
    f_rewind(&fil); // Di chuyen con tro ve dau tep
    char ch;
    UINT bytesRead;
    while (f_read(&fil, &ch, 1, &bytesRead) == FR_OK && bytesRead > 0) { // Doc tung ky tu va hien thi
        USART_SendChar(ch); // Gui ky tu qua UART
    }
}

int main() {
    // Khoi tao phan cung
    SPIRC552_Config(); // Cau hinh RFID
    TIMDelay_Config(); // Cau hinh ham tre
    UART1_Config(); // Cau hinh UART
    MFRC522_Init(); // Khoi tao RFID

    // Mount he thong tep
    fr = f_mount(&FatFs, "", 1);
    if (fr != FR_OK) {
        return 0;
    }

    // Mo tep "cards.txt" de doc
    fr = f_open(&fil, "cards.txt", FA_READ);
    if (fr != FR_OK) {
        return 0;
    }

    // Hien thi noi dung cua tep "cards.txt"
    showFileContent();

    // Doc du lieu the tu tep
    for (int i = 0; i < MAX_CARDS; ++i) {
        UINT bytesRead; // So byte da doc
        fr = f_read(&fil, Key_Cards[i], sizeof(serNum), &bytesRead);
        if (fr != FR_OK || bytesRead != sizeof(serNum)) {
            break; // Dung viec doc neu co loi hoac EOF
        }
    }

    // Dong tep
    f_close(&fil);

    while (1) {
        // Cho the duoc dua vao
        Delay_ms(1000); // Cho 1 giay truoc khi doc the
        status = MFRC522_Request(PICC_REQIDL, str);    
        if (status == MI_OK) {	
            sprintf(myString,"Your card's number are: %x, %x, %x, %x, %x \r\n",serNum[0], serNum[1], serNum[2], serNum[3],serNum[4]);
						USART_SendString(myString);
            status = MFRC522_Anticoll(str);
            memcpy(serNum, str, sizeof(serNum));
						check == 1;
						check2 == 1;
            // Reset bien cardMatched
            int cardMatched = 0;

            USART_SendString("The ID: ");
            for (int k = 0; k < sizeof(serNum); ++k) {
                sprintf(myString, "%02X ", serNum[k]); // Chuyen tu so sang dang hex
                USART_SendString(myString);
            }
            USART_SendString("\n");
 
            // So sanh ID the voi cac ID trong the SD
             for (int j = 0; j < MAX_CARDS; ++j) {
                if (compareArrays(serNum, Key_Cards[j], sizeof(serNum))) {
                    
                    sprintf(myString, "ID the khop tai vi tri %d\n", j);
                    USART_SendString(myString);
                    cardMatched = 1;  
                    break; 
                }
								if (!cardMatched) {
                USART_SendString("ID the khong khop voi du lieu SD\n");
								}
            }

            
        }
		if(check == 1||check2 ==1)
				{
				
					check = 0;
					check2 = 0;
					Delay_ms(1000);
					set_pwm(1500);
					Delay_ms(2000);
					set_pwm(500);
					Delay_ms(1000);
				}
    }

    return 0;
}
