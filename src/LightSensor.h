#include "Arduino.h"

uint16_t lightSensorPin = A0;

void setupLightSensor(uint16_t pin) {
  lightSensorPin = pin;
  pinMode(lightSensorPin, INPUT);
}

void printLightSensor() {
    Serial.print("Light ");
    Serial.println(analogRead(lightSensorPin)  / 1023);
}

float getLightSensor() {
  return analogRead(lightSensorPin) * 100 / 1023;
}