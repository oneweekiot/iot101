# video Lessons - Preview

# Introduction
In this initial video we present the One Week IoT approach to IoT and what can you expect from the training. 

[![Introduction](Images/1.png)](https://youtu.be/6IEFBBy_xuQ)

# IoT 101 - What is IoT?
This video presents some basic concepts about IoT at a basic level. It is important to give you a better context about Iot and spark your imagination and creativity about Iot possibilities. 

[![IoT 101](Images/2.png)](https://youtu.be/_ytS9iKTOzE)

# IoT 101 - DEMO
All of the next videos will help you build your own IoT end-to-end solution and this video shows what the end result will look like, what can you expect to build and learn! 

[![DEMO](Images/3.png)](https://youtu.be/QbA_g9gALng)

# Installing the Arduino IDE
Arduino IDE (Integrated Development Environment) is the home for all development related to your device. It enables you to write, test and upload code to the device. It is the first step into firmware programming! 

[![Arduino IDE](Images/4.png)](https://youtu.be/FXCKqd-sDeQ)

# Checking your device - Device Manager
Arduino IDE installation script adds several drivers that will allow devices to communicate to your PC via Serial ports. In this step you'll check if the installation happened successfully. 

[![Device Manager](Images/5.png)](https://youtu.be/FKKNCu75aqs)

# Adding a new board to Arduino IDE - Board Definition
By default, the board you have with you - Node MCU based on the ESP8266 Microcontroller - doensn't work with Arduino IDE. It is necessary for you to add the board definition and install the drivers separately. 

[![Board Definition](Images/6.png)](https://youtu.be/JIlY62Pb1b4)

# Adding Libraries
Libraries add funcionality to your code making it simpler and faster to create your own solutions. In this step we will add 4 libraries required to the IoT end-to-end project.

[![Libraries](Images/7.png)](https://youtu.be/eJvLOV1iwD4)

# Testing the installation
At this point you should have all setup and configuration steps completed, so you can connect the board to your PC and load your first sketch into it to test. Exciting, huh? 

[![Test 1](Images/8.png)](https://youtu.be/mFJJOWeiqdg)

# Advanced testing with Serial Monitor
now you'll see that you can send data to the board (code) but you can also get information from the board via serial communication, which helps a lot when it comes to debug applications. 

[![Test 2](Images/9.png)](https://youtu.be/J5BQMXoIjxo)

# Creating your IO.Adafruit account
Create your online Adafruit account. don't worry: it's free (no credit card information required).

[![IO.Adafruit](Images/10.png)](https://youtu.be/juBTkhI94MQ)

# Creating the Topics/Feeds
The first step after creating your Adafruit Account is to create the Topics/Feeds that will get the data from the device. At is core, IO.Adafruit is an online MQTT Broker, which means you can create multiple compartments to store information (messages). 
Example: you create a topic named **temperature** to store temperature data sent from the device. When your device connects to the MQTT Broker (IO.Adafruit) it needs to tell the broker where to store the information (data) it is sending. 
The MQTT broker works based in Publishing and Subscribe model, that allows connected devices to publish (send) information to a given topic, and the MQTT broker will broadcast that message to all devices that are subscribing that same topic. 
Example: a second device subscribes to the **temperature**  topic and every time the first devie publishes a new temperature value, this second device will be notified and get the data. 

[![MQTT Topics](Images/11.png)](https://youtu.be/Sr5pvl2Hkw4)

# Sending data from the device to the Internet
It is time now to load a sample code, connect your device to wifi and your Adafruit Account, and send data to the cloud. 

[![Send Data](Images/12.png)](https://youtu.be/OG-ms2UEd5I)

# Creating an online dashboard
One nice feature of the IO.Adafruit service is the possibility to create dashboard to allow interaction with users in both displayng data and getting inputs.Lets test both.

[![Dashboard](Images/13.png)](https://youtu.be/_D-gyK-psiY)