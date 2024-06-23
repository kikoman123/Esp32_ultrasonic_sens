/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
 *************************************************************
  Blynk.Edgent implements:
  - Blynk.Inject - Dynamic WiFi credentials provisioning
  - Blynk.Air    - Over The Air firmware updates
  - Device state indication using a physical LED
  - Credentials reset using a physical Button
 *************************************************************/

/* Fill in information from your Blynk Template here */
/* Read more: https://bit.ly/BlynkInject */
#define BLYNK_TEMPLATE_ID "TMPL6TboEzjrC"
#define BLYNK_TEMPLATE_NAME "DistanceUltrsonicSensor"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
#define USE_ESP32_DEV_MODULE
//#define USE_ESP32C3_DEV_MODULE
//#define USE_ESP32S2_DEV_KIT
//#define USE_WROVER_BOARD
//#define USE_TTGO_T7
//#define USE_TTGO_T_OI
#include "Blynk.h"
#include "BlynkEdgent.h"

#define  trig  5
#define  echo  18

long duration;
int distance;

BlynkTimer timer;
void setup()
{
  Serial.begin(115200);
  delay(100);

  BlynkEdgent.begin();
   timer.setInterval(1000L, sendSensor);
}

void loop() {
  BlynkEdgent.run();
  timer.run();
}
void sendSensor()
{
  digitalWrite(trig, LOW);   
  delayMicroseconds(2);       
  digitalWrite(trig, HIGH); 
  delayMicroseconds(10);      
  digitalWrite(trig, LOW);   
  duration = pulseIn(echo, HIGH);   
  distance = duration * 0.034 / 2;

  Serial.print("Distance = ");    
  if(distance>=19){
  Serial.println(distance);
  }    
  else{
 Serial.println("distance loading ");
  }
 

  Blynk.virtualWrite(V0, distance);
  delay(2500);                        //Pause for 3 seconds and start measuring distance again
}

