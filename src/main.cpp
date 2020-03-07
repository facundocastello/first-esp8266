#include "Arduino.h"
#include "IrWhirpool.h"
#include "LightSensor.h"
#include "DHTSensor.h"
#include "Buzzer.h"
#include "Relay.h"
#include "WiFi.h"
#include "Ota.h"

const uint16_t lightSensor = A0;
const uint16_t DHT = D1;
const uint16_t IrLed = D2;
const uint16_t pirPin = D4;
const uint16_t buzzer = D5;
const uint16_t relay = 13; //D7

uint32_t delayMS = 1000;
unsigned long previousTimeGeneral = 0;

void setup()
{
  Serial.begin(9600);
  setupBuzzer(buzzer, 800);
  initWifi();
  handleBuzzer(true);
  setupOta();
  pinMode(pirPin, INPUT);
  setupDHTSensor(DHT);
  setupLightSensor(lightSensor);
  setupIr(IrLed);
  setupRelay(relay);
}

void loop()
{
  const unsigned long nowTime = millis();

  if (nowTime - previousTimeGeneral > delayMS)
  {
    previousTimeGeneral = nowTime;
    handleOta();
    handleDHTSensor();
    handleLightSensor();
    Serial.print("Relay ");
    // Serial.println(!digitalRead(relay));
    triggerRelay();
    handleIr();
    // handleBuzzer(true);

    Serial.println(digitalRead(pirPin));
  }
  handleBuzzer(false);
}