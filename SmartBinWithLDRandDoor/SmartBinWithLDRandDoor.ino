#include <Servo.h>
Servo servo;
Servo servoDoor;

//Sonar
const int echoPin = 13;
const int trigPin = 12;

//Signal
const int ledPin = 3;
const int buzzer = 10;

//IR
const int irIn = 9;
const int irOut = 8;

//
const int ServoIn = 7;

//defines variables
long duration;
int distance;
int safetyDistance;
int irDistance;
int trigger_distance;



#define irOutDoor 2

//ldr
#define ldrOUT  A0
int leddoor = 5;


void setup() {
  //Sonar
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(HIGH, 1);
  digitalWrite(1, HIGH);
  

  //Output
  pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);

  //IR - Bin
  pinMode(irIn, OUTPUT);
  pinMode(irOut, INPUT);

  //IR - Door

  //LDR
  pinMode(leddoor,OUTPUT);

  //Servo
  pinMode(ServoIn, OUTPUT);
  
  servoDoor.attach(3);
  servo.attach(6);
  servoDoor.attach(3);
  Serial.begin(9600); // Starts the serial communication
}


void loop() {

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delay(10);
digitalWrite(trigPin, LOW);



// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
distance= duration*0.034/2;

trigger_distance = 4;

  //IR - Door
  if(digitalRead(irOutDoor)==0){
    servoDoor.write(90);
  }
  else{
    servoDoor.write(0);
  }

  //LDR
    
  Serial.print("LDR : ");
  Serial.println(analogRead(A0));
  if(analogRead(A0)<900){
    digitalWrite(leddoor,HIGH);
  }
  else{
    
    digitalWrite(leddoor,LOW);
  }

if (distance <= trigger_distance){
  digitalWrite(irIn, LOW);
  digitalWrite(ServoIn, LOW);
  servo.write(0);

  while(distance<=trigger_distance){
    digitalWrite(buzzer, HIGH);
    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(buzzer, LOW);
    digitalWrite(ledPin, LOW);
    delay(1000);
    digitalWrite(trigPin, HIGH);
    delay(10);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    distance= duration*0.034/2;
  }
}
else{
  digitalWrite(buzzer, LOW);
  digitalWrite(ledPin, LOW);
  digitalWrite(irIn, HIGH);
  delay(1000);
  irDistance = digitalRead(irOut);
  
  if (irDistance == 0){
    digitalWrite(ServoIn, HIGH);
    servo.write(90);
    
   }
   else if(irDistance == 1){
    servo.write(0);
    digitalWrite(ServoIn, LOW);
    
   }
  
}

// Prints the distance on the Serial Monitor
Serial.print("IR: ");
Serial.println(irDistance);
Serial.print("Sonar: ");
Serial.println(distance);

}
