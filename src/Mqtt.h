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


void publishSensors()
{

  float temperature = getTemperature();
  float humidity = getHumidity();
  float lightSensor = getLightSensor();
  float motion = digitalRead(pirPin);
  String sendMessage = "{ \"temperature\": " + String(temperature) + ",  \"humidity\": " + String(humidity) + ",  \"light\": " + String(lightSensor) + ",  \"motion\": " + String(motion) + " }";

  client.publish((place + "/sensors").c_str(), sendMessage.c_str());
}


void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  std::vector<String> arrStrPayload;
  String strPayload = "";
  for (int i = 0; i < length; i++)
  {

    if (String((char)payload[i]) == String(","))
    {
      Serial.println(strPayload);
      arrStrPayload.push_back(strPayload);
      strPayload = "";
    }
    else
    {
      strPayload += (char)payload[i];
    }
  }
  Serial.println(strPayload);
  arrStrPayload.push_back(strPayload);
  String strTopic = String(topic);
  String subTopic = strTopic.substring(strTopic.indexOf("/") + 1, strTopic.length());

  if (subTopic == "switch")
  {
    triggerRelay();
  }
  if (subTopic == "getSensors")
  {
    publishSensors();
  }
  if (subTopic == "buzzer")
  {
    handleBuzzer(true);
  }
  if (subTopic == "acToggle")
  {
    toggleAC(
        arrStrPayload.size() > 0 ? arrStrPayload[0].toInt() : 24,
        arrStrPayload.size() > 0 ? arrStrPayload[1].toInt() : 0);
  }
  if (subTopic == "acTemperature")
  {
    changeACSettings(
        arrStrPayload.size() > 0 ? arrStrPayload[0].toInt() : 24,
        arrStrPayload.size() > 0 ? arrStrPayload[1].toInt() : 0);
  }
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

void handleMqtt()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
}
