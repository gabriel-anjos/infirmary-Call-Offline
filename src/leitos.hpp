#include <iostream>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "Button2.h"

WiFiClientSecure net;


PubSubClient client(net);

Button2 button1,button2,button3,button4;
//depois separar os nomes para buttonEnable1,buttonDisable1.....


#define AWS_IOT_PUBLISH_TOPIC "EmergencyCall_Leitos"

#define leitoEnable01 D7
#define leitoEnable02 D6
#define leitoEnable03 D8


#define leitoDisable01 D5 
#define leitoDisable02 D3
#define leitoDisable03 D2


//int ButtonPressEnableLeito01,ButtonPressEnableLeito02,ButtonPressEnableLeito03 = 0;
//int ButtonReleasedEnableLeito01,ButtonReleasedEnableLeito02,ButtonReleasedEnableLeito03 = 0;

//int ButtonPressDisableLeito01,ButtonPressDisableLeito02,ButtonPressDisableLeito03 = 0;
//int ButtonReleasedDisableLeito01,ButtonReleasedDisableLeito02,ButtonReleasedDisableLeito03 = 0;

//int ButtonPressDisableLeito01 = 8;


int idLeito01 = 1;
int idLeito02 = 9;
int idLeito03 = 3;

int postoRef = 1;

////nt statusbutton01,statusbutton02,statusbutton03 = 0;

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


// static void buttonActiveLeito(const uint8_t button, int idleito)
// {
//   int ButtonPressEnableLeito01 = 0;
//   int ButtonReleasedEnableLeito01 = 0;
//   int statusButton = 1;

//   if (digitalRead(button) == HIGH)
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

//     sendMessage(idleito,statusButton,postoRef);
//     Serial.println("sendddd000111");
//     delay(500);
//   }
// }

// static void buttonDisableLeito(const uint8_t button, int idleito)
// {
  
//   int statusButton = 0;
//   int id = idleito;

//   if(id == idLeito01){

//     if (digitalRead(button) == HIGH)
//     {
//       ButtonPressDisableLeito01 = 1;
//       ButtonReleasedDisableLeito01 = 0;
//       //buttonPressDisable = 1;
//       //buttonReleasedDisable = 0;

//     }
//     else
//     {
//       ButtonReleasedDisableLeito01 = 1;
//     // buttonReleasedDisable = 1;

//     }
//     //if ((buttonPressDisable == 1) && (buttonReleasedDisable == 1))
//     if ((ButtonPressDisableLeito01 == 1) && (ButtonReleasedDisableLeito01 == 1))

//     {
//       //buttonPressDisable = 0;
//       //buttonReleasedDisable = 0;
//       ButtonPressDisableLeito01 = 0;
//       ButtonReleasedDisableLeito01 = 0;

//       sendMessage(idleito,statusButton,postoRef);

//       Serial.println("disableee00011");
//       delay(500);
//     }

//   }



  
//}

int ttt(Button2 t){
  int tid;
  tid = t.getID();
  return tid;
}

static void activeCall(Button2& btn){
  int statusButton=1;
  if(btn == button1){
    int id =0;
    button1.setID(idLeito01);
    id = button1.getID();
    Serial.println((int)id);
    sendMessage(id,statusButton,postoRef);
  }else if(btn == button2){
    int id =0;
    button2.setID(idLeito02);
    id = button2.getID();
    Serial.println((int)id);
    sendMessage(id,statusButton,postoRef);
  }
  
}

static void disableCall(Button2& btn){
  int statusButton=0;
  if(btn == button1){
    int id =0;
    button1.setID(idLeito01);
    id = button1.getID();
    Serial.println((int)id);
    sendMessage(id,statusButton,postoRef);
  }else if(btn == button2){
    int id =0;
    button2.setID(idLeito02);
    id = button2.getID();
    Serial.println((int)id);
    sendMessage(id,statusButton,postoRef);
  }
  
}

static void setupPressHandleActive(){
  button1.setPressedHandler(Leitos::activeCall);
  button2.setPressedHandler(Leitos::activeCall);
}

static void setupPressHandleDisable(){
  button1.setPressedHandler(Leitos::disableCall);
  button2.setPressedHandler(Leitos::disableCall);
}

static void setupBeginEnable(){
  button1.begin(leitoEnable01,INPUT,false, false);
  button2.begin(leitoEnable02,INPUT,false, false);
}

static void setupBeginDisable(){
  button1.begin(leitoDisable01,INPUT,false, false);
  button2.begin(leitoDisable02,INPUT,false, false);
}


public:

static void setupPressHandle(){
 Leitos::setupPressHandleActive();
 Leitos::setupPressHandleDisable();

}

static void setupBegin(){
  Leitos::setupBeginEnable();
  Leitos::setupBeginDisable();
}





static void buttonActive(){

  //Leitos::buttonActiveLeito(leitoEnable01,idLeito01);
  // Leitos::buttonActiveLeito(leitoEnable02,idLeito02);
  // Leitos::buttonActiveLeito(leitoEnable03,idLeito03);

}

static void buttonDisable(){

 // Leitos::buttonDisableLeito(leitoDisable01,idLeito01);
  // Leitos::buttonDisableLeito(leitoDisable02,idLeito02);
  // Leitos::buttonDisableLeito(leitoDisable03,idLeito03);

}


// // static void buttonActiveLeito01()
// // {
  
// //   int statusButton = 1;

// //   if (digitalRead(leitoEnable01) == HIGH)
// //   {
// //     ButtonPressEnableLeito01 = 1;
// //     ButtonReleasedEnableLeito01 = 0;
// //   }
// //   else
// //   {
// //     ButtonReleasedEnableLeito01 = 1;
// //   }
// //   if ((ButtonPressEnableLeito01 == 1) && (ButtonReleasedEnableLeito01 == 1))
// //   {
// //     ButtonPressEnableLeito01 = 0;
// //     ButtonReleasedEnableLeito01 = 0;

// //     sendMessage(idLeito01,statusButton,postoRef);
// //     Serial.println("sendddd000111");
// //     delay(500);
// //   }
// // }

// static void buttonActiveLeito02()
// {
//   int statusButton = 1;

//   if (digitalRead(leitoEnable02) == HIGH)
//   {
//     ButtonPressEnableLeito02 = 1;
//     ButtonReleasedEnableLeito02 = 0;
//   }
//   else
//   {
//     ButtonReleasedEnableLeito02 = 1;
//   }
//   if ((ButtonPressEnableLeito02 == 1) && (ButtonReleasedEnableLeito02 == 1))
//   {
//     ButtonPressEnableLeito02 = 0;
//     ButtonReleasedEnableLeito02 = 0;

//     sendMessage(idLeito02,statusButton,postoRef);

//     Serial.println("sendddd0000222");
//     delay(500);
//   }
// }

// static void buttonActiveLeito03()
// {
//   int statusButton = 1;
  
//   if (digitalRead(leitoEnable03) == HIGH)
//   {
//     ButtonPressEnableLeito03 = 1;
//     ButtonReleasedEnableLeito03 = 0;
//   }
//   else
//   {
//     ButtonReleasedEnableLeito03 = 1;
//   }
//   if ((ButtonPressEnableLeito03 == 1) && (ButtonReleasedEnableLeito03 == 1))
//   {
//     ButtonPressEnableLeito03 = 0;
//     ButtonReleasedEnableLeito03 = 0;
//     sendMessage(idLeito03,statusButton,postoRef);

//     Serial.println("sendddd000333");
//     delay(500);
//   }
// }

// // static void buttonDisableLeito01()
// // {
// //   int statusButton = 0;

// //   if (digitalRead(leitoDisable01) == HIGH)
// //   {
// //     ButtonPressDisableLeito01 = 1;
// //     ButtonReleasedDisableLeito01 = 0;
// //   }
// //   else
// //   {
// //     ButtonReleasedDisableLeito01 = 1;
// //   }
// //   if ((ButtonPressDisableLeito01 == 1) && (ButtonReleasedDisableLeito01 == 1))
// //   {
// //     ButtonPressDisableLeito01 = 0;
// //     ButtonReleasedDisableLeito01 = 0;
// //     sendMessage(idLeito01,statusButton,postoRef);

// //     Serial.println("disableee00011");
// //     delay(500);
// //   }
// // }

// static void buttonDisableLeito02()
// {
//   int statusButton = 0;
  
//   if (digitalRead(leitoDisable02) == HIGH)
//   {
//     ButtonPressDisableLeito02 = 1;
//     ButtonReleasedDisableLeito02 = 0;
//   }
//   else
//   {
//     ButtonReleasedDisableLeito02 = 1;
//   }
//   if ((ButtonPressDisableLeito02 == 1) && (ButtonReleasedDisableLeito02 == 1))
//   {
//     ButtonPressDisableLeito02 = 0;
//     ButtonReleasedDisableLeito02 = 0;
//     sendMessage(idLeito02,statusButton,postoRef);

//     Serial.println("disableee000222");
//     delay(500);
//   }
// }

// static void buttonDisableLeito03()
// {
//   int statusButton = 0;

//   if (digitalRead(leitoDisable03) == HIGH)
//   {
//     ButtonPressDisableLeito03 = 1;
//     ButtonReleasedDisableLeito03 = 0;
//   }
//   else
//   {
//     ButtonReleasedDisableLeito03 = 1;
//   }
//   if ((ButtonPressDisableLeito03 == 1) && (ButtonReleasedDisableLeito03 == 1))
//   {
//     ButtonPressDisableLeito03 = 0;
//     ButtonReleasedDisableLeito03 = 0;
//     sendMessage(idLeito03,statusButton,postoRef);

//     Serial.println("disableee000333");
//     delay(500);
//   }
// }

};
