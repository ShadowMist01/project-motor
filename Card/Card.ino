#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9

// Accepted card UIDs live in a local, Git-ignored header (see
// card_config.example.h). Without it the placeholders below match no real
// card, so every card is denied.
#if defined(__has_include)
#if __has_include("card_config.h")
#include "card_config.h"
#endif
#endif
#ifndef AUTHORIZED_UID_1
#define AUTHORIZED_UID_1 "00 00 00 00"
#define AUTHORIZED_UID_2 "00 00 00 00 00 00 00"
#endif

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
double tap;
int x = 0;
int nyala = 0;
void setup()
{
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
}
void loop()
{
  // Look for new cards
    if ( mfrc522.PICC_IsNewCardPresent() == true)
    {
      if ( mfrc522.PICC_ReadCardSerial() == true)
      {
        if (x == 0)
        {
          tap = millis();
        }
        //Serial.print(tap);
        Serial.print("UID tag :");
        String content = "";
        for (byte i = 0; i < mfrc522.uid.size; i++)
        {
          Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
          Serial.print(mfrc522.uid.uidByte[i], HEX);
          content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
          content.concat(String(mfrc522.uid.uidByte[i], HEX));
        }
        content.toUpperCase();
        if (content.substring(1) == AUTHORIZED_UID_1 && x == 0 && nyala == 0 || content.substring(1) == AUTHORIZED_UID_2 && x == 0 && nyala == 0) //change here the UID of the card/cards that you want to give access
        {
          digitalWrite(2, HIGH);
          Serial.println(" Authorized access");
          x = 1;
          delay(4000);
        }
        else if (content.substring(1) == AUTHORIZED_UID_1 && x == 1 && nyala == 0 || content.substring(1) == AUTHORIZED_UID_2 && x == 1 && nyala == 0) //change here the UID of the card/cards that you want to give access
        {
          digitalWrite(3, HIGH);
          Serial.println(" Authorized access");
        }
        else if (content.substring(1) == AUTHORIZED_UID_1 && x == 1 && nyala == 1 || content.substring(1) == AUTHORIZED_UID_2 && x == 1 && nyala == 1)
        {
          digitalWrite(2, LOW);
          digitalWrite(3, LOW);
          x = 0 ;
          nyala = 0;
          delay(1000);
        }
        else
        {
          //digitalWrite(3, HIGH);
          Serial.println(" Access denied");
          //delay(3000);
        }
      }
    }
    if(millis() - tap > 6000 && x == 1)
    {
      nyala = 1;
    }
    
    // Select one of the cards

    //Show UID on serial monitor
}
