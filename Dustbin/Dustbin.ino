#include <Servo.h>
Servo servo;

//Sonar
const int echoPin = 13;
const int trigPin = 12;

//Signal
const int ledPin = 11;
const int buzzer = 10;

//IR
const int irIn = 9;
const int irOut = 8;

//
const int ServoIn = 7;
//const int ServoIn = 

//defines variables
long duration;
int distance;
int safetyDistance;
int irDistance;
int trigger_distance;

void setup() {
  //Sonar
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 

  //Output
  pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);

  //IR
  pinMode(irIn, OUTPUT);
  pinMode(irOut, INPUT);

  //Servo
  pinMode(ServoIn, OUTPUT);

  servo.attach(6);
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

trigger_distance = 10;

if (distance <= trigger_distance){
  digitalWrite(irIn, LOW);
  digitalWrite(ServoIn, LOW);
  servo.write(0);
  //servo2.write(90);

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
  //servo2.write(0);
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
