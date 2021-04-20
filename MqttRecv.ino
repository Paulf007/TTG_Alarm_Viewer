void callback(char* topic, byte* payload, unsigned int length) {
if  (MenueDisplay != 1){
  topicStr = topic;

  //Serial.print("Message:");
  
  strData = "";
  for (int i = 0; i < length; i++) {
   // Serial.print((char)payload[i]);
    strData += (char)payload[i];
  }
  
 // Serial.println();
 // Serial.println("-----------------------");

  if (topicStr.endsWith("fillscreen")) {
       tft.fillScreen(strData.toInt());
  }  

  if (topicStr.endsWith("settextcolor")) {
    tft.setTextColor(getValue(strData, ',', 0).toInt(), getValue(strData, ',', 1).toInt());
  }    

if (linkSwitches[0] == 1){

  if (topicStr.endsWith("drawstringl")) { // Alarm Recieved and overides all
    digitalWrite(TFT_BL, HIGH);
      if (clockActive == 1){              // Check if the Clock is Showing
      tft.fillScreen(TFT_BLACK);
      clockActive = 0 ;                   // Disable Clock until timeOut
      startScrn ();                       // Show top Banner
    }
    clockTimer = millis();                // Reset Clock Banner
    alarmActive = 1 ;                     // Set Alarm Active so that no other data is displayed 
    if (linkSwitches[1] == 0){
     AlarmTimeOut = 90; 
    }else{
     AlarmTimeOut = 60; 
    }
    
    linkSwitches[3] = 0;                  // Disable Show Energy - MQTT Payloads is ignored
    startTime();                          // Start Timer to go back to inverter screen

 
    textString = getValue(strData, ',', 0);
    textXPos = getValue(strData, ',', 1).toInt();  
    textYPos = getValue(strData, ',', 2).toInt();
    textFont = getValue(strData, ',', 3).toInt();
    buzz     = getValue(strData, ',', 4).toInt();
    //tft.drawString(textString.c_str(),0,0,1); // Overwrite the text to clear it
    tft.setFreeFont(FSB24);
    tft.setTextSize(NULL);
    tft.drawString("                                ",1,30,GFXFF); 
    tft.drawString(textString.c_str(),textXPos,textYPos,GFXFF); // Overwrite the text to clear it
    startTone(buzz , 150);
    //startTime();
    //timer = 60;
    //ypos += tft.fontHeight(GFXFF);
    //tft.drawString(textString.c_str(),textXPos,textYPos,textFont); // Overwrite the text to clear it
 
  }      
  if (topicStr.endsWith("drawstrings")) {
    
    textString = getValue(strData, ',', 0);
    textXPos = getValue(strData, ',', 1).toInt();  
    textYPos = getValue(strData, ',', 2).toInt();
    textFont = getValue(strData, ',', 3).toInt();
    //tft.drawString(textString.c_str(),0,0,1); // Overwrite the text to clear it
    //tft.setFreeFont(FSB24);
    //tft.drawString(textString.c_str(),textXPos,textYPos,GFXFF); // Overwrite the text to clear it
    //ypos += tft.fontHeight(GFXFF);
    //tft.drawString(textString.c_str(),textXPos,textYPos,textFont); // Overwrite the text to clear it
    printScreen (textString.c_str(),textXPos,textYPos,textFont);
  } 

  if (topicStr.endsWith("clear")) {
    digitalWrite(TFT_BL, LOW);
    //tft.fillScreen(TFT_BLACK);
 
  } 
}



if (linkSwitches[3] == 1 ){          // Check if Solar Menue is Active 
  clockTimer = millis();            // Restart Clock Timer
  if (clockActive == 1){
    clockActive = 0;
    tft.fillScreen(TFT_BLACK);
    startScrn ();
  }
  char sensor[20]="";   
    if (topicStr.endsWith("Inverter_Watts_W")) {

     solarData[0] = strData.toInt();    // set Inverter Data
     displayInverter ();

  } 
//int soc = 0 ;
//int grid = 0 ;
//int bat = 0 ;
  if (topicStr.endsWith("Battery_Soc_%")) {
    solarData[1] = strData.toInt();

  }
   if (topicStr.endsWith("Solar_Watts_W")) {
    solarData[2]= strData.toInt();

  }
 

   if (topicStr.endsWith("Grid_Watts_W")) {
    solarData[3] = strData.toInt();
 
  }

   if (topicStr.endsWith("Battery_Watts_W")) {
    solarData[4] = strData.toInt();

   }

 
   }
  } 
 } // end callback
