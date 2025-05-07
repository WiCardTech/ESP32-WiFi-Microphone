/*
 * WiFi Microphone Arduino program For ESP32 (12bit@8KHz - Free Revision)
 * Rev 1.2
 * 
 * Tested with esp32 board 3.2.0 and DOIT ESP32 Devkit V1
 * 
 * Web page File
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

void streamPage() //stream page: http://192.168.4.1/s
{
  unsigned int j,k,l = 0, uiSampleSize;
  
  //client_stop = true;
  
  //rev1.2
  if(ucWMBitrate == 0)
  {
    /*Sample Rate - 6000*/
    buff[0x18] = 0x70;
    buff[0x19] = 0x17;
  }
  else if(ucWMBitrate == 1)
  {
    /*Sample Rate - 7000*/
    buff[0x18] = 0x58;
    buff[0x19] = 0x1B;
  }
  else //if(ucWMBitrate == 2)
  {
    /*Sample Rate - 8000*/
    buff[0x18] = 0x40;
    buff[0x19] = 0x1F;
  }
  
  k = buff[0x19];
  k *= 256;
  k += buff[0x18];
  uiSampleSize = k * 2;
  if(ucWMPacketLen == 0)
    uiSampleSize *= (60 * 5);
  else if(ucWMPacketLen == 1)
    uiSampleSize *= (60 * 10);
  else if(ucWMPacketLen == 2)
    uiSampleSize *= (60 * 30);
  else //if(ucWMPacketLen == 3)
    uiSampleSize *= (60 * 60);

  //Server.sendHeader("Access-Control-Allow-Origin", "origin-list");
  //Server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  Server.setContentLength(uiSampleSize + 44);
  Server.send(200, "audio/wav", "");
  
  /*header*/
  /*id*/
  buff[0] = 0x52;
  buff[1] = 0x49;
  buff[2] = 0x46;
  buff[3] = 0x46;
  /*len-8*/
  buff[4] = (uiSampleSize+36)&0xFF; /*LSB*/
  buff[5] = ((uiSampleSize+36)/0x100)&0xff;
  buff[6] = ((uiSampleSize+36)/0x10000)&0xff;
  buff[7] = ((uiSampleSize+36)/0x1000000)&0xff;
  /*WAVE*/
  buff[8] = 0x57; /*LSB*/
  buff[9] = 0x41;
  buff[0xa] = 0x56;
  buff[0xb] = 0x45;
  /*Sign*/
  buff[0xc] = 0x66; /*LSB*/
  buff[0xd] = 0x6D;
  buff[0xe] = 0x74;
  buff[0xf] = 0x20;
  /*--*/
  buff[0x10] = 0x10;//12 /*LSB*/
  buff[0x11] = 0x00;
  buff[0x12] = 0x00;
  buff[0x13] = 0x00;
  /*PCM*/
  buff[0x14] = 0x01; /*LSB*/
  buff[0x15] = 0x00;
  /*CH - 1*/
  buff[0x16] = 0x01;
  buff[0x17] = 0x00;

  /* already set */
  
  /*-*/
  buff[0x1a] = 0x00;
  buff[0x1b] = 0x00;
  /* */
  buff[0x1c] = 0x40;
  buff[0x1d] = 0x1F;
  buff[0x1e] = 0x00;
  buff[0x1f] = 0x00;
  /* sample byte - 2*/
  buff[0x20] = 0x02;
  //buff[0x20] = 0x01;
  buff[0x21] = 0x00;
  /* bit per sample - 16*/
  buff[0x22] = 0x10;
  //buff[0x22] = 0x08;
  buff[0x23] = 0x00;
  /* data */
  buff[0x24] = 0x64;
  buff[0x25] = 0x61;
  buff[0x26] = 0x74;
  buff[0x27] = 0x61;

  /* len */
  buff[0x28] = uiSampleSize&0xff;
  buff[0x29] = (uiSampleSize/0x100)&0xff;
  buff[0x2a] = (uiSampleSize/0x10000)&0xff;
  buff[0x2b] = (uiSampleSize/0x1000000)&0xff;
  
  Server.sendContent_P((const char *)buff, 44);
  
  //rev 1.2
  /*if(ucWMBitrate == 0) //60kbps
    ulTimer2 = micros() - AUDIO_60KBPS_TIMING;
  else if(ucWMBitrate == 1) //70kbps
    ulTimer2 = micros() - AUDIO_70KBPS_TIMING;
  else //if(ucWMBitrate == 2) //80kbps
    ulTimer2 = micros() - AUDIO_80KBPS_TIMING;*/

  ulTimer2 = micros();
  ulTimer1 = micros();
  for(k = 0; k < uiSampleSize; k++)
  {
    unsigned int x = 0;
    while(x < 8000 && k < uiSampleSize)
    {
      //wdt_reset();
      yield();
      
      ulTimer1 = micros();
      if((ulTimer1 - ulTimer2) > 800)
        l = 0;
      else
      {
        if(l == 12000)
        {
          k = uiSampleSize;
          
#ifdef LOG_ENABLE
          Serial.println("Connection interrupted!");
#endif
          
          break;
        }
          
        l++;
  
        //rev 1.2
        if(ucWMBitrate == 0) //60kbps
        {
            ulTimer1 = micros();
            if((ulTimer1 - ulTimer2) < AUDIO_60KBPS_TIMING)
              delayMicroseconds(AUDIO_60KBPS_TIMING - (ulTimer1 - ulTimer2));
        }
        else if(ucWMBitrate == 1) //70kbps
        {
            ulTimer1 = micros();
            if((ulTimer1 - ulTimer2) < AUDIO_70KBPS_TIMING)
              delayMicroseconds(AUDIO_70KBPS_TIMING - (ulTimer1 - ulTimer2));
        }
        else //if(ucWMBitrate == 2) //80kbps
        {
            ulTimer1 = micros();
            if((ulTimer1 - ulTimer2) < AUDIO_80KBPS_TIMING)
              delayMicroseconds(AUDIO_80KBPS_TIMING - (ulTimer1 - ulTimer2));
        }
      }
  
      ulTimer2 = micros();
      j = analogRead(33);
  
      if(j > 4095)
        j = 4095;

      j *= 8;

      /*if(j >= 2048)
        j -= 2048;
      else
        j = 4096 - j;
        
      j *= 16;*/
      
      //rev 1.2
      /*if(ucWMAmp == 1)
      {
        if(j >= 16384)
          j = 32767;
        else
          j *= 2;
      }
      else if(ucWMAmp == 2)
      {
        if(j >= 8192)
          j = 32767;
        else
          j *= 4;
      }*/
      
      buff[x] = j & 0xFF;
      x++;
      buff[x] = (j >> 8) & 0xFF;
      x++;
    }
    
    Server.sendContent_P((const char *)buff, x);
  }

  Server.client().stop();
}

void calPage() //calibration page: http://192.168.4.1/cal
{
  if(Server.arg("s") != NULL)
  {
    unsigned int j,k;
    
    Server.setContentLength(800);

    Server.send(200, "image/jpeg", "");

    for(k = 0; k < 800; k++)
    {
      //wdt_reset();
      yield();
      j = analogRead(33);

      if(j > 4095)
        j = 4095;

      j /= 16;
      
      buff[k] = j;
    }
    Server.sendContent_P((const char *)buff, 800);
    Server.client().stop();
  }
  else
  {
    //rev 1.2
    Server.send(200, "text/html", "<html><head><title>WiCard-WiFi Microphone</title> <meta content='text/html;charset=utf-8' http-equiv='Content-Type'/><meta content='utf-8' http-equiv='encoding'/><style type='text/css'>body{background:#00E0F0;color:#777}.container{max-width: 95%;width: 100%;margin: 0 auto}.content{margin: 10px;}#C{width: 100%;}.inner{background: #F9F9F9;padding: 30px 25px;margin: 70px 0;box-shadow: 0 0 20px 0 rgba(0, 0, 0, 0.2), 0 5px 5px 0 rgba(0, 0, 0, 0.24);}input{width: 100%;margin: 5px 0 10px;padding: 10px;}</style></head><body><div class='container'><div class='inner'><div style='text-align:center'><a href='https://store.wicard.net'><img src='data:image/png;base64,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'/></a></div><div class='content'> <canvas id='C' width='1000' height='256' style='border:1px solid #d3d3d3;'>Your browser does not support the HTML5 canvas tag. </canvas></div><div id='num'></div></div></div><script>var init=0;var c=document.getElementById('C');var ctx=c.getContext('2d');var intval=setInterval(loadFrame,1000);var a, i;function loadFrame(){clearInterval(intval); if(init==0){init=1;for(i=0; i < 94; i++){ctx.beginPath();ctx.moveTo(i, 128);ctx.lineTo(i+1, 128);ctx.stroke();}for(i=905; i < 999; i++){ctx.beginPath();ctx.moveTo(i, 128);ctx.lineTo(i+1, 128);ctx.stroke();}}if (window.XMLHttpRequest) xhr=new XMLHttpRequest(); else xhr=new ActiveXObject('Microsoft.XMLHTTP'); xhr.open('GET', '?s=0', true); xhr.responseType='arraybuffer'; xhr.onreadystatechange=function(){if (xhr.readyState==4 && xhr.status==200){var a=new Uint8Array(xhr.response); if(a.length==800){var i;ctx.clearRect(99,0,802,256);for(i=0; i < 799; i++){ctx.beginPath();ctx.moveTo(i+100, (255-a[i]));ctx.lineTo(i+101, (255-a[i+1]));ctx.stroke();}intval=setInterval(loadFrame,200)}else alert('error! please refresh...');}}; xhr.send();}</script></body></html>");
  }
}

void rootPage() //root page: http://192.168.4.1/
{
  //secret link bug fixed-rev 1.2
  Server.send(200, "text/html", "<html><head><title>WiCard-WiFi Microphone</title> <meta content='text/html;charset=utf-8' http-equiv='Content-Type'/><meta content='utf-8' http-equiv='encoding'/><style type='text/css'>body{background:#00E0F0;color:#777}.container{max-width: 95%;width: 100%;margin: 0 auto}.content{margin: auto; width: min-content;}.inner{background: #F9F9F9;padding: 30px 25px;margin: 70px 0;box-shadow: 0 0 20px 0 rgba(0, 0, 0, 0.2), 0 5px 5px 0 rgba(0, 0, 0, 0.24);}</style></head><body><div class='container'><div class='inner'><div style='text-align:center'><a href='https://store.wicard.net'><img src='data:image/png;base64,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'/></a></div><br/> <div class='content'><audio controls><source type='audio/wav' id='player'/>Your browser does not support the audio tag.</audio></div></div></div><script>function setSRC(){var u=window.location.href; var p=document.getElementById('player'); if(u[u.length - 1]=='/') u=u + 's'; else u=u + '/s'; p.src=u;}setSRC(); </script></body></html>");
}
