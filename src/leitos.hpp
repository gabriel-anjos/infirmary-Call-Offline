#include <iostream>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include "Button2.h"
#include <string.h>

WiFiClient wifiClient;
PubSubClient client(wifiClient);

Button2 activeButton01,activeButton02,activeButton03,disableButton01,disableButton02,disableButton03;
//depois separar os nomes para buttonEnable1,buttonDisable1.....


#define AWS_IOT_PUBLISH_TOPIC "EmergencyCall_Leitos"
#define led D0

#define leitoEnable01 D7 
#define leitoEnable02 D8
#define leitoEnable03 D1


#define leitoDisable01 D5 
#define leitoDisable02 D6
#define leitoDisable03 D2


int idLeito01 = 4;
int idLeito02 = 5;
int idLeito03 = 6;

int postoRef = 1;



class Leitos
{

  private:

  static void sendMessage(int idLeito , int statusButton, int postoRef )
  {
    StaticJsonDocument<512> doc;
    doc["id"] = idLeito;
    doc["status"] = statusButton;
    doc["posto_ref"] = postoRef;
    char jsonBuffer[700];
    serializeJson(doc, jsonBuffer);
    client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
    Serial.println(jsonBuffer);
  }


  static void handleIdDisable(Button2 t,int id){
    int statebutton = 0;
    int id3=0;
    t.setID(id);
    id3=t.getID();
    sendMessage(id3,statebutton,postoRef);
  }

  static void handleIdActive(Button2 t,int id){
    int statebutton = 1;
    int id2=0;
    t.setID(id);
    id2=t.getID();
    sendMessage(id2,statebutton,postoRef);
  }

  static void activeCall(Button2& btn){
    if(btn == activeButton01){
    
      handleIdActive(activeButton01,idLeito01);
    }else if(btn == activeButton02){
    
      handleIdActive(activeButton02,idLeito02);

    }else if(btn == activeButton03){

      handleIdActive(activeButton03,idLeito03);

    }
    
  }



  static void disableCall(Button2& btn){
    if(btn == disableButton01){
    
      handleIdDisable(disableButton01,idLeito01);
    }else if(btn == disableButton02){
    
      handleIdDisable(disableButton02,idLeito02);

    }else if(btn == disableButton03){
    
      handleIdDisable(disableButton03,idLeito03);

    }
    
  }

  static void setupPressHandleActive(){
    activeButton01.setPressedHandler(Leitos::activeCall);
    activeButton02.setPressedHandler(Leitos::activeCall);
    activeButton03.setPressedHandler(Leitos::activeCall);

  }

  static void setupPressHandleDisable(){\
    disableButton01.setPressedHandler(Leitos::disableCall);
    disableButton02.setPressedHandler(Leitos::disableCall);
    disableButton03.setPressedHandler(Leitos::disableCall);

  }
  /// Quando nao for utilizar o botao desativalo, adicionando duas barras ao começo da linha.
  static void setupBeginEnable(){
    activeButton01.begin(leitoEnable01,INPUT_PULLUP,false, true);    //comentar essa linha se nao for utilizar o botao 1
    activeButton02.begin(leitoEnable02,INPUT_PULLUP,false, true);    //comentar essa linha se nao for utilizar o botao 2
    activeButton03.begin(leitoEnable03,INPUT_PULLUP,false, true);    //comentar essa linha se nao for utilizar o botao 3

  }

  /// Quando nao for utilizar o botao desativalo, adicionando duas barras ao começo da linha.
  static void setupBeginDisable(){
    disableButton01.begin(leitoDisable01,INPUT_PULLUP,false, true);   //comentar essa linha se nao for utilizar o botao 1
    disableButton02.begin(leitoDisable02,INPUT_PULLUP,false, true);   //comentar essa linha se nao for utilizar o botao 2
    disableButton03.begin(leitoDisable03,INPUT_PULLUP,false, true);   //comentar essa linha se nao for utilizar o botao 3

  }
  /// Quando nao for utilizar o botao desativalo, adicionando duas barras ao começo da linha.

  static void loopButtonEnable(){
    activeButton01.loop();        //comentar essa linha se nao for utilizar o botao 1
    activeButton02.loop();        //comentar essa linha se nao for utilizar o botao 2
    activeButton03.loop();        //comentar essa linha se nao for utilizar o botao 3

  }
  /// Quando nao for utilizar o botao desativalo, adicionando duas barras ao começo da linha.

  static void loopButtonDisable(){
    disableButton01.loop();      //comentar essa linha se nao for utilizar o botao 1
    disableButton02.loop();      //comentar essa linha se nao for utilizar o botao 2
    disableButton03.loop();      //comentar essa linha se nao for utilizar o botao 3

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

  static void loopButtons(){
  Leitos::loopButtonEnable();
  Leitos::loopButtonDisable();
  }



};
