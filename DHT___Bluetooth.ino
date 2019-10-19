#include <dht.h>
#include <SoftwareSerial.h>

dht DHT;
SoftwareSerial Bluetooth(2,3);

#define DHT11_PIN 2

void setup(){
  Serial.begin(9600);
  Bluetooth.begin(9600);
  Bluetooth.println("Ready");
  Serial.println("Started");
}

void loop()
{
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Bluetooth.print("Temperature = ");
  Bluetooth.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  Bluetooth.print("Humidity = ");
  Bluetooth.println(DHT.humidity);
  delay(2000);
}
