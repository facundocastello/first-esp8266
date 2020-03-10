#include "Arduino.h"

uint16_t buzzerPin = D5;

int buzzerTone = 800;
unsigned long previousTimeBuzzer = 0;
unsigned long previousTimeMillis = 0;
const int activeTime = 1000;

bool finished = false;

void setupBuzzer(uint16_t pin, int newBuzzerTone)
{
  buzzerTone = newBuzzerTone;
  buzzerPin = pin;
  pinMode(buzzerPin, OUTPUT);
}

void handleBuzzer(bool activate)
{
  if (activate)
  {
    previousTimeMillis = millis();
    finished = false;
  }
  const unsigned long nowTimeMillis = millis();
  if ((nowTimeMillis - previousTimeMillis) < activeTime)
  {
    const unsigned long nowTimeMicros = micros();
    if ((nowTimeMicros - previousTimeBuzzer) >= buzzerTone)
    {
      previousTimeBuzzer = nowTimeMicros;
      digitalWrite(buzzerPin, !digitalRead(buzzerPin));
    }
  }
  else if (!finished)
  {
    finished = true;
    digitalWrite(buzzerPin, LOW);
  }
}