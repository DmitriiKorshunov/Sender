#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Arduino.h>
#include "heltec.h"
#define BAND    433E6  //you can set band here directly,e.g. 868E6,915E6
#define DHTPIN 17
 
DHT dht(DHTPIN, DHT11); // Инициализация датчика


void setup() {
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
 dht.begin();
}

void loop() {
  float h = dht.readHumidity(); //Измеряем влажность
  float t = dht.readTemperature(); //Измеряем температуру

  // send packet
  LoRa.beginPacket();
  LoRa.println("Temp");
  LoRa.println(t);
  LoRa.println("Humidity");
  LoRa.println(h);
  LoRa.endPacket();
  digitalWrite(25, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(25, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}
