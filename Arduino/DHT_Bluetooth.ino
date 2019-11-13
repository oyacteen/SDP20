#include <Wire.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include "LowPower.h"

SoftwareSerial Bluetooth(2,3); //RX|TX

//////////////////////////
unsigned long delayTime;
/////////////////////////

void setup() {
  Serial.begin(9600);
  Bluetooth.begin(9600);

  //////////////////////////////////////////LOW POWER ALL PINS OUTPUT
  //for (int i = 0; i < 20; i++) {
   // pinMode(i, OUTPUT);
  //}

  //Serial.println("-- Default Test --");
  //delayTime = 1000;
  /////////////////////////////////////////////////////////////////

  //delayTime = 60000; // in milliseconds
  ///////////////////////////////////////////////////////////////////
  delay(2000);                   
  //Serial.println();
 // delay(100); // let sensor boot up
}
///////////////////////////////////////VOID SETUP END

void loop()
{
  LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_2S, ADC_OFF, BOD_OFF);
  
  //delay(1000);//LOW POWER CODE, SLEEP FOR 8 SECONDS
  
  delay(500);
  
  Serial.print("Moisture = ");
  Serial.println(analogRead(0));
  Serial.print("Light = ");
  Serial.println(analogRead(1));
  
  delay(1000);
  
  Bluetooth.print(analogRead(0));
  Bluetooth.print(" ");
  Bluetooth.print(analogRead(1));
  Bluetooth.print("\n");
  
  delay(2000);
  
  Bluetooth.print(analogRead(0));
  Bluetooth.print(" ");
  Bluetooth.print(analogRead(1));
  Bluetooth.print("\n");
  
  delay(2000);
 
}
