/*
RGB Light controlled by ultrasonic sensor

Sensor - 5v, grnd, Pin 12 = Trigg, Pin 11 = Echo
RGB Light - Grnd, Red 6, Green 5, Blue 3

How it works: 
Hold hand over sensor (less than 30cm) for a second to switch it on and off
Wave your hand over sensor to random shuffle through preset colours


*/




#include <HCSR04.h>
unsigned long startTime;
const byte ledPin = 13;
unsigned long currentTime;
const unsigned long periodSwitch = 1000;
const unsigned long periodColour = 30;
unsigned long timeDiff;
#define BLUE 3
#define GREEN 5
#define RED 6
long randRed = random(1,256);
long randBlue = random(1,256);
long randGreen = random(1,256);
int randColour = 0;
int colourArr[7][3] {{HIGH,HIGH,HIGH},{LOW,HIGH,HIGH},{LOW,LOW,HIGH},{HIGH,LOW,HIGH}, {LOW,HIGH,LOW}, {HIGH,LOW,LOW},{HIGH,HIGH,LOW}};//array to go through different colours


HCSR04 hc(12,11);//initialisation class HCSR04 (trig pin , echo pin)

void setup()
{ Serial.begin(9600);
pinMode(ledPin, OUTPUT);
pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(ledPin, LOW);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  randomSeed(analogRead(0));

}
int redValue;
int greenValue;
int blueValue;

void loop()
{/* Serial.print( hc.dist() );
Serial.println(" cm");
delay(500);*/
currentTime = millis();
/*if (hc.dist() < 30.00) { 
  startTime = currentTime;
  delay(periodSwitch);
  currentTime = millis();
  
  if (currentTime - startTime >= periodSwitch) {
    digitalWrite(ledPin, !digitalRead(ledPin));
     Serial.println("Should be on m8");
    } 
 
}*/
startTime = currentTime;
 while (hc.dist() < 30.00){};
currentTime = millis();
timeDiff = currentTime - startTime;
Serial.println(timeDiff);

 if (timeDiff >= periodSwitch) {
    digitalWrite(ledPin, !digitalRead(ledPin));
     Serial.println("Should be on");
     if (digitalRead(RED) == HIGH || digitalRead(GREEN) == HIGH ||digitalRead(BLUE) == HIGH){ 
     digitalWrite(RED, LOW);
digitalWrite(GREEN, LOW);
digitalWrite(BLUE, LOW);
} else if (digitalRead(RED) == LOW && digitalRead(GREEN) == LOW && digitalRead(BLUE) == LOW) {
  digitalWrite(RED, HIGH);
digitalWrite(GREEN, HIGH);
digitalWrite(BLUE, HIGH);
};
};
     
    
if (timeDiff >= 10 && timeDiff <= 300 ){
  Serial.println("Change colour");
 randColour = random(0,6);
 randBlue = random(0,4);
 randGreen = random(0,4);
digitalWrite(RED, colourArr[randColour][0]);
digitalWrite(GREEN, colourArr[randColour][1]);
digitalWrite(BLUE, colourArr[randColour][2]);
 
 Serial.print("The random colour is: ");
 Serial.println(randColour);
 /*analogWrite(RED, randRed);
analogWrite(GREEN, randGreen);
analogWrite(BLUE, randBlue);*/
  
};  




 

}//return curent distance in serial
