#include <LowPower.h> // low power sleep
#include <SoftwareSerial.h> //serial communication for bluetooth
#include <Wire.h>
SoftwareSerial ble(11,10); // wiring for BLE RX/TX (RX of hm10 goes to pin 10)

// Allocating memory for data/BLE transmission
char moist_output[4];
char lux_output[5];

const int luxPin = A1; //Analog Pin of Solar Cell input
const int soilVccPin = 8; //Power VCC pin for Soil sensor
const int soilDataPin = A0; //Data Pin for Soil sensor
const int bleVcc = 6; //HM-10 VCC pin
const int bleGnd = 7; //HM-10 GND pin

// insuffiecient light intesity boundary
float inBound = 1.61;
// lower light intesity boundary 
float lowBound = 1.79; 
// medium light intesity boundary
float medBound = 2.50;
// high light intensity boundary 
float highBound = 3.11; 

float voltage;

//float temp;
//float hum;
//float pres;
int moist;
int lightLevel;
float dist;

void setup() {
  pinMode(soilVccPin,OUTPUT);
  digitalWrite(soilVccPin, HIGH);
  pinMode(bleVcc,OUTPUT);
  pinMode(bleGnd,OUTPUT);
  digitalWrite(bleVcc,HIGH);
  digitalWrite(bleGnd,LOW);
  //Serial.begin(9600);
  ble.begin(9600);
  //Serial.println("AT commands: okay ");
}

void loop() {
  // looping for values
  pinMode(soilVccPin,OUTPUT);
  digitalWrite(soilVccPin, HIGH); //Turn on soil sensor for measurement
  delay(200);
  moist = analogRead(soilDataPin); //Measure soil moisture
  //Serial.print("moistVal = ");
  //Serial.println(moist);
  dtostrf(moist,2,0,moist_output);
  digitalWrite(soilVccPin, LOW);  //Turn off soil sensor
  pinMode(soilVccPin, INPUT);

  lightLevel = analogRead(luxPin); //Measure light intensity
  voltage = lightLevel * (5.0 / 1024.0);
  //Serial.print("lightLevel = ");
  //Serial.println(lightLevel);
  //Serial.print("Voltage = ");
  //Serial.println(voltage);
  //Serial.println();
  dtostrf(voltage,4,2,lux_output);
  
  pinMode(bleGnd,OUTPUT); //Turn on bluetooth 
  digitalWrite(bleVcc,HIGH);
  delay(1000);
  ble.write(moist_output); // write BLE (send to Pi)
  ble.write(" ");
  ble.write(lux_output);
  ble.flush();
  delay(1000);
  digitalWrite(bleVcc,LOW);
  pinMode(bleGnd,INPUT);  //Turn off bluetooth

  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
  delay(200); // allow the system to wake
  
}


void bleOff() {
  Serial.write("AT+PWRM1");
  
}

void bleOn() {
  Serial.write("ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc");
}
