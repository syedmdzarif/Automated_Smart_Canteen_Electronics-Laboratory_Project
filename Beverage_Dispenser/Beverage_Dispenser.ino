#include <Wire.h> 
#include <Servo.h> 
#include <MFRC522.h>

//Servo
Servo servo1;

//RFID
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.

int ir1out = 7;
int ir2out = 6;

void setup() {
  
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus

  //IR
  pinMode(ir1out, INPUT);
  pinMode(ir2out, INPUT);

  //RFID
  mfrc522.PCD_Init();   // Initiate MFRC522

  //Servo
  servo1.attach(5);
  servo1.write(90);
}

void loop(){ 
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



  if (content.substring(1) == "93 F1 C3 0B") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Message : Authorized access");


    Serial.print("ir1 : ");
    Serial.println(digitalRead(ir1out));
    Serial.print("ir2 : ");
    Serial.println(digitalRead(ir2out));
    
    if (digitalRead(ir1out)==0 && digitalRead(ir2out)==1){
      servo1.write(90);
      delay(1000);
      servo1.write(0);
      
    }
    else if (digitalRead(ir1out)==0 && digitalRead(ir2out)==0){
      servo1.write(90);
      delay(3000);
      servo1.write(0);
    }
  
  
  }
 else   {
    
    Serial.println(" Access denied");
  }
  servo1.write(0);
}
