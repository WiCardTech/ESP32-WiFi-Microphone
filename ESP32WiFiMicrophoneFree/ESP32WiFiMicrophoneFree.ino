/*
 * WiFi Microphone Arduino program For ESP32 (12bit@8KHz - Free Revision)
 * Rev 1.2
 * 
 * Tested with esp32 board 3.2.0 and DOIT ESP32 Devkit V1
 * 
 * Main File
 * 
 * Author: M. Mahdi K. Kanan (mvtdesign@gmail.com)
 * WiCardTech Engineering Group (https://wicard.net)
 * 
 * All of the revisions:
 * ESP32 WiFi Microphone (12bit@8KHz - Free Revision) --> https://wicard.net/projects/Arduino/ESP32-ESP8266/ESP32%20WiFi%20Microphone%20free%20arduino%20source%20code
 * ESP8266 WiFi Microphone (10bit@8KHz - Free Revision) --> https://wicard.net/projects/Arduino/ESP32-ESP8266/ESP8266%20WiFi%20Microphone%20free%20arduino%20source%20code
 * ESP32 WiFi Microphone and Recorder --> https://wicard.net/projects/Arduino/ESP32-ESP8266/esp32-voice-recorder
 * ESP8266 WiFi Microphone and Recorder --> https://wicard.net/projects/Arduino/ESP32-ESP8266/nodemcu-voice-recorder-esp8266
 * ESP32-Cam IP-Camera (Free Revision) --> https://wicard.net/projects/Arduino/ESP32-ESP8266/esp32cam-ipcamera-bin
 * ESP32-Cam HD DashCam --> https://wicard.net/projects/Arduino/ESP32-ESP8266/esp32-cam-DashCam
 * ESP32-Cam CCTV --> https://wicard.net/projects/Arduino/ESP32-ESP8266/ESP32-CAM%20CCTV%20IP%20Camera
 * ESP32-Cam Camera and Microphone --> https://wicard.net/projects/Arduino/ESP32-ESP8266/spycam-video-audio-esp32cam
 * 
*/

#include <time.h>
#include <Arduino.h>
#include "EEPROM.h"

#include "AC.h"

#ifdef UPDATE_IP
#include <HTTPClient.h>
#endif

unsigned int  ipTimer;
unsigned char buff[8000];
unsigned long int  ulTimer1;
unsigned long int  ulTimer2;

#ifdef UPDATE_IP
HTTPClient    http;    //Declare object of class HTTPClient
#endif

void setup()
{
  int i;

  ipTimer = 0;
  
  WiFi.mode(WIFI_OFF);
  pinMode(2, OUTPUT); //blue led
  
  pinMode(33, ANALOG);
         
  //blink for 1 second
  digitalWrite(2, LOW);
  delay(1000);
  digitalWrite(2, HIGH);

  DisableHotSpot = false;
  
  Serial.begin(115200);
  Serial.setDebugOutput(false);
  
#ifdef LOG_ENABLE
  Serial.println(" ");
  Serial.println("** WiCardTech **");
  Serial.println("** WiFi Microphone Arduino Firmware for ESP32 (Rev 1.2) **");
  Serial.println("** https://wicard.net **");
#endif

  //0-161 is allocated for AutoConnect (162 bytes)
  //162-255 is free for the program (94 bytes)
  EEPROM.begin(256);
  
  delay(1000);
  
  init_AC();
  
  // Configuring Internal Pages
  if(secureLink[0] == 0)
  {
    Server.on("/", rootPage);
    Server.on("/s", streamPage);
    Server.on("/cal", calPage);
  }
  else
  {
    Server.on("/"+((String)secureLink)+"/", rootPage);
    Server.on("/"+((String)secureLink), rootPage);//added-rev 1.2
    Server.on("/"+((String)secureLink)+"/s", streamPage);//fixed-rev 1.2
    Server.on("/"+((String)secureLink)+"/cal", calPage);//fixed-rev 1.2
  }
  
  delay(1000);
  
  Server.begin();
#ifdef LOG_ENABLE
  Serial.println("HTTP server started");
#endif

  //Your Setup code
  
#ifdef LOG_ENABLE
  Serial.println("Setup Done!");
#endif

  delay(1000);
}

//Main Loop!
void Delay10Sec()
{
  unsigned int i, j;

  unsigned long mic;
  
  for(i = 0; i < LOOP_10_S; i++)
  {
    Server.handleClient();
    
    //Your loop code
  }
}

void loop()
{
  Delay10Sec();
#ifdef LOG_ENABLE
  Serial.print("-");
#endif
  handle_AC();

#ifdef UPDATE_IP
  if(WiFi.status() == WL_CONNECTED)
  {
    if(ipTimer == 100)
    {
      http.begin("http://Your-Website");
      ipTimer = http.GET();
#ifdef LOG_ENABLE
      Serial.println("Updating IP");
      if(ipTimer>0)
      {
        Serial.print("HTTP Response code: ");
        Serial.println(ipTimer);
        Serial.println(http.getString());
      }
      else
      {
        Serial.print("Error code: ");
        Serial.println(ipTimer);
      }
#endif
      ipTimer = 0;
      http.end();  //Close connection
    }
    else
      ipTimer++;
  }
#endif
}
