#include <iostream>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

WiFiClientSecure net;


PubSubClient client(net);


#define AWS_IOT_PUBLISH_TOPIC "EmergencyCall_Leitos"

#define leitoEnable01 D7
#define leitoEnable02 D6
#define leitoEnable03 D8


#define leitoDisable01 D5 
#define leitoDisable02 D3
#define leitoDisable03 D2


int ButtonPressEnableLeito01,ButtonPressEnableLeito02,ButtonPressEnableLeito03 = 0;
int ButtonReleasedEnableLeito01,ButtonReleasedEnableLeito02,ButtonReleasedEnableLeito03 = 0;

int ButtonPressDisableLeito01,ButtonPressDisableLeito02,ButtonPressDisableLeito03 = 0;
int ButtonReleasedDisableLeito01,ButtonReleasedDisableLeito02,ButtonReleasedDisableLeito03 = 0;



int idLeito01 = 1;
int idLeito02 = 2;
int idLeito03 = 3;

int postoRef = 1;

int statusbutton01,statusbutton02,statusbutton03 = 0;

class Leitos
{

private:

static void sendMessage(int idLeito , int statusButton, int postoRef )
{
  StaticJsonDocument<512> doc;
  doc["ID"] = idLeito;
  doc["Status"] = statusButton;
  doc["posto-ref"] = postoRef;
  char jsonBuffer[700];
  serializeJson(doc, jsonBuffer);
  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
  Serial.println(jsonBuffer);
}


static void buttonActiveLeito(const uint8_t button, int idleito)
{
  
  int statusButton = 1;

  if (digitalRead(button) == HIGH)
  {
    ButtonPressEnableLeito01 = 1;
    ButtonReleasedEnableLeito01 = 0;
  }
  else
  {
    ButtonReleasedEnableLeito01 = 1;
  }
  if ((ButtonPressEnableLeito01 == 1) && (ButtonReleasedEnableLeito01 == 1))
  {
    ButtonPressEnableLeito01 = 0;
    ButtonReleasedEnableLeito01 = 0;

    sendMessage(idleito,statusButton,postoRef);
    Serial.println("sendddd000111");
    delay(500);
  }
}
public:

static void buttonActive(){

  Leitos::buttonActiveLeito(leitoEnable01,idLeito01);
}


// static void buttonActiveLeito01()
// {
  
//   int statusButton = 1;

//   if (digitalRead(leitoEnable01) == HIGH)
//   {
//     ButtonPressEnableLeito01 = 1;
//     ButtonReleasedEnableLeito01 = 0;
//   }
//   else
//   {
//     ButtonReleasedEnableLeito01 = 1;
//   }
//   if ((ButtonPressEnableLeito01 == 1) && (ButtonReleasedEnableLeito01 == 1))
//   {
//     ButtonPressEnableLeito01 = 0;
//     ButtonReleasedEnableLeito01 = 0;

//     sendMessage(idLeito01,statusButton,postoRef);
//     Serial.println("sendddd000111");
//     delay(500);
//   }
// }

static void buttonActiveLeito02()
{
  int statusButton = 1;

  if (digitalRead(leitoEnable02) == HIGH)
  {
    ButtonPressEnableLeito02 = 1;
    ButtonReleasedEnableLeito02 = 0;
  }
  else
  {
    ButtonReleasedEnableLeito02 = 1;
  }
  if ((ButtonPressEnableLeito02 == 1) && (ButtonReleasedEnableLeito02 == 1))
  {
    ButtonPressEnableLeito02 = 0;
    ButtonReleasedEnableLeito02 = 0;

    sendMessage(idLeito02,statusButton,postoRef);

    Serial.println("sendddd0000222");
    delay(500);
  }
}

static void buttonActiveLeito03()
{
  int statusButton = 1;
  
  if (digitalRead(leitoEnable03) == HIGH)
  {
    ButtonPressEnableLeito03 = 1;
    ButtonReleasedEnableLeito03 = 0;
  }
  else
  {
    ButtonReleasedEnableLeito03 = 1;
  }
  if ((ButtonPressEnableLeito03 == 1) && (ButtonReleasedEnableLeito03 == 1))
  {
    ButtonPressEnableLeito03 = 0;
    ButtonReleasedEnableLeito03 = 0;
    sendMessage(idLeito03,statusButton,postoRef);

    Serial.println("sendddd000333");
    delay(500);
  }
}

static void buttonDisableLeito01()
{
  int statusButton = 0;

  if (digitalRead(leitoDisable01) == HIGH)
  {
    ButtonPressDisableLeito01 = 1;
    ButtonReleasedDisableLeito01 = 0;
  }
  else
  {
    ButtonReleasedDisableLeito01 = 1;
  }
  if ((ButtonPressDisableLeito01 == 1) && (ButtonReleasedDisableLeito01 == 1))
  {
    ButtonPressDisableLeito01 = 0;
    ButtonReleasedDisableLeito01 = 0;
    sendMessage(idLeito01,statusButton,postoRef);

    Serial.println("disableee00011");
    delay(500);
  }
}

static void buttonDisableLeito02()
{
  int statusButton = 0;
  
  if (digitalRead(leitoDisable02) == HIGH)
  {
    ButtonPressDisableLeito02 = 1;
    ButtonReleasedDisableLeito02 = 0;
  }
  else
  {
    ButtonReleasedDisableLeito02 = 1;
  }
  if ((ButtonPressDisableLeito02 == 1) && (ButtonReleasedDisableLeito02 == 1))
  {
    ButtonPressDisableLeito02 = 0;
    ButtonReleasedDisableLeito02 = 0;
    sendMessage(idLeito02,statusButton,postoRef);

    Serial.println("disableee000222");
    delay(500);
  }
}

static void buttonDisableLeito03()
{
  int statusButton = 0;

  if (digitalRead(leitoDisable03) == HIGH)
  {
    ButtonPressDisableLeito03 = 1;
    ButtonReleasedDisableLeito03 = 0;
  }
  else
  {
    ButtonReleasedDisableLeito03 = 1;
  }
  if ((ButtonPressDisableLeito03 == 1) && (ButtonReleasedDisableLeito03 == 1))
  {
    ButtonPressDisableLeito03 = 0;
    ButtonReleasedDisableLeito03 = 0;
    sendMessage(idLeito03,statusButton,postoRef);

    Serial.println("disableee000333");
    delay(500);
  }
}

};
