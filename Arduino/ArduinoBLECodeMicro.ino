#include <LowPower.h> // low power sleep
#include <SoftwareSerial.h> //serial communication for bluetooth
#include <Wire.h>
//#include <avr/power.h>
SoftwareSerial ble(11,10); // wiring for BLE RX/TX (RX of hm10 goes to pin 10)

// Allocating memory for data/BLE transmission
//char temp_output[5];
//char hum_output[5];
//char pres_output[5];
char ble_dat_send[24];
char dist_output[5];
char moist_output[4];
char lux_output[5];

const int pingPin = 7; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 6; // Echo Pin of Ultrasonic Sensor
const int luxPin = 1; //Analog Pin of Solar Cell input

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
  //if(F_CPU == 8000000) clock_prescale_set(clock_div_2);
  //if(F_CPU == 4000000) clock_prescale_set(clock_div_4);
  //if(F_CPU == 2000000) clock_prescale_set(clock_div_8);
  //if(F_CPU == 1000000) clock_prescale_set(clock_div_16);
  Serial.begin(9600);
  ble.begin(9600);
  //while(!Serial);
  Serial.println("AT commands: okay ");
}

void loop() {
  // looping for values
  //temp = bme.readTemperature();  
  //dtostrf(temp,3,1,temp_output);

  //pres = bme.readPressure()/100.0F;
  //dtostrf(pres,3,1,pres_output);

  //hum = bme.readHumidity();
  //dtostrf(hum,3,1,hum_output);

  moist = analogRead(0);
  //Serial.print("moistVal = ");
  //Serial.println(moist);
  //Serial.print("moistSize = ");
  //Serial.println(sizeof(moist));
  dtostrf(moist,2,0,moist_output);
  //Serial.print("moist_outputSize = ");
  //Serial.println(sizeof(moist_output));

  lightLevel = analogRead(luxPin);
  voltage = lightLevel * (5.0 / 1024.0);
  dtostrf(voltage,2,1,lux_output);
  
  //dist = calc_distance_cm();
  //Serial.print("Dist = ");
  //Serial.println(dist);
  //dtostrf(dist,2,1,dist_output);

  
  
  // change data from float to char array for BLE
  //strcpy(ble_dat_send,temp_output);
  //strcat(ble_dat_send,";");
  //strcat(ble_dat_send,hum_output);
  //strcat(ble_dat_send,";");
  //strcat(ble_dat_send,pres_output);
  
  //strcpy(ble_dat_send,moist_output);
  //strcat(ble_dat_send,";");
  //strcat(ble_dat_send,dist_output);
 // int elementSize = sizeof(moist_output[0]);
  //int packageSize = sizeof(moist_output);
  //char firstElement = moist_output[0];
  //Serial.print("elementSize =");
  //Serial.println(elementSize);
  //Serial.print("packageSize =");
  //Serial.println(packageSize);
  //Serial.print("firstElement =");
  //Serial.println(firstElement);
  
  //int arraySize = sizeof(moist_output)/sizeof(moist_output[0]);
  //Serial.print("# of elements = ");
  //Serial.println(arraySize);
  //ble.write(moist_output);
  ble.write(moist_output); // write BLE (send to Pi)
  ble.write(" ");
  ble.write(lux_output);
  //ble.write(dist_output);
  ble.flush();
  delay(100);
  bleOff();
  // Sleep routine (113 ~ 15 min)
  //for(int ii;ii<113;ii++){
    //LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);    
  //}    
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF); 

  delay(200); // allow the system to wake
  bleOn();
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

void bleOff() {
  Serial.write("AT+PWRM1");
  
}

void bleOn() {
  Serial.write("ccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc");
}
float microsecondsToCentimeters(float microseconds) {
   return microseconds / 29 / 2;
}
