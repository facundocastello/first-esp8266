
/* IRremoteESP8266: IRsendDemo - demonstrates sending IR codes with IRsend.
 *
 * Version 1.0 April, 2017
 * Based on Ken Shirriff's IrsendDemo Version 0.1 July, 2009,
 * Copyright 2009 Ken Shirriff, http://arcfn.com
 *
 * An IR LED circuit *MUST* be connected to the ESP8266 on a pin
 * as specified by kIrLed below.
 *
 * TL;DR: The IR LED needs to be driven by a transistor for a good result.
 *
 * Suggested circuit:
 *     https://github.com/markszabo/IRremoteESP8266/wiki#ir-sending
 *
 * Common mistakes & tips:
 *   * Don't just connect the IR LED directly to the pin, it won't
 *     have enough current to drive the IR LED effectively.
 *   * Make sure you have the IR LED polarity correct.
 *     See: https://learn.sparkfun.com/tutorials/polarity/diode-and-led-polarity
 *   * Typical digital camera/phones can be used to see if the IR LED is flashed.
 *     Replace the IR LED with a normal LED if you don't have a digital camera
 *     when debugging.
 *   * Avoid using the following pins unless you really know what you are doing:
 *     * Pin 0/D3: Can interfere with the boot/program mode & support circuits.
 *     * Pin 1/TX/TXD0: Any serial transmissions from the ESP8266 will interfere.
 *     * Pin 3/RX/RXD0: Any serial transmissions to the ESP8266 will interfere.
 *   * ESP-01 modules are tricky. We suggest you use a module with more GPIOs
 *     for your first time. e.g. ESP-12 etc.
 */
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
const uint16_t kIrLed = D2;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).
IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.
// Example of data captured by IRrecvDumpV2.ino replace the array below with the numbers captured by IRrecvDumpV2.ino from the serial monitor 
uint16_t rawData[71] = {9262, 4456,  608, 538,  604, 538,  602, 596,  548, 538,  604, 536,  604, 538,  602, 540,  604, 536,  606, 1642,  606, 1638,  608, 1642,  602, 1642,  608, 538,  604, 1642,  604, 1644,  606, 1642,  604, 1642,  602, 1644,  604, 538,  604, 538,  604, 540,  602, 538,  606, 594,  550, 538,  604, 564,  578, 540,  602, 1642,  630, 1618,  606, 1642,  604, 1646,  604, 1642,  604, 1640,  606, 40702,  9246, 2196,  614}; 
void setup() {
  irsend.begin();
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
}
void loop() {
#if SEND_RAW
  Serial.println("a rawData capture from IRrecvDumpV2");
  irsend.sendRaw(rawData, 71, 38);  // Send a raw data capture at 38kHz.
#endif  // SEND_RAW
  delay(2000);
}