/*
  This code validates that everything is working fine.
*/
#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_NeoPixel.h>
#include <DHT.h>
#include <DHT_U.h>
#include <SPI.h>
#define PIN 2
#define NUMPIXELS 3

//declaring "pixels" as a NeoPixel
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  pinMode(5, INPUT);  //set pin 5 as an INPUT
  pinMode(16, INPUT); //same for pin 16

  Serial.begin(9600); //initialize Serial conversation at 9600 bauds per second

  pixels.begin();                   //initialize the neoPixels
  pixels.setPixelColor(0, 0, 0, 0); //set the 1st neoPixel color to nothing
  pixels.setPixelColor(1, 0, 0, 0); //set the 2nd neoPixel color to nothing
  pixels.setPixelColor(2, 0, 0, 0); //set the 3rd neoPixel color to nothing
  pixels.show();                    //display the colors set in the previous lines
}

void loop()
{
  if (digitalRead(5) == HIGH) //check state for Pin 5, where we have the first button connected
  //code that runs if the statement above is true (a.k.a. the button is pressed)
  {
    Serial.println("Button B pressed");
    pixels.setPixelColor(0, 0, 75, 0);
    pixels.setPixelColor(1, 0, 0, 75);
    pixels.setPixelColor(2, 75, 0, 0);
    pixels.show();
    tone(14, 1000);
    delay(200);
    tone(14, 800);
    delay(200);
    noTone(14);
  }
  else
  //code that runs if the statement above is false (a.k.a. the button is not pressed)
  {
    noTone(14);
    pixels.setPixelColor(0, 0, 0, 0);
    pixels.setPixelColor(1, 0, 0, 0);
    pixels.setPixelColor(2, 0, 0, 0);
    pixels.show();
  }

  if (digitalRead(16) == HIGH)
  {
    Serial.println("Button A pressed");
    pixels.setPixelColor(0, 75, 0, 0);
    pixels.setPixelColor(1, 0, 75, 0);
    pixels.setPixelColor(2, 0, 0, 75);
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
    pixels.setPixelColor(0, 0, 0, 0);
    pixels.setPixelColor(1, 0, 0, 0);
    pixels.setPixelColor(2, 0, 0, 0);
    pixels.show();
  }
}
