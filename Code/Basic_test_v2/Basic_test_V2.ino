/*
  This sample code connects to 2 feeds.

*/  
  #include <ESP8266WiFi.h>
  #include "Adafruit_MQTT.h"
  #include "Adafruit_MQTT_Client.h"
  #include "SPI.h"
  #include <Adafruit_NeoPixel.h>
  #define PIN            2
  #define NUMPIXELS      3
  
  Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
    
  void setup() 
  {
    Serial.begin(115200);
    delay(10); 
    pinMode(5,INPUT);
    pinMode(16,INPUT);
   
    pixels.begin();
    pixels.setPixelColor(0,0,0,0);
    pixels.show();
  }
     
  void loop() 
  {
   if(digitalRead(5)==HIGH)
      {
          pixels.setPixelColor(0,0,75,0);
          pixels.setPixelColor(1,0,0,75);
          pixels.setPixelColor(2,75,0,0);
          pixels.show();
          tone(14, 1000);
          delay(200);
          tone(14, 800);
          delay(200);
          noTone(14);
       }
      else
      {
          noTone(14);
          pixels.setPixelColor(0,0,0,0);
          pixels.setPixelColor(1,0,0,0);
          pixels.setPixelColor(2,0,0,0);
          pixels.show(); 
      }
      if(digitalRead(16)==HIGH)
      {
          pixels.setPixelColor(0,75,0,0);
          pixels.setPixelColor(1,0,75,0);
          pixels.setPixelColor(2,0,0,75);
          pixels.show();
          tone(14, 1200);
          delay(200);
          tone(14, 1400);
          delay(200);
          noTone(14);
       }
      else
      {
          noTone(14);
          pixels.setPixelColor(0,0,0,0);
          pixels.setPixelColor(1,0,0,0);
          pixels.setPixelColor(2,0,0,0);
          pixels.show(); 
      }  
  }    
 


 
