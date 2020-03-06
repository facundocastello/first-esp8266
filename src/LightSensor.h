#include "Arduino.h"

uint16_t lightSensorPin = A0;

void setupLightSensor(uint16_t pin) {
  lightSensorPin = pin;
  pinMode(lightSensorPin, INPUT);
}

void handleLightSensor() {
    Serial.print("Light ");
    Serial.println(analogRead(lightSensorPin * 3.3 / 1023));
}