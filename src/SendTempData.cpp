#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Arduino.h>
#include "heltec.h"
#define BAND    433E6  //you can set band here directly,e.g. 868E6,915E6
#define DHTPIN 17
 
DHT dht(DHTPIN, DHT11); // Init sencsor


void setup() {
//Begin Heltec`s Lib for lora
Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
//Begin Sensor Lib
dht.begin();
}

void loop() {
// Sensor DHT
float h = dht.readHumidity(); // Recieve data about humidity.
float t = dht.readTemperature(); // Recieve data about temp.
// Information about device id
// Init display
Heltec.display->init();
Heltec.display->flipScreenVertically();
// Text setting
Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
Heltec.display->setFont(ArialMT_Plain_16);
Heltec.display->drawString(0, 0, "The num this");
Heltec.display->drawString(0, 20, "device - 1");
Heltec.display->display();
// Send packet
LoRa.beginPacket();
LoRa.print("1"); // id 1. Choose id for your device here. 
LoRa.print("Temp");
LoRa.print(t);
LoRa.print("Hum");
LoRa.println(h);
LoRa.endPacket();
digitalWrite(25, HIGH);   
delay(1000);              
digitalWrite(25, LOW);    
delay(1000);                      
LoRa.idle();  //  Radio in idle (standby) mode.
digitalWrite(25, HIGH);             
delay(5000); 
digitalWrite(25, LOW);  
}
