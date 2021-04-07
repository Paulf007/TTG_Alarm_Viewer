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

if (linkSwitches[5] == 1){
  if (topicStr.endsWith("drawstringl")) {
    digitalWrite(TFT_BL, HIGH);
      if (clockActive == 1){
      tft.fillScreen(TFT_BLACK);
      startScrn ();
    }
    alarmActive = 1 ;
    linkSwitches[3] = 0;
    //Serial.println("Energy Auto:");
    //Serial.println(energyAuto);
    if (linkSwitches[0] == 1) {    // Switch screen off after 120 sec or keep screen on with Last trigger
      //Serial.print("Start Timer:");
      //Serial.println(energyM);
      displayBanner ();
      //scrAuto = 1 ;
      startMillis = millis();
      startSecMillis = millis();
      }else{
        startTime();
      }
 
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
if (linkSwitches[3] == 1 ){
  clockTimer = millis();
  if (clockActive == 1){
    clockActive = 0;
    tft.fillScreen(TFT_BLACK);
    startScrn ();
  }
  char sensor[20]="";   
    if (topicStr.endsWith("Inverter_Watts_W")) {

     //tft.drawString("               ",20,30,GFXFF);
     //tft.drawString("Use ",20,30,GFXFF);
     //char sensor[10]="";
     inv = strData.toInt();
     //Serial.print("Int");
     //Serial.println(inv);
     displayInverter ();
     //sprintf(sensor,"%s%s%s","Inv:",strData.c_str()," w");
     //tft.drawString("                                ",1,30,GFXFF); 
     //tft.drawString(sensor,1,30,GFXFF);
     //tft.unloadFont();
  } 
//int soc = 0 ;
//int grid = 0 ;
//int bat = 0 ;
  if (topicStr.endsWith("Battery_Soc_%")) {
    soc = strData.toInt();

  }
   if (topicStr.endsWith("Solar_Watts_W")) {
    sol = strData.toInt();

  }
 

   if (topicStr.endsWith("Grid_Watts_W")) {
    grid = strData.toInt();
 
  }

   if (topicStr.endsWith("Battery_Watts_W")) {
    bat = strData.toInt();

   }

 
 }
 /*
 else if (energyAuto == 1) {
  char sensor[20]="";   
    if (topicStr.endsWith("Inverter_Watts_W")) {
     tft.setFreeFont(FSB24);
     tft.setTextSize(NULL);
     //tft.drawString("               ",20,30,GFXFF);
     //tft.drawString("Use ",20,30,GFXFF);
     //char sensor[10]="";
     sprintf(sensor,"%s%s%s","Inv:",strData.c_str()," w");
     tft.drawString("                                ",1,30,GFXFF); 
     tft.drawString(sensor,1,30,GFXFF);
     //tft.unloadFont();
  } 

  if (topicStr.endsWith("Battery_Soc_%")) {
    //char sensor[10]="";
    textString = getValue(strData, '.', 0);
    sprintf(sensor,"%s%s%s","Soc:",textString.c_str(),"%");
    printScreen (sensor,1,80,2); 
  }
   if (topicStr.endsWith("Solar_Watts_W")) {
    //char sensor[10]="";
    sprintf(sensor,"%s%s%s","Sol:",strData.c_str(),"w");
    printScreen (sensor,120,80,2); 
  }
 

   if (topicStr.endsWith("Grid_Watts_W")) {
    //char sensor[10]="";
    sprintf(sensor,"%s%s%s","Grd:",strData.c_str(),"w");
    printScreen (sensor,1,110,2); 
  }

   if (topicStr.endsWith("Battery_Watts_W")) {
    //char sensor[10]="";
    sprintf(sensor,"%s%s%s","Bat:",strData.c_str(),"w");
    printScreen (sensor,120,110,2);
   }
 
    }
    */
  } // end of block on Menue
 } // end callback
