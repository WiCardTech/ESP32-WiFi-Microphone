# ESP32-WiFi-Microphone
ESP32 WiFi Microphone
Introduction
This project is an ESP32 WiFi Microphone firmware arduino source code (.ino) which can play live sound and voices with up to 96Kbps (12bit @8KHz) quality. (To using more powerful WiFi microphone and voice recorder arduino project, please refer to our website: https://wicard.net/projects)
There are the following files in this project:
1-	ESP32WiFiMicrophoneFree.ino (Main handler file)
2-	AC.h – Project global variables and definitions file.
3-	AC.ino – Project WiFi settings and config file.
4-	MicPage.ino – This file contains the WiFi Microphone WebApp’s script.
Uploading the project
First open one of the files with Arduino program, then set the settings as the following image (Board revision and board type):
 (Refer to the PDF file) Figure 1-Arduino settings
•	The “Board” must be set on one of the ESP32 Modules before doing anything. 

WaveShare Sound Sensor
WaveShare sound sensor is an audio amplifier and sensor with LM386. This module is compatible with this project.
 
ESP32 WiFi Microphone Schematics
It’s suggested to use a standard 3.3V microphone module (like “WaveShare Sound Sensor”). The ADC pin (GPIO 33) of esp32 is the audio signal input. Before using the WiFi microphone, build one of the following circuits. 
Here’s a simple circuit with WaveShare Sound Sensor and ESP32 DEVKIT:
 (Refer to the PDF file) Figure 3-WaveShare and ESP32 schematic
And here’s a suggested circuit with a simple capacitive microphone, LM386, Memory module and NodeMCU:
 (Refer to the PDF file) Figure 4-LM386 and ESP32 Schematic
The ESP32 WiFi Microphone Web Application
After upload, the program will run automatically.
Then the blue LED on the board would be turned on. Then you’ll be able to see the module’s hot spot ssid via the WiFi networks in your PC or smart phone.
The default SSID is WiCardMp and the default password is 12345678. Connect and go to 192.168.4.1/config with a web browser.

The WiFi configuration page:
 (Refer to the PDF file) Figure 5-WiFi configuration
In the “Modem Configuration” section, you’re able to view/edit the SSID and password of WiFi modem/router and then click on “Save” after inserting. The module would connect to the modem after about 30 seconds in case of validity of ssid and password.
•	This page is also available via the DHCP IP of the module.
In the “Device Hot Spot Configuration” section, you can set the module hotspot’s SSID and password. Also you can set a password for the internal page with Secure Link section. (Example: the secure link is ABCD and the root page would be at 192.168.4.1/ABCD/ address)
The “Hidden HotSpot” button will set the module’s hot spot as hidden hotspot and the “Disable HotSpot when is connected to the modem” would disable the module’s hotspot, when is connected to the modem.
The stream configuration
The stream configuration is in the bottom of “config” page:
 (Refer to the PDF file) Figure 6-Stream Configuration
With “Audio Stream Bitrate” the quality of the audio stream can be set in 72, 84 or 96Kbps.
•	The signal strength must be higher for higher quality.
The “Audio Stream Packet Length” sets the stream time in 5, 10, 30 or 60 minutes.

The Audio Stream Page
This page is in the root address (192.168.4.1 or the router’s given IP) and decodes the received data from module to the audio stream.
After opening the page, wait for a few seconds for the initial file loading. Then click on the “play”.
This page records audio data to in the browser’s cache automatically. Also you can play the audio and listen to the audio lively at the same time.
 (Refer to the PDF file) Figure 7-Live Stream
The preset time is 10 minutes. After this time spent, you can refresh the page and record again.
To downloading the audio file directly, go to 192.168.4.1/s (or the router’s given IP).
•	If you close the web page, recording will be aborted.
Do not open two pages at the same time. The module can handle only one page at a time.

Microphone Calibration
There is a calibration page in “192.168.4.1/cal” which shows the audio signal. When there’s no noise and voice, the signal must be a straight horizontal line at the center of scope. So if the signal is lower than middle lines (like the following image), try to calibrate it with adding load, pull up and pull down resistors.
 (Refer to the PDF file) Figure 8-Oscilloscope
Also you can see the input audio signal shape in this page and filter it with load and decoupling capacitors if it is necessary:
 (Refer to the PDF file) Figure 9-Audio Signal
The audio signal uses 8000Hz sample rate with 12 bits resolution which gives a low quality souond. To receive more quality sounds, please use the newer revisions of this project: https://wicard.net/projects 

To opening the calibration page:
-	Close the root page (192.168.0.113), close all the pages and then after a few seconds open calibration page (192.168.0.113/cal) or Re-start the module, then open calibration page after the module connected to the modem.
•	The WiFi signal strength takes effect on the module capability and the audio streams.
The ADC voltage must be between 0 and 3.3V (power source).

Other Revisions
* ESP32 WiFi Microphone (12bit@8KHz - Free Revision) --> https://wicard.net/projects/Arduino/ESP32-ESP8266/ESP32%20WiFi%20Microphone%20free%20arduino%20source%20code
 * ESP8266 WiFi Microphone (10bit@8KHz - Free Revision) --> https://wicard.net/projects/Arduino/ESP32-ESP8266/ESP8266%20WiFi%20Microphone%20free%20arduino%20source%20code
 * ESP32 WiFi Microphone and Recorder --> https://wicard.net/projects/Arduino/ESP32-ESP8266/esp32-voice-recorder
 * ESP8266 WiFi Microphone and Recorder --> https://wicard.net/projects/Arduino/ESP32-ESP8266/nodemcu-voice-recorder-esp8266
 * ESP32-Cam IP-Camera (Free Revision) --> https://wicard.net/projects/Arduino/ESP32-ESP8266/esp32cam-ipcamera-bin
 * ESP32-Cam HD DashCam --> https://wicard.net/projects/Arduino/ESP32-ESP8266/esp32-cam-DashCam
 * ESP32-Cam CCTV --> https://wicard.net/projects/Arduino/ESP32-ESP8266/ESP32-CAM%20CCTV%20IP%20Camera
 * ESP32-Cam Camera and Microphone --> https://wicard.net/projects/Arduino/ESP32-ESP8266/spycam-video-audio-esp32cam

Revision History
1.2
- Schematic improvement
- Secure link debug
- ADC input improvement
- Output file improvement
- Selectable stream quality
- Adjustable stream time
- Adjustable software amplitude
1.1
- 10:28 frame (increased)
- Audio stream recorder and player
- 8KHz sample rate (increased)
- 12 bits resolution (increased)
- Calibration page
- The stability and quality of audio stream increased
- Suggested test circuit updated
- Bugs fixed
1.0
- 3300 miliseconds frames
- LOUD button
- 7.5KHz sample rate
- 8 bits resolution
- Internal pages secure link
- Show MAC and IP in config page
- Set module hotspot and modem’s ssid and password
- Automatically connection to the modem
- Config page
- Hidden hotspot button
- Disable hotspot button

Project Update
To receive the latest update for this project, please refer to our website:
https://wicard.net/projects
