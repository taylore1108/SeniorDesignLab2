#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino.h>
#include <WiFiClient.h>
#include <HTTP_Method.h>
#include <WebServer.h>
#include <ESPDateTime.h>
#include <Time.h>
#include <ESPAsyncWebServer.h>//
#include <Uri.h> //
#include <SPI.h>//
 #include <AsyncTCP.h>//
 
#define USE_SERIAL Serial
AsyncWebServer server(80);

//sms set up 
const char* resource = "https://maker.ifttt.com/trigger/TempTrigger/with/key/fOZGnZt3fxbSPMjgMfd_Xij7h7Z5Gg_B_gQv8RhImyV";
String messageToText = "The sengal has been interupted";
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

void setupDateTime() {
  // setup this after wifi connected
  // you can use custom timeZone,server and timeout
  // DateTime.setTimeZone("CST-8");
  // DateTime.setServer("asia.pool.ntp.org");
  // DateTime.begin(15 * 1000);
  // from
  /** changed from 0.2.x **/
  DateTime.setTimeZone("CST-8");
  // this method config ntp and wait for time sync
  // default timeout is 10 seconds
  DateTime.begin(/* timeout param */);
  if (!DateTime.isTimeValid()) {
    Serial.println("Failed to get time from server.");
  }
}

String makeMessage(){
  String m;
  time_t t= now();

  if(isAm(t)){
    m = "AM";
  }
  else{
    m = "PM";
  }
  String s =  "Critical Safety Event at " + hourFormat12(t) + "\:" + minute(t) + "  " + m + " on " + month(t) + "\/" + day(t) + "\/2022";
  return s;
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
