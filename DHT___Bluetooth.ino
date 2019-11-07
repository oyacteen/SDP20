#include <Wire.h>
#include <SPI.h>
#include <dht.h>
#include <SoftwareSerial.h>
#include "LowPower.h"

dht DHT;
#define DHT11_PIN 7

SoftwareSerial Bluetooth(2,3);

bool status;
const int green_led = 13;
const int red_led = 12;
const int transmit_pin = 11;
const int receive_pin =10;
const int white_led = 9;
//SoftwareSerial MyBlue(receive_pin,transmit_pin); //RX|TX



struct package
{
  int temperature ;
  int humidity ;
  int moisture;
};


typedef struct package Package;
Package data;
//////////////////////////
unsigned long delayTime;
/////////////////////////


 void readSensor() {
  //delay(1);
  int chk = DHT.read11(DHT11_PIN);
  data.humidity = DHT.humidity;
  data.temperature = DHT.temperature;
  data.moisture = analogRead(0);
}

bool AlertCheck(){
  if (DHT.humidity > 40 & DHT.temperature > 23) return false;
  else return true;
 
}

void setup() {
  Serial.begin(9600);
  Bluetooth.begin(9600);
  pinMode(green_led, OUTPUT);
  pinMode(red_led, OUTPUT);
  pinMode(white_led,OUTPUT);


  //////////////////////////////////////////LOW POWER ALL PINS OUTPUT
  //for (int i = 0; i < 20; i++) {
   // pinMode(i, OUTPUT);
  //}

  //Serial.println("-- Default Test --");
  //delayTime = 1000;
  /////////////////////////////////////////////////////////////////

  //delayTime = 60000; // in milliseconds
  ///////////////////////////////////////////////////////////////////
  digitalWrite(red_led, HIGH);
  delay(2000);                   
  digitalWrite(red_led, LOW);
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

  readSensor();
  delay(500);
  Serial.print("Moisture = ");
  Serial.println(data.moisture);
  delay(500);
  //Serial.print("Humidity = ");
  //Serial.println(DHT.humidity);
  delay(500);
  //status = AlertCheck();
  if (AlertCheck() == false) {
    digitalWrite(red_led, HIGH); // Flash a light to show transmitting
    //Bluetooth.println("Your plant is too hot and humid!");
    //Bluetooth.print("Temperature = ");
    Bluetooth.print(DHT.temperature);
    Bluetooth.print(" ");
    //Bluetooth.print("Humidity = ");
    Bluetooth.print(DHT.humidity);
    Bluetooth.print("\n");
    delay(2000);
    digitalWrite(red_led,LOW);
  }
  else if (AlertCheck() == true){
    digitalWrite(green_led,HIGH);
    //Bluetooth.println("Your plant is healthy and happy!");
    //Bluetooth.print("Temperature = ");
    Bluetooth.print(DHT.temperature);
    Bluetooth.print(" ");
    //Bluetooth.print("Humidity = ");
    Bluetooth.print(DHT.humidity);
    Bluetooth.print("\n");
    delay(2000);
    digitalWrite(green_led,LOW); 
  }
  //digitalWrite(led_pin, LOW);
  //delay(1);
}
