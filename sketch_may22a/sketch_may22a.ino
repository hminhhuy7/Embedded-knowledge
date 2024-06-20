#include <SPI.h>
#include <RFID.h>

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN, RST_PIN);

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
}

void loop()
{
  if (rfid.isCard()) {
    Serial.println("Find the card!");
    if (rfid.readCardSerial()) {
      Serial.print("The card's number is  : ");
      rfid.
      Serial.print(rfid.serNum[3]);
      // Serial.print(rfid.serNum[1],HEX);
      // Serial.print(rfid.serNum[2],HEX);
      // Serial.print(rfid.serNum[3],HEX);
      // Serial.print(rfid.serNum[4],HEX);
      Serial.println(" ");
    }
    rfid.selectTag(rfid.serNum);
  }
  rfid.halt();
}