void startTime(){
        startMillis = millis();
        snd = 1;
}

void SecTimer (){                       // Triggers every 1 second
 if (millis() - startSec > 1000 ){
  startSec = millis();
  displayTime ();
  displayAlarmTimeOut ();
  }
  
}

void ShowClock (){
 if (millis() - clockTimer > 650000 && clockActive == 0  ){
  tft.fillScreen(TFT_BLACK);
  clockActive = 1;
  //energyM = 0;
  }
  
}

void timeOutT(){
   unsigned long currentMillis = millis();
  if (currentMillis - startMillis > 60000 && snd == 1 ){                                  // Switch Screen off after 60 seconds 
    screenOff();
    
  }
  if (currentMillis - startMillis > 90000 && linkSwitches[3] == 0 && screenStatus == 1 ){   //linkSwitches[1] = Screen auto off
   linkSwitches[3] = 1;                                                                     // If screen is off it will not go back to solar Solar 
   startScrn (); 
   alarmActive = 0 ;
   //scrAuto = 1 ; 
  }
  
}

void displayTimeOut (){
  byte screen = digitalRead (TFT_BL);
  if (screen ==1 && linkSwitches[1] == 1){
    if (millis()- startSecMillis >= 1000){
      timer--;
      //Serial.println (timer);
      startSecMillis = millis();
      if (MenueDisplay == 1){
        printScreen (String(timer),200,115,2);
      }else{
  printScreen ("Screen Off",0,1,1);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  printScreen (String(timer),70,1,1);

  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  printScreen ("Audio",105,1,1);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  printScreen (String(linkSwitches[2]),140,1,1);

  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  printScreen ("Energy ",170,1,1);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  printScreen (String(linkSwitches[3]),215,1,1);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
        //printScreen ("Screen Off",0,1,1);
        //tft.setTextColor(TFT_RED, TFT_BLACK);
        //printScreen (String(timer),70,1,1);
        //tft.setTextColor(TFT_YELLOW, TFT_BLACK);
      }
    }
  }
}

void displayBanner (){
    printScreen ("Alarm",0,1,1);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  printScreen (String(linkSwitches[0]),70,1,1);

  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  printScreen ("Audio",105,1,1);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  printScreen (String(linkSwitches[2]),140,1,1);

  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  printScreen ("Energy ",170,1,1);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  printScreen (String(linkSwitches[3]),215,1,1);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
}
