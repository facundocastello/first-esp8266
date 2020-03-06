#include "Arduino.h"
#include "IrWhirpool.h"
#include "LightSensor.h"
#include "DHTSensor.h"
#include "Buzzer.h"
#include "Relay.h"

const uint16_t lightSensor = A0;
const uint16_t DHT = D1;
const uint16_t IrLed = D2;
const uint16_t buzzer = D5;
const uint16_t relay = 13; //D7

uint32_t delayMS = 5000;
unsigned long previousTimeGeneral = 0;

void setup()
{
  Serial.begin(9600);

  setupDHTSensor(DHT);
  setupLightSensor(lightSensor);
  setupIr(IrLed);
  setupBuzzer(buzzer, 800);
  setupRelay(relay);
}

void loop()
{
  const unsigned long nowTime = millis();

  if (nowTime - previousTimeGeneral > delayMS)
  {
    previousTimeGeneral = nowTime;
    handleDHTSensor();
    handleLightSensor();
    Serial.print("Relay ");
    // Serial.println(!digitalRead(relay));
    triggerRelay();
    handleIr();
    handleBuzzer(true);
  }
  handleBuzzer(false);
}