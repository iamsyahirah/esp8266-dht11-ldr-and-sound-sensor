#define BLYNK_TEMPLATE_ID "TMPL4or_sETJ"
#define BLYNK_DEVICE_NAME "decibelmeter"
#define BLYNK_AUTH_TOKEN "H2hfJdSlnfxPUlB0Nb799EG4V4KkvjGr"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Wire.h>
#include "DHT.h"

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "";  // type your wifi name
char pass[] = "";  // type your wifi password

#define sound A0
#define DHTPIN D2
#define light D0


DHT dht(D2, DHT11);
BlynkTimer timer;

void setup() {   
  Serial.begin(9600);
  
  Blynk.begin(auth, ssid, pass);
  dht.begin();
 
  // Call the functions
  timer.setInterval(100L, DHT11sensor);
  timer.setInterval(100L, soundSensor); 
  timer.setInterval(100L, LDRsensor);
  }

  //Get the DHT11 sensor values
  void DHT11sensor() {
    float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.println(F("Humidity: "));
  Serial.println(h);
  Serial.println(F("Temperature: "));
  Serial.println(t);
    
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
  }

  void soundSensor() {
  // Get the sound sensor values
  int value = analogRead(sound);
  Serial.println("Sound sensor: ");
  Serial.println(value);
  delay(1000);
  
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
    Blynk.virtualWrite(V2, value);
    delay(500);
}

//Get the LDR sensor values
void LDRsensor() {
  int lightValue = analogRead(light);
  lightValue = map(lightValue, 0, 1023, 0, 100);
  //lightValue = map(lightValue, 0, 800, 0, 10);

  Serial.println("Light level: ");
  Serial.println(lightValue);

  // We'll have a few threshholds, qualitatively determined
  //if (LDRvalue < 500) {
   // Serial.println(" - Bright");
  //} else {
   // Serial.println(" - Dark");
 // }

  delay(1000);

  Blynk.virtualWrite(V3, lightValue);
  }

void loop()
{
  Blynk.run();
  timer.run();
 }
