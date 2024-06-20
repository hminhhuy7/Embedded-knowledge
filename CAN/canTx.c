#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_can.h"

uint16_t id = 0x234;
uint32_t ID;
uint8_t data[8] = {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80};
uint8_t TestArray[8];

void RCC_Config(){
	   RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	   RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 
	
}

void GPIO_Config(){
	  GPIO_InitTypeDef GPIO_InitStruct;
	  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
	  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	  GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	  GPIO_Init(GPIOA, &GPIO_InitStruct); 
}

void CAN_Config(){
   	CAN_InitTypeDef CAN_InitStruct;
	  CAN_InitStruct.CAN_TTCM = DISABLE; // dinh thoi gian truyen du lieu, disable: truyen thu cong bang ham
	  CAN_InitStruct.CAN_ABOM = DISABLE; // quan li ngat bus tu dong neu co loi se ngat 
	  CAN_InitStruct.CAN_AWUM = DISABLE; // can co che do sleep mode de tiet kien nang luong va cai nay se goi khi co du lieu truyen toi
	  CAN_InitStruct.CAN_NART = DISABLE; // co truyen lai du lieu bi loi hay khong 
	  CAN_InitStruct.CAN_RFLM = DISABLE; // khoa bo dem khi day 
	  CAN_InitStruct.CAN_TXFP = DISABLE; // dis: uu tien goi tin co id thap de truyen nhan. nguoc lai thi theo thu tu
	  CAN_InitStruct.CAN_Mode = CAN_Mode_Normal;
	
	 // cau hinh toc do cho Can
	  CAN_InitStruct.CAN_Prescaler = 4;
	  CAN_InitStruct.CAN_SJW = CAN_SJW_1tq; // thoi gian tr phan cung
	  CAN_InitStruct.CAN_BS1 = CAN_BS1_3tq;
	  CAN_InitStruct.CAN_BS2 = CAN_BS2_5tq;
}

void CAN_Filter_Config(){
	   CAN_FilterInitTypeDef FilterInit;
	   FilterInit.CAN_FilterNumber = 0 ; // chon so filter muon loc
	   FilterInit.CAN_FilterMode = CAN_FilterMode_IdMask ; // dung mask de loc id
	   FilterInit.CAN_FilterScale = CAN_FilterScale_32bit;// kich thuoc bo loc
	   FilterInit.CAN_FilterMaskIdHigh = 0xFFE0;
	   FilterInit.CAN_FilterMaskIdLow = 0x0000;
	   FilterInit.CAN_FilterIdHigh =  id << 5; // id 11 bit phai dich qua 5 bit
	   FilterInit.CAN_FilterIdLow = 0x0000;
	   FilterInit.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;
	   FilterInit.CAN_FilterActivation = ENABLE;
	
	   CAN_FilterInit (&FilterInit);
	   
}

void Transmmit(uint8_t *data, uint8_t len){
	  CanTxMsg TxMessage;
    TxMessage.StdId = id; // 11bit ID voi che do std
    TxMessage.ExtId = 0x00;
    TxMessage.RTR = CAN_RTR_DATA;
    TxMessage.IDE = CAN_ID_STD;
    TxMessage.DLC = len;
      for (int i = 0; i < len; i++)
      {
         TxMessage.Data[i] = data[i];
       }
      CAN_Transmit(CAN1, &TxMessage);
}

void Receive(){
	   CanRxMsg RxMessage;
     while (CAN_MessagePending(CAN1, CAN_FIFO0) <1 );
     CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
     ID = RxMessage.StdId;
     for (int i = 0; i < RxMessage.DLC; i++)
     {
      TestArray[i] = RxMessage.Data[i];
     }
}

int main(){
	
	  RCC_Config();
	  GPIO_Config();
	  CAN_Config();
	
	  Transmmit(data, 8);
}



