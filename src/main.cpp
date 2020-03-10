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
const uint16_t relay = 13; //D6

#include "Mqtt.h"

uint32_t delayMS = 3600000;
unsigned long previousTimeGeneral = 0;

String housePlace = "desktop";

void setup()
{
  Serial.begin(9600);
  setupBuzzer(buzzer, 800);
  initWifi();
  setupOta();
  initMqtt(housePlace);
  handleBuzzer(true);
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
    publishSensors();
    Serial.println();
  }
  handleOta();
  handleMqtt();
  handleBuzzer(false);
}