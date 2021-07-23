//Developed by VIKRAM BALA. Contact: vikrambala2002@gmail.com. 
//Please contact if you wish to use for commercial purposes, and provide credit in any public usage.
//Credit can be provided with the following: "Vikram Bala, https://github.com/vbala29"

/*PART OF THIS CODE IS ATTRIBUTED TO RUI SANTOS, SEE HIS COPYRIGHT GRANT BELOW
  Rui Santos
  Complete project details at Complete project details at https://RandomNerdTutorials.com/esp8266-nodemcu-http-get-post-arduino/

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

//THIS CODE IS INTENDED TO RUN ON AN ESP8266 NODE MCU

#include <Stepper.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h> 

#define STEPS 2038

const char* ssid = "Vikram's iPhone";
const char* password = "chickenbuilder";

Stepper axesOne = Stepper(STEPS, D1, D3, D2, D4);

const char* serverName = "https://api.meteomatics.com/2021-07-14T15:05:00.000-04:00/sun_elevation:d,sun_azimuth:d/39.165681,-76.890385/json?model=mix";
const char* login = "https://jhuapl-bala:bSFZqvkCyxKE@api.meteomatics.com";
unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

double currAzimuth = 0;
double currElevation = 90;

void setup() {
  Serial.begin(9600);   // initialize serial communication at 9600 BPS
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  axesOne.setSpeed(60); //60 rpm
//  WiFi.hostname("Vikram's iPhone");
//  WiFi.begin(ssid, password);
//  Serial.println("Connecting");
//  while(WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.println("Connecting.. status: " + String(WiFi.status()));
//  }
//  Serial.println("");
//  Serial.print("Connected to WiFi network with IP Address: ");
//  Serial.println(WiFi.localIP());
//  httpGETRequest(login);
//  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
}

void loop() {
  //Send an HTTP POST request every 10 minutes
//  if ((millis() - lastTime) > timerDelay) {
//    //Check WiFi connection status
//    if(WiFi.status()== WL_CONNECTED){
//            
//      String response = httpGETRequest(serverName);
//      Serial.println(response);
//      int ind1 = response.indexOf("value");
//      int ind2 = response.indexOf("}", ind1);
//      String elevation = response.substring(ind1+2, ind2);
//
//      int ind3 = response.indexOf("value", ind2);
//      int ind4 = response.indexOf("}", ind3);
//      String azimuth = response.substring(ind3+2, ind4);      
//
//      Serial.println("Azimuth = " + azimuth + ", elevation = " + elevation);
//    }
//    else {
//      Serial.println("WiFi Disconnected");
//    }
//    lastTime = millis();
      updatePosition(60, 60);

// }

  
}

void updatePosition(double azimuth, double elevation) {
  axesOne.step(1000);
}


String httpGETRequest(const char* serverName) {
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "{}"; 
  
  if (httpResponseCode> 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
