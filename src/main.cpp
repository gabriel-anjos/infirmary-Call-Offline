#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <MFRC522.h>
#include <ArduinoJson.h>
#include <time.h>
#include "secrets.h"
#include "leitos.hpp"
#include "connectionWifi.h"
//#define RST_PIN D3
//#define SS_PIN D4
// #define leitoEnable01 D7
// #define leitoEnable02 D6
// #define leitoEnable03 D8
// #define leitoDisable01 D5 
// #define leitoDisable02 D3
// #define leitoDisable03 D2
//#define ButtonSend D6
//#define ButtonDisable D4



// int IdLeito = 8;
// int Posto_ref = 1;
// String thing_ref = "EmergencyCall";
String convert = "";
String conteudo = "";
String TagsCadastradas[] = {"06 8e 67 a5", "6d fc e8ab"};
String access = "denied!";
int TIME_ZONE = 4;
int Permitido = 0;
//int StatusButton = 0;

//int sendStatus = 0;

unsigned long lastMillis = 0;
unsigned long previousMillis = 0;
const long interval = 5000;

//#define AWS_IOT_PUBLISH_TOPIC "EmergencyCall_Leitos"

//MFRC522 mfrc522(SS_PIN, RST_PIN);
//WiFiClientSecure net;

BearSSL::X509List cert(cacert);
BearSSL::X509List client_crt(client_cert);
BearSSL::PrivateKey key(privkey);

//PubSubClient client(net);

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

// void sendMessage()
// {
//   StaticJsonDocument<512> doc;
//   doc["ID"] = IdLeito;
//   doc["Status"] = StatusButton;
//   doc["posto-ref"] = Posto_ref;
//   doc["thingRef"] = thing_ref;
//   char jsonBuffer[700];
//   serializeJson(doc, jsonBuffer);
//   client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
//   Serial.println(jsonBuffer);
// }

void acessoLiberado()
{
  Serial.println("");
  Serial.println("Access granted!");
  Serial.println("Tag Cadastrada: " + conteudo);
  //StatusButton = 2;
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

// void HandleButtonActive()
// {
  
//   if (digitalRead(leitoEnable03) == HIGH)
//   {
//     ButtonPress = 1;
//     ButtonReleased = 0;
//   }
//   else
//   {
//     ButtonReleased = 1;
//   }
//   if ((ButtonPress == 1) && (ButtonReleased == 1))
//   {
//     ButtonPress = 0;
//     ButtonReleased = 0;
//     StatusButton = 1;

//     //sendMessage();
//     Serial.println("sendddd");
//     delay(500);
//   }
// }

// void HandleButtonDisable()
// {

//   if (digitalRead(leitoDisable03) == HIGH)
//   {
//     ButtonPressDisable = 1;
//     ButtonReleasedDisable = 0;
//   }
//   else
//   {
//     ButtonReleasedDisable = 1;
//   }
//   if ((ButtonPressDisable == 1) && (ButtonReleasedDisable == 1))
//   {
//     ButtonPressDisable = 0;
//     ButtonReleasedDisable = 0;
//     StatusButton = 0;
//     //sendMessage();
//     Serial.println("disableee");
//     delay(500);
//   }
// }

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
  delay(3000);
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
    if (client.connect(THINGNAME))
    {
      Serial.println("connected!");
    }
    else
    {
      TryCount += 1;
      Serial.println("client foi desconectado!! ");
      Serial.print("failed, reason -> ");
      Serial.println(client.state());
      delay(2000);
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
  client.setServer(MQTT_HOST, 8883);
  net.setTrustAnchors(&cert);
  net.setClientRSACert(&client_crt, &key);
  connectWifi();
  NTPConnect();
  SPI.begin();
  //mfrc522.PCD_Init();
  //pinMode(ButtonSend, INPUT);
  //pinMode(ButtonDisable, INPUT);
  pinMode(leitoEnable01, INPUT);
  pinMode(leitoDisable01, INPUT);
  pinMode(leitoEnable02, INPUT);
  pinMode(leitoDisable02, INPUT);
  pinMode(leitoEnable03, INPUT);
  pinMode(leitoDisable03, INPUT);


}

void loop()

{
  checkConnection();
  
  //Leitos::buttonActiveLeito01();

  //Leitos::buttonActiveLeitoteste(leitoEnable01,);

  Leitos::buttonActive();
  Leitos::buttonDisable();

  // Leitos::buttonDisableLeito01();

  // Leitos::buttonActiveLeito02();
  // Leitos::buttonDisableLeito02();

  // Leitos::buttonActiveLeito03();
  // Leitos::buttonDisableLeito03();
  
  // Rfid();
}