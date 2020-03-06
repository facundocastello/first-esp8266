#include "Arduino.h"

uint16_t relayPin = 13; //D7

void setupRelay(uint16_t pin)
{
  relayPin = pin;
  pinMode(relayPin, OUTPUT);
}
void triggerRelay()
{
  uint8_t newRelayValue = !digitalRead(relayPin);
    Serial.print("Relay ");
    Serial.println(newRelayValue == 1 ? "Turned On": "Turned Off");
  digitalWrite(relayPin,newRelayValue);
}