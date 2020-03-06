#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "casacas"
#define STAPSK "arrancaaescribir"
#endif

void initWifi()
{
  Serial.println('Connecting wifi');
  WiFi.hostname("ESP-host");
  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);
  int8_t stat = WiFi.status();
  while (stat != WL_CONNECTED)
  {
    delay(500);
    Serial.print(stat);
    stat = WiFi.status();
  }
  
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
// : Operation mode: 802.11g+n to Automatic Channel: 11 to Automatic Channel Bandwich: 20 to Automatic

// then the problem was solved.