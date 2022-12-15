#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <MFRC522.h>
#include <ArduinoJson.h>
#include <time.h>
#include "secrets.h"
#include "connectionWifi.h"
#include "leitos.hpp"
#include "Button2.h"


String convert = "";
String conteudo = "";
String TagsCadastradas[] = {"06 8e 67 a5", "6d fc e8ab"};
String access = "denied!";
int TIME_ZONE = 4;
int Permitido = 0;


unsigned long lastMillis = 0;
unsigned long previousMillis = 0;
const long interval = 5000;


//MFRC522 mfrc522(SS_PIN, RST_PIN);



time_t now;
time_t nowish = 1510592825;

void NTPConnect()
{
  Serial.print("Setting time using SNTP");
  configTime(TIME_ZONE * 3600, -3, "pool.ntp.org", "time.nist.gov");

  now = time(nullptr);
  while (now < nowish)
  {
    delay(500);
    Serial.print(".");
    now = time(nullptr);
  }
  Serial.println(now);
  Serial.println("done!");
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);
  Serial.print("Current time: ");
  Serial.print(asctime(&timeinfo));
}


void acessoLiberado()
{
  Serial.println("");
  Serial.println("Access granted!");
  Serial.println("Tag Cadastrada: " + conteudo);
  //sendMessage();

  Permitido = 0;
  access = "denied!";
}
void acessoNegado()
{
  Serial.println("");
  Serial.println("Access denied!");
  Serial.println("Tag NAO Cadastrada: " + conteudo);
}


// void Rfid()
// {
//   if (!mfrc522.PICC_IsNewCardPresent())
//   {
//     return;
//   }

//   if (!mfrc522.PICC_ReadCardSerial())
//   {
//     return;
//   }

//   Serial.print("UID da tag :");
//   conteudo = "";
//   for (byte i = 0; i < mfrc522.uid.size; i++)
//   {

//     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
//     Serial.print(mfrc522.uid.uidByte[i], HEX);
//     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
//     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
//   }

//   for (int i = 0; i < (sizeof(TagsCadastradas) / sizeof(TagsCadastradas)); i++)
//   {
//     if (conteudo.substring(1).equalsIgnoreCase(TagsCadastradas[i]))
//     {
//       Permitido = 1;
//       access = "granted!";
//     }
//   }

//   if (Permitido == 1)
//   {
//     acessoLiberado();
//     delay(500);
//   }
//   else
//   {
//     acessoNegado();
//     delay(500);
//   }
// }

void connectWifi()
{
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println(String("Attempting to connect to SSID: ") + String(WIFI_SSID));

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("WIFI connected!!!");
}

void connectBroker()
{
  int TryCount = 0;
  Serial.print("MQTT connecting ");
  while (!client.connected())
  {
    if (client.connect(DEVICE_NAME))
    {
      Serial.println("connected!");
    }
    else
    {
      TryCount += 1;
      Serial.println("client foi desconectado!! ");
      Serial.print("failed, reason -> ");
      Serial.println(client.state());
      delay(1000);
      if (TryCount == 10)
        ESP.restart();

      Serial.println("contador");
      Serial.println((int)TryCount);
      // break;
    }
  }
  client.setBufferSize(1024);
}

void checkConnection()
{
  if (!client.connected())
  {
    connectWifi();
    connectBroker();
  }
  else
  {
    client.loop();
    if (millis() - lastMillis > 5000)
    {
      lastMillis = millis();
    }
  }
  now = time(nullptr);
}


void setup()
{
  Serial.begin(115200);
  client.setServer(MQTT_HOST, 1883);
  connectWifi();
  NTPConnect();
  SPI.begin();
  //mfrc522.PCD_Init();

  pinMode(led,OUTPUT);
  Leitos::setupBegin();
  Leitos::setupPressHandle();
}

void loop()

{
  checkConnection();
  Leitos::loopButtons();

  
  // Rfid();
}