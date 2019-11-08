#include <Wire.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include "LowPower.h"

bool status;
const int green_led = 13;
int count = 0;


void setup() {
  Serial.begin(9600);
  Serial.println("Initializing");
  pinMode(green_led, OUTPUT);
  digitalWrite(green_led, HIGH);
  delay(5000);                 
  Serial.println("Beginning Test");  
  digitalWrite(green_led, LOW);
}
///////////////////////////////////////VOID SETUP END

void loop()
{
  Serial.println("Entering Sleep Mode");
  delay(500);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_4S, ADC_OFF, BOD_OFF);
  delay(500);
  Serial.println("Waking from Sleep Mode");

  delay(500);

  Serial.println("Simulating sensor collection...");
    digitalWrite(green_led, HIGH);
    delay(1000);
    digitalWrite(green_led, LOW);
    delay(500);
    
    digitalWrite(green_led, HIGH);
    delay(1000);
    digitalWrite(green_led, LOW);
    delay(500);
    
    digitalWrite(green_led, HIGH);
    delay(1000);
    digitalWrite(green_led, LOW);
    delay(500);
    
    digitalWrite(green_led, HIGH);
    delay(1000);
    digitalWrite(green_led, LOW);
    delay(500);
  Serial.println("Data Transmitted!");
  delay(500);
}
