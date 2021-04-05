/*
  MQTT Receiver for TTGO-T-DISPLAY Board
 based on @martinbateman clock code
 
 It just listens for MQTT messages and executes them
 All colors ,must be rgb565 in decimal format
 
 Currrent topics supported:
 
 fillscreen
 payload = color
 
 texttocolor
 payload = foreground,background (e.g two numbers seperated by a comma
 
 drawString
 payload = string,xPosition,YPosition,fontNumber
 
*/
/////////////////////////// Add Wifi Config Portal ///////////////////////////////
#if defined(ESP32)
  #define USE_SPIFFS            true
  #define ESP_DRD_USE_EEPROM    true
#else  
  #error This code is intended to run on the ESP32 platform! Please check your Tools->Board setting.  
#endif
#include <ESP_WiFiManager.h>                    //https://github.com/khoih-prog/ESP_WiFiManager
#define DRD_TIMEOUT             10
#define DRD_ADDRESS             0
#include <ESP_DoubleResetDetector.h>            //https://github.com/khoih-prog/ESP_DoubleResetDetector
DoubleResetDetector* drd;
const int PIN_LED       = 2;
bool      initialConfig = false;

#include <NTPClient.h>
#include <WiFiUdp.h>
/////////////////////Define Solar Data/////////////////////////////////////////////
int inv = 0 ;
int soc = 0 ;
int grid = 0 ;
int bat = 0 ;
int sol = 0 ;
byte solPos = 1 ;
/////////////////////////////////////////////////////////////////
#include <WiFi.h>
//#include <NTPClient.h>
//#include <WiFiUdp.h>
#include <PubSubClient.h>
#include <Tone32.h>
// Updater
#include "OTA.h"


//#include <Hash.h>
//#include <AsyncTCP.h>
//#include <ESPAsyncWebServer.h>
//#include <AsyncElegantOTA.h>
//AsyncWebServer server(80);
#include <EEPROM.h>
#define EEPROM_SIZE 1
#include <TFT_eSPI.h>
#include <SPI.h>
#include "Free_Fonts.h" // Include the header file attached to this sketch
TFT_eSPI tft = TFT_eSPI();                   // Invoke custom library with default width and height
unsigned long drawTime = 0;

#include "Button2.h";

#define TFT_BL          4  // Dispaly backlight control pin


// Replace with your network credentials
const char* ssid     = "PlaasGeluk";
const char* password = "PlaasGeluk11";
const char* mqtt_server = "192.168.8.30";
long lastReconnectAttempt = 0;
// Buttons
#define BUTTON_A_PIN  35
#define BUTTON_B_PIN  0

/////////////////////  Add clock /////////////////////////////////////////////
WiFiUDP ntpUDP;
//NTPClient timeClient(ntpUDP);
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 7200, 60000);
unsigned long startSec;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
char monthsOfYear[12][12] = {"Jan", "Feb", "Mar", "Apr","May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
unsigned long clockTimer;
byte clockActive = 0;
byte alarmActive = 0;


////////////////////////Screen Timer Out /////////////////////////////////////////
//  unsigned long currentMillis = millis(); // refresh counter variable
unsigned long startMillis;
byte snd = 0;
byte scrAuto = 1;
int timer = 60;
unsigned long startSecMillis;


/////////////////////////Screen Rotation///////////////////////////////////////
byte screenR = 1 ;
byte alarmS = 1;
/////////////////////////Menu ///////////////////////////////////////
byte MenueDisplay = 0;    // Activate Menue
byte menueSelect = 0;
////////////////////////////////////////////////////////////////
Button2 buttonA = Button2(BUTTON_A_PIN);
Button2 buttonB = Button2(BUTTON_B_PIN);


/////////////////////////TONE SETUP ///////////////////////////////////////
byte playTone = 1 ;
byte tn = 0 ; // On or OFf
byte runT = 0;
byte count = 0 ;
unsigned long startMTone ;
int buzz = 0 ;
byte lp = 0 ;
unsigned long toneTmer ;
/////////////////////Screen Menu///////////////////////////////////////////
int energyM = 1 ;
byte energyAuto = 1 ; // Turn Screen off Auto 

//int cheer_red = 0;
//int cheer_green = 0;
//int cheer_blue = 0;
unsigned int rgb565Decimal = 0;
//unsigned int newrgb565Decimal;
//String colourString = "not set yet";
//String newColourString;
int textColour = 0xFFFF;
int textBackColour = 0;
String textString = "00:00:00";
int textXPos = 0;  
int textYPos = 0;
int textFont = 7;
String strData;
String topicStr;



//WiFiUDP ntpUDP;
//NTPClient timeClient(ntpUDP);
WiFiClient espClient;
PubSubClient client(espClient);

//TFT_eSPI tft = TFT_eSPI();

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}






 


boolean reconnect() {

    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      printScreen ("Connected" ,0,65,2); 
      Serial.println("connected");
      client.subscribe("TTGO/#",1);
      client.subscribe("stat/victron/#",1);
      startScrn ();
      delay (1000) ;
    } 
     return client.connected();
}
    


void setup() {
  Serial.begin(115200);
  EEPROM.begin(EEPROM_SIZE);
  buttonA.setLongClickTime(1000);
  buttonB.setLongClickTime(1000);
  tn = 0;
  runT = 0 ;
  solPos = 1 ;
  //ledcWriteTone(0,400);
  //delay (200);
  //ledcWriteTone(0,0);
  // Setup buttons
  buttonA.setClickHandler(changed);
  buttonB.setClickHandler(changed);
  buttonA.setLongClickDetectedHandler(longClickDetected);
  buttonB.setLongClickDetectedHandler(longClickDetected);
  //buttonA.setLongClickHandler(handler);
  //buttonB.setLongClickHandler(handler);
  buttonA.setDoubleClickHandler(handler);
  buttonB.setDoubleClickHandler(handler);
  buttonA.setTripleClickHandler(handler);
  buttonB.setTripleClickHandler(handler);
  energyM = 1;
  scrAuto = 0;
  alarmS = 1 ;
  menueSelect = 0;
  energyAuto = 1;
  if (TFT_BL > 0) {
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
  }
  
  tft.init();

  // Setup Screen Rotation 
  byte scrR = EEPROM.read(0);
  Serial.print ("Add0:");
  Serial.println (scrR);
  if (scrR > 3){
    tft.setRotation(3);
  }else{
    tft.setRotation(scrR);
  }
  
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK); // Note: the new fonts do not draw the background colour
  tft.fillScreen(TFT_BLACK);
  //tft.drawString("Energy On",170,1,1);
  //tft.drawString("Screen Auto On ",0,1,1);
  
  setupWifi ();
  setupOTA("Alarm Viewer");
 // WiFi.begin(ssid, password);
 // while (WiFi.status() != WL_CONNECTED) {
 //   delay(500);
 // }
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  startTime();
  startSecMillis = millis();

//server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
//    request->send(200, "text/plain", "Go to /update to upgrade firmware");
//  });
  
  //AsyncElegantOTA.begin(&server);    // Start ElegantOTA
//  server.begin();
//  Serial.println("HTTP server started");
  startTone(3 , 50);
  displayInverter ();
  
  timeClient.begin();
  startSec = millis();
  clockTimer = millis();
}





void loop() {
  buttonA.loop();
  buttonB.loop();
  timeOutT();
  runTone ();
  displayTimeOut ();
  SecTimer ();
  ShowClock ();
//  displayMenue();
  //AsyncElegantOTA.loop();

#ifdef defined(ESP32_RTOS) && defined(ESP32)
#else // If you do not use FreeRTOS, you have to regulary call the handle method.
  ArduinoOTA.handle();
#endif
  
  if (!client.connected()) {
    long now = millis();
    if (now - lastReconnectAttempt > 5000) {
      lastReconnectAttempt = now;
      // Attempt to reconnect
      if (reconnect()) {
        lastReconnectAttempt = 0;
      }
    }
  } else {
    // Client connected

    client.loop();
  }




 
}


/////////////////////////////////////////////////////////////////
void onTimeout() {
  Serial.print("got timeout");
}
