void startTime(){
        startMillis = millis();
        snd = 1;
}

void SecTimer (){
 if (millis() - startSec > 1000 ){
  startSec = millis();
  displayTime ();
  }
  
}

void ShowClock (){
 if (millis() - clockTimer > 120000 && clockActive == 0  ){
  tft.fillScreen(TFT_BLACK);
  clockActive = 1;
  //energyM = 0;
  }
  
}

void timeOutT(){
   unsigned long currentMillis = millis();
  if (currentMillis - startMillis > 60000 && snd == 1 ){
    screenOff();
  }
  if (currentMillis - startMillis > 90000 && energyM == 0 && energyAuto == 1 ){
    Serial.println("90 Sec Done");
   energyM = 1;
   startScrn (); 
   alarmActive = 0 ;
   //scrAuto = 1 ; 
  }
  
}

void displayTimeOut (){
  byte screen = digitalRead (TFT_BL);
  if (screen ==1 && scrAuto == 1){
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
  printScreen (String(playTone),140,1,1);

  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  printScreen ("Energy ",170,1,1);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  printScreen (String(energyM),215,1,1);
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
    printScreen ("Screen Off",0,1,1);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  printScreen (String(timer),70,1,1);

  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  printScreen ("Audio",105,1,1);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  printScreen (String(playTone),140,1,1);

  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  printScreen ("Energy ",170,1,1);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  printScreen (String(energyM),215,1,1);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
}
