#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino.h>
#include <WiFiClient.h>
#include <HTTP_Method.h>



const char* ssid  = "Galaxy S2267C8";
const char* password = "nxzz5758";
String numberToText = "16308006164";

void setup() {
  // put your setup code here, to run once:
  USE_SERIAL.begin(115200);
  initWiFi();
  server.begin();
}

void initWiFi() {
    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }
    //WiFi.config(ip);
    WiFi.begin(ssid,password);
    
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to WiFi..");
    }
    Serial.println(WiFi.localIP());    
}

void loop() {
  // put your main code here, to run repeatedly:


  delay(200);
}

bool readReceiver(){
  
}



void sendText(){
  HTTPClient http;   
  http.begin(resource);  
  http.addHeader("Content-Type", "application/json");    
  String packet = "{\"value1\":\""+messageToText+"\",\"value2\":\""+numberToText+"\"}";
  int httpResponseCode = http.POST(packet);
  //int httpResponseCode = http.POST("{\"value1\":\"Message body here\",\"value2\":\"16308006164\"}");
  USE_SERIAL.println("Response Code: "+httpResponseCode);
  String response = http.getString();         
  USE_SERIAL.println("Response Code2: "+response);                
  http.end();
}
