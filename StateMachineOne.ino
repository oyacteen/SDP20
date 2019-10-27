#include <Wire.h>
#include <SPI.h>
#include <dht.h>
#include <SoftwareSerial.h>
#include "LowPower.h"

dht DHT;  //Instantiate temp and humidity sensor
#define DHT11_PIN 7
SoftwareSerial Bluetooth(2,3);

bool status;
const int green_led = 13;
const int red_led = 12;
const int transmit_pin = 11;
const int receive_pin =10;
const int white_led = 9;

struct package
{
  int temperature ;
  int humidity ;
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
  digitalWrite(red_led, HIGH);
  delay(2000);                   
  digitalWrite(red_led, LOW);
}
///////////////////////////////////////VOID SETUP END




void loop()
{
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  
  //delay(1000);//LOW POWER CODE, SLEEP FOR 8 SECONDS

  readSensor();
  delay(500);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  delay(500);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  delay(500);
  //status = AlertCheck();
  if (AlertCheck() == false) {
    digitalWrite(red_led, HIGH); // Flash a light to show transmitting
    Bluetooth.println("Your plant is too hot and humid!");
    Bluetooth.print("Temperature = ");
    Bluetooth.println(DHT.temperature);
    Bluetooth.print("Humidity = ");
    Bluetooth.println(DHT.humidity);
    delay(2000);
    digitalWrite(red_led,LOW);
  }
  else if (AlertCheck() == true){
    digitalWrite(green_led,HIGH);
    Bluetooth.println("Your plant is healthy and happy!");
    Bluetooth.print("Temperature = ");
    Bluetooth.println(DHT.temperature);
    Bluetooth.print("Humidity = ");
    Bluetooth.println(DHT.humidity);
    delay(2000);
    digitalWrite(green_led,LOW); 
  }
  //digitalWrite(led_pin, LOW);
  //delay(1);
}
