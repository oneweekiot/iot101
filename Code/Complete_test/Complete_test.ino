/***************************************************
 Based in the great Adafruit MQTT Library ESP8266 Example

  Must use ESP8266 Arduino from:
    https://github.com/esp8266/Arduino

  Works great with Adafruit's Huzzah ESP board & Feather
  ----> https://www.adafruit.com/product/2471
  ----> https://www.adafruit.com/products/2821

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Tony DiCola for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_NeoPixel.h>
#include <DHT.h>
#include <DHT_U.h>
#include <SPI.h>

#define DHTPIN 10     // Pin connected to the temperature sensor
#define DHTTYPE DHT11 // Sensor Type
DHT_Unified dht(DHTPIN, DHTTYPE);

#define PIN 2
#define NUMPIXELS 3
#define WLAN_SSID "WIFI NAME"
#define WLAN_PASS "WIFI PASSWORD"
#define AIO_SERVER "io.adafruit.com"
#define AIO_USERNAME "YOUR USER NAME"
#define AIO_KEY "YOUR ID"
//#define AIO_SERVERPORT 8883 // use 8883 for SSL
//WiFiClientSecure client;    // use WiFiFlientSecure for SSL
#define AIO_SERVERPORT  1883
WiFiClient client;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
Adafruit_MQTT_Publish temperature = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperature");
Adafruit_MQTT_Publish humidity = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");
Adafruit_MQTT_Publish light = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/light");
Adafruit_MQTT_Subscribe neopixel = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/neopixel");
Adafruit_MQTT_Subscribe slider = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/slider");

void setup()
{
  Serial.begin(115200);
  delay(10);
  pinMode(A0, INPUT); //Pin connected to the light Sersor (LDR)

  // Connect to WiFi access point.
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  //beeps to show Wifi connection was established
  tone(14, 1000);
  delay(200);
  tone(14, 800);
  delay(200);
  noTone(14);

  // Setup MQTT subscriptions for all feeds.
  mqtt.subscribe(&neopixel);
  mqtt.subscribe(&slider);

  dht.begin();

  pixels.begin();                   //initialize the neoPixels
  pixels.setPixelColor(0, 0, 0, 0); //set the 1st neoPixel color to nothing
  pixels.setPixelColor(1, 0, 0, 0); //set the 2nd neoPixel color to nothing
  pixels.setPixelColor(2, 0, 0, 0); //set the 3rd neoPixel color to nothing
  pixels.show();                    //display the colors set in the previous lines
}

void loop()
{
  MQTT_connect();
  sensors_event_t event;

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(10000)))
  {
    //inside this while loop we'll check if there is any new information to feeds we subscribe
    //limited to 5 subscriptions by default

    if (subscription == &slider)
    {
      Serial.println("");
      Serial.print("New Slider value: ");
      Serial.println((char *)slider.lastread);
      uint16_t sliderval = atoi((char *)slider.lastread); 
      // convert string read to a number
      // http://www.cplusplus.com/reference/cstdlib/atoi/
      if (sliderval > 500)
      {
        digitalWrite(5, 1);
        tone(14, 1000);
      }
      else
      {
        digitalWrite(5, 0);
        noTone(14);
      }
    }

    if (subscription == &neopixel)
    {
      Serial.println("");
      Serial.print("New NeoPixel value: ");
      Serial.print((char *)neopixel.lastread);
      //convet Hex to RGB using a RIGHT SHIFT operation
      //more details at: https://processing.org/reference/rightshift.html
      String hexstring = ((char *)neopixel.lastread);
      long number = (long)strtol(&hexstring[1], NULL, 16);
      int r = number >> 16;
      int g = number >> 8 & 0xFF;
      int b = number & 0xFF;
      Serial.print(" Converting to RGB: ");
      Serial.print("R: ");
      Serial.print(r);
      Serial.print(" G: ");
      Serial.print(g);
      Serial.print(" B: ");
      Serial.println(b);
      pixels.setPixelColor(0, r, g, b);
      pixels.setPixelColor(1, r, g, b);
      pixels.setPixelColor(2, r, g, b);
      pixels.show();
    }
  }

  // Once the subscription loop times out, it's time to publish data

  //publish light value
  float Light = analogRead(A0);
  Serial.println("");
  Serial.print("Sending light data: ");
  Serial.print(Light);
  Serial.print("...");
  if (!light.publish(Light))
  {
    Serial.println("Failed");
  }
  else
  {
    Serial.println("OK!");
  }

  //publish temperature value
  dht.temperature().getEvent(&event);
  if (!isnan(event.temperature)) //checking for non-number values BEFORE publishing
  {
    Serial.print("Sending temperature data: ");
    Serial.print(event.temperature);
    Serial.print("...");
    if (!temperature.publish(event.temperature))
    {
      Serial.println("Failed");
    }
    else
    {
      Serial.println("OK!");
    }
  }

  //publish humidity value
  dht.humidity().getEvent(&event);
  if (!isnan(event.relative_humidity)) //checking for non-number values BEFORE publishing
  {
    Serial.print("Sending humidity data: ");
    Serial.print(event.relative_humidity);
    Serial.print("...");
    if (!humidity.publish(event.relative_humidity))
    {
      Serial.println("Failed");
    }
    else
    {
      Serial.println("OK!");
    }
  }
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect()
{
  int8_t ret;
  if (mqtt.connected()) // Stop if already connected
  {
    return;
  }
  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) // connect will return 0 for connected
  {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000); // wait 5 seconds
    retries--;
    if (retries == 0)
    {
      while (1)
        ;
    }
  }
  Serial.println("MQTT Connected!");

  //beeps to show MQTT connection was established
  tone(14, 1200);
  delay(200);
  noTone(14);
  delay(50);
  tone(14, 1200);
  delay(200);
  noTone(14);
}
