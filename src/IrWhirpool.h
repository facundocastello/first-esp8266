#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ir_Whirlpool.h>

// ESP8266 GPIO pin to use. Recommended: 4 (D2).
IRWhirlpoolAc *ac; // Set the GPIO used for sending messages.

void printState()
{
  // Display the settings.
  Serial.println("Whirlpool A/C remote is in the following state:");
  Serial.printf("  %s\n", ac->toString().c_str());
  // Display the encoded IR sequence.
  unsigned char *ir_code = ac->getRaw();
  Serial.print("IR Code: 0x");
  for (uint8_t i = 0; i < kWhirlpoolAcStateLength; i++)
    Serial.printf("%02X", ir_code[i]);
  Serial.println();
}

void setupIr(uint16_t IrLed)
{
  ac = new IRWhirlpoolAc(IrLed);
  ac->begin();
  delay(200);

  // ac->setVane(kWhirlpoolAcvan);
}

void toggleAC(int temperature, int fan = 0)
{
  // Now send the IR signal.
#if SEND_MITSUBISHI_AC
  Serial.println("Sending IR command to A/C ...");
  ac->setPowerToggle(true);
  ac->setFan(fan);
  ac->setMode(kWhirlpoolAcCool);
  ac->setTemp(temperature);
  ac->send();
#endif // SEND_MITSUBISHI_AC
  printState();
}

void changeACSettings(int temperature, int fan = 0)
{
  // Now send the IR signal.
#if SEND_MITSUBISHI_AC
  Serial.println("Sending IR command to A/C ...");
  ac->setPowerToggle(false);
  ac->setFan(fan);
  ac->setMode(kWhirlpoolAcCool);
  ac->setTemp(temperature);
  ac->send();
#endif // SEND_MITSUBISHI_AC
  printState();
}