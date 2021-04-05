void setupWifi (){
  Serial.print(F("\nStarting ConfigOnDoubleReset_minimal on ")); 
  Serial.println(ARDUINO_BOARD);
  Serial.println(ESP_WIFIMANAGER_VERSION); 

  
  drd = new DoubleResetDetector(DRD_TIMEOUT, DRD_ADDRESS);
  if (drd->detectDoubleReset()) { 
    Serial.println(F("DRD")); 
    initialConfig = true; }
  ESP_WiFiManager ESP_wifiManager("ConfigOnDoubleReset");
  if (ESP_wifiManager.WiFi_SSID() == "") { Serial.println(F("No AP credentials")); initialConfig = true; }
  if (initialConfig) {
    //Serial.println(F("Starting Config Portal"));
    ESP_wifiManager.setConfigPortalTimeout(10); 
    tft.fillScreen(TFT_BLACK);
    printScreen ("Wifi Config Active",0,30,2); 
    printScreen ("Look for ESP_******",0,55,2); 
    printScreen ("Ip:192.168.4.1/ap",0,80,2); 
    printScreen ("Active for 60s",0,105,2); 
    //digitalWrite(PIN_LED, HIGH);
    if (!ESP_wifiManager.startConfigPortal()) { Serial.println(F("Not connected to WiFi")); }
    else { Serial.println(F("connected")); }
  }
  else { WiFi.mode(WIFI_STA); WiFi.begin(); } 
  printScreen ("Start Wifi ..",0,10,2); 
  unsigned long startedAt = millis();
  //digitalWrite(PIN_LED, LOW); 
  //Serial.print(F("After waiting "));
  int connRes = WiFi.waitForConnectResult();
  float waited = (millis() - startedAt);
  
  Serial.print(waited / 1000); 
  Serial.print(F(" secs , Connection result is ")); 
  Serial.println(connRes);
  
  if (WiFi.status() != WL_CONNECTED) 
  { 
    Serial.println(F("Failed to connect"));
    printScreen ("Connection Fail",0,40,2);  
    } else { 
      printScreen ("Connected to Wifi",0,40,2); 
  IPAddress localAddr =  WiFi.localIP();
  byte oct1 = localAddr[0];
  byte oct2 = localAddr[1];
  byte oct3 = localAddr[2];
  byte oct4 = localAddr[3];
  char s[16];  
  sprintf(s, "%d.%d.%d.%d", oct1, oct2, oct3, oct4);
      printScreen (s,0,70,2); 
    Serial.print(F("Local IP: ")); 
    Serial.println(WiFi.localIP());
     printScreen ("Start MQTT ... " ,0,100,2); 
  }
}
