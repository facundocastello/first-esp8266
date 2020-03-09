#include <PubSubClient.h>
#include <iostream>
#include <sstream>
#include <string>

const char *mqtt_server = "192.168.0.253";
const char *username = "facumqtt";
const char *password = "facumqtt";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

String place = "";

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
  Serial.println();
  // switch (topic)
  // {
  // case /* constant-expression */:
  //   /* code */
  //   break;

  // default:
  //   break;
  // }
}

void reconnect()
{
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str(), username, password))
    {
      Serial.println("connected");
      client.subscribe((place + "/#").c_str());
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void initMqtt(String rootPlace)
{
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  place = rootPlace;
}

void handleMqtt(String sendMessage, String topic)
{

  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
  
  client.publish((place + "/" + topic).c_str(), sendMessage.c_str());
}

void publishSensors(float temperature, float humidity, float lightSensor, float motion)
{
  handleMqtt("{ \"temperature\": " + String(temperature) + ",  \"humidity\": " + String(humidity) + ",  \"light\": " + String(lightSensor) + ",  \"motion\": " + String(motion) + " }", "sensors");
}
