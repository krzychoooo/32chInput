#include <Arduino.h>
#include <Wire.h>
#include <TCA6416A.h>
#include "Input_32chanel.h"

TCA6416A chanel0x20Obj(0x20);
TCA6416A chanel0x21Obj(0x21);
Input_32chanel myInput(chanel0x20Obj, chanel0x21Obj);

uint8_t IRQpin = 2;

void show(void);

void ARDUINO_ISR_ATTR tca6416INT() {
  myInput.intFlag = true;
  myInput.timeToRead = millis() + 50;
}

void setup()
{
	Serial.begin(115200);

  pinMode(IRQpin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IRQpin), tca6416INT, FALLING);

  if (myInput.begin(show) == false){
    Serial.println("TCA6416 problem");
    while (1);    
  }
}

void loop(){
myInput.loop();
}


void show(){
   Serial.print("chanel \t"); 
   for (size_t i = 0; i < 32; i++){
     Serial.print(i); Serial.print("\t"); 
    }
    Serial.println("");
    Serial.print("value  \t"); 
  for (size_t i = 0; i < 32; i++){
    bool val = myInput.getChanelValue(i);
    Serial.print(val); Serial.print("\t"); 
  }
  Serial.println("\n");
}