#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <LiquidCrystal_I2C.h>

//LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

//RFID
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

//Servo
Servo servo1; //define servo name
//Servo servo2;
//Servo servo3;
//Servo servo4;
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus

  //LCD
  lcd.begin();
  lcd.backlight();
  lcd.print("1. Sandwich 40BDT");
  lcd.setCursor(0, 1);
  lcd.print("2. Fried Rice 80BDT");
  lcd.setCursor(0, 2);
  lcd.print("3. Noodles 30BDT");
//  lcd.setCursor(0, 3);
//  lcd.print("3. Noodles 30BDT");
//  lcd.setCursor(0, 4);
//  lcd.print("3. Noodles 30BDT");


    
  
  
  //RFID
  mfrc522.PCD_Init();   // Initiate MFRC522
  
  //Servo
  servo1.attach(7); //servo pin
//  servo2.attach(6);
//  servo3.attach(5);
//  servo4.attach(4);
}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  content.toUpperCase();



  if (content.substring(1) == "1A 68 0B 0B") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Message : Authorized access");
    servo1.write(90);
    delay(2000);
    servo1.write(0);
  }
 
 else   {
    Serial.println(" Access denied");
  }
}
