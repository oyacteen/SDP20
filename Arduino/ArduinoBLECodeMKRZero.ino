#include <ArduinoLowPower.h>
//#include <LowPower.h> // low power sleep
#include <avr/dtostrf.h>
//#include <SoftwareSerial.h> //serial communication for bluetooth
#include <Wire.h>
#include <RTCZero.h>
//#include <avr/power.h>
//SoftwareSerial ble(11,10); // wiring for BLE RX/TX (RX of hm10 goes to pin 10)

// Allocating memory for data/BLE transmission
//char temp_output[5];
//char hum_output[5]; 
//char pres_output[5];
char ble_dat_send[24];
char dist_output[5];
char moist_output[4];

RTCZero rtc;

/* Change these values to set the current initial time */
const byte seconds = 0;
const byte minutes = 00;
const byte hours = 00;

/* Change these values to set the current initial date */
const byte day = 11;
const byte month = 12;
const byte year = 19;

const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor

//float temp;
//float hum;
//float pres;
int moist;
float dist;

void setup() {
  delay(5000);
  //if(F_CPU == 8000000) clock_prescale_set(clock_div_2);
  //if(F_CPU == 4000000) clock_prescale_set(clock_div_4);
  //if(F_CPU == 2000000) clock_prescale_set(clock_div_8);
  //if(F_CPU == 1000000) clock_prescale_set(clock_div_16);
  
  rtc.begin(); //Start RTC library, this is where the clock source is initialized
  rtc.setTime(hours, minutes, seconds); //set time
  rtc.setDate(day, month, year); //set date
  rtc.setAlarmTime(00, 00, 30); //set alarm time to go off in 30 seconds
  rtc.enableAlarm(rtc.MATCH_HHMMSS); //set alarm
  rtc.attachInterrupt(ISR); //creates an interrupt that wakes the SAMD21 which is triggered by a FTC alarm
  
  Serial.begin(9600);
  Serial1.begin(9600);
  while(!Serial);
  Serial.println("AT commands: okay ");

  rtc.standbyMode();
  
}

void loop() {
  // looping for values
  //temp = bme.readTemperature();  
  //dtostrf(temp,3,1,temp_output);

  //pres = bme.readPressure()/100.0F;
  //dtostrf(pres,3,1,pres_output);

  //hum = bme.readHumidity();
  //dtostrf(hum,3,1,hum_output);

  
}

void ISR() {
  moist = analogRead(0);
  Serial.print("moistVal = ");
  Serial.println(moist);
  Serial.print("moistSize = ");
  Serial.println(sizeof(moist));
  dtostrf(moist,2,0,moist_output);
  //Serial.print("moist_outputSize = ");
  //Serial.println(sizeof(moist_output));
  
  dist = calc_distance_cm();
  Serial.print("Dist = ");
  Serial.println(dist);
  dtostrf(dist,2,1,dist_output);
  
  // change data from float to char array for BLE
  //strcpy(ble_dat_send,temp_output);
  //strcat(ble_dat_send,";");
  //strcat(ble_dat_send,hum_output);
  //strcat(ble_dat_send,";");
  //strcat(ble_dat_send,pres_output);
  
  //strcpy(ble_dat_send,moist_output);
  //strcat(ble_dat_send,";");
  //strcat(ble_dat_send,dist_output);
  int elementSize = sizeof(moist_output[0]);
  int packageSize = sizeof(moist_output);
  char firstElement = moist_output[0];
  Serial.print("elementSize =");
  Serial.println(elementSize);
  Serial.print("packageSize =");
  Serial.println(packageSize);
  Serial.print("firstElement =");
  Serial.println(firstElement);
  
  int arraySize = sizeof(moist_output)/sizeof(moist_output[0]);
  Serial.print("# of elements = ");
  Serial.println(arraySize);
  //ble.write(moist_output);
  Serial1.write(moist_output); // write BLE (send to Pi)
  Serial1.write(" ");
  Serial1.write(dist_output);
  Serial1.flush();
  delay(100);

  // Sleep routine (113 ~ 15 min)
  //for(int ii;ii<113;ii++){
    //LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);    
  //}  
  //LowPower.deepSleep(2000); 
  //LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
  // Sleep routine (8 ~ 1min)
  //for(int ii;ii<8;ii++){
    //LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);    
  //}  
  delay(200); // allow the system to wake
}

float calc_distance_cm(){
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   float duration = pulseIn(echoPin, HIGH);
   dist = microsecondsToCentimeters(duration);
   return dist;
}

void sensorsOff() {
  
  
}
float microsecondsToCentimeters(float microseconds) {
   return microseconds / 29 / 2;
}
