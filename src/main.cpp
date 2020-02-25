// #include <WiFiUdp.h>
// #include <SPI.h>
// #include <Ethernet.h>
// #include <PubSubClient.h>
#include <StepMotor.h>
#include <Ota.h>

StepMotor *motor;
Ota *ota;

void setup()
{
  Serial.begin(9600);
  Serial.println("Booting");
  motor = new StepMotor();
  ota = new Ota();
}

void loop()
{
  motor->handleMotor();
  ota->handleOta();
}