#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "Arduino.h"

DHT_Unified *dht;
uint16_t DHTPin = D1;

void setupDHTSensor(uint16_t pin) {
  DHTPin = pin;
  dht = new DHT_Unified(DHTPin, DHT11);
  dht->begin();
}

void printDHTSensor() {
      sensors_event_t event;
    dht->temperature().getEvent(&event);
    if (isnan(event.temperature))
    {
      Serial.println(F("Error reading temperature!"));
    }
    else
    {
      Serial.print(F("Temperature: "));
      Serial.print(event.temperature);
      Serial.println(F("°C"));
    }
    // Get humidity event and print its value.
    dht->humidity().getEvent(&event);
    if (isnan(event.relative_humidity))
    {
      Serial.println(F("Error reading humidity!"));
    }
    else
    {
      Serial.print(F("Humidity: "));
      Serial.print(event.relative_humidity);
      Serial.println(F("%"));
    }
}

float getTemperature() {
  sensors_event_t event;
  dht->temperature().getEvent(&event);
  return event.temperature;
}

float getHumidity() {
  sensors_event_t event;
  dht->humidity().getEvent(&event);
  return event.relative_humidity;
}