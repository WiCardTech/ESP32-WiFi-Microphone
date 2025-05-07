/*
 * WiFi Microphone Arduino program For ESP32 (12bit@8KHz - Free Revision)
 * Rev 1.2
 * 
 * Tested with esp32 board 3.2.0 and DOIT ESP32 Devkit V1
 * 
 * WiFi configuration header File
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

#ifndef ac_H_
#define ac_H_

#define LOG_ENABLE
//#define UPDATE_IP
#define LOOP_10_S 5500000//2800000
#define MEM_SAVED   0xAB

#define AUDIO_60KBPS_TIMING     163 //166
#define AUDIO_70KBPS_TIMING     139 //142
#define AUDIO_80KBPS_TIMING     121 //125

//#define PGM_P       const char *
//#define PGM_VOID_P  const void *
//#define PSTR(s) (__extension__({static const char __c[] PROGMEM = (s); &__c[0];}))

//0-161 is allocated for AutoConnect (162 bytes)
//162-255 is free for the program (94 bytes)
#define EEP_AC_KEY        0
#define EEP_ST_SSID       1
#define EEP_ST_PASS       33
#define EEP_AP_SSID       65
#define EEP_AP_PASS       97
#define EEP_SECURE        129
#define EEP_AC_CONFIG     161

//rev 1.2
#define EEP_WM_BITRATE    162
#define EEP_WM_PACKETLEN  163
#define EEP_WM_AMP        164

#define EEP_ST_SSID_LEN   32
#define EEP_ST_PASS_LEN   32
#define EEP_AP_SSID_LEN   32
#define EEP_AP_PASS_LEN   32
#define EEP_SECURE_LEN    32

#include <WiFi.h>
#include <WebServer.h>

#include "EEPROM.h"

WebServer  Server;

bool DisableHotSpot;

char STSsid[EEP_ST_SSID_LEN]; //1-32
char STPassword[EEP_ST_PASS_LEN]; //33-64
char APSsid[EEP_AP_SSID_LEN]; //65-96
char APPassword[EEP_AP_PASS_LEN]; //97-128
char secureLink[EEP_SECURE_LEN]; //129-160

//rev 1.2
unsigned char ucWMBitrate;
unsigned char ucWMPacketLen;
unsigned char ucWMAmp;

void configPage_AC();
void init_AC();
void handle_AC();

#endif // INCLUDED
