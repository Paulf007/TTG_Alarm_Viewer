void runCommand (byte com){
   switch (com) {
       case 4 :
       if (alarmS == 1) {
              alarmS = 0;
              loopMenue (com);
            }else{
              alarmS = 1;
              loopMenue (com); 
            }
   

       break; 
        case 0 :
            if (energyAuto == 1) {
              energyAuto = 0;
              loopMenue (com);
            }else{
              energyAuto = 1;
              loopMenue (com); 
            }
       break;    
         case 1 :
            if (scrAuto == 1) {
              scrAuto = 0;
              loopMenue (com);
            }else{
              scrAuto = 1;
              loopMenue (com); 
            }
       break;    
         case 2 :
            if (playTone == 1) {
              playTone = 0;
              loopMenue (com);
            }else{
              playTone = 1;
              loopMenue (com); 
            }
       break;    
         case 3 :
            if (energyM == 1) {
              energyM = 0;
              loopMenue (com);
            }else{
              energyM = 1;
              loopMenue (com); 
            }
       break;    
         case 5 :
          byte scrR = EEPROM.read(0);
          if (scrR > 3){
            tft.setRotation(3);
            EEPROM.write(0, 3);
            EEPROM.commit();
            ESP.restart();
          }else if (scrR == 3){
            tft.setRotation(1);
            EEPROM.write(0, 1);
            EEPROM.commit(); 
            ESP.restart();
          }else if (scrR == 1){
            tft.setRotation(3);
            EEPROM.write(0, 3);
            EEPROM.commit(); 
            ESP.restart();
          }
       break;    
   
    
  }
}

void setupMenue (){
    
   MenueDisplay = 1;
   tft.fillScreen(TFT_BLACK);
   tft.setTextColor(TFT_YELLOW, TFT_BLACK);        // Clear  Screen 
   //sprintf(info,"%s%s%s","Inv:",strData.c_str()," w");     
    char b[2];  
    String str;  
      //sprintf(sensor,"%s%s%s","Sol:",strData.c_str(),"w");
   tft.setTextColor(TFT_RED, TFT_BLACK);
   printScreen ("Energy TimeOut",0,1,2);
   printOnOff (energyAuto,200,0,2);
   tft.setTextColor(TFT_YELLOW, TFT_BLACK);
   printScreen ("Screen TimeOut",0,23,2);
   printOnOff (scrAuto,200,23,2);
   printScreen ("Audio ",0,46,2);
   printOnOff (playTone,200,46,2);
   printScreen ("Show Energy ",0,69,2);
   printOnOff (energyM,200,69,2);
   printScreen ("Alarm ",0,95,2);
   printOnOff (alarmS,200,95,2);
   printScreen ("Flip Screen ",0,115,2);
   //printScreen (String(scrR),200,95,2);


}

void loopMenue (byte loc){
  //tft.fillScreen(TFT_BLACK);
 // printScreen (String(loc),200,115,2);
 switch (loc) {
    case 0 :
       
       tft.setTextColor(TFT_YELLOW, TFT_BLACK);        // Clear  Screen 
       tft.setTextColor(TFT_RED, TFT_BLACK);
       printScreen ("Energy TimeOut",0,1,2);
       printOnOff (energyAuto,200,0,2);
       tft.setTextColor(TFT_YELLOW, TFT_BLACK);
       printScreen ("Screen TimeOut",0,23,2);
       printOnOff (scrAuto,200,23,2);
       printScreen ("Audio ",0,46,2);
       printOnOff (playTone,200,46,2);
       printScreen ("Show Energy ",0,69,2);
       printOnOff (energyM,200,69,2);
       
       //printScreen (String(scrR),200,95,2);
       printScreen ("Alarm ",0,95,2);
       printOnOff (alarmS,200,95,2);
       printScreen ("Flip Screen ",0,115,2);
    break;
  case 1 :
       //tft.fillScreen(TFT_BLACK);
       tft.setTextColor(TFT_YELLOW, TFT_BLACK);        // Clear  Screen 
       printScreen ("Energy TimeOut",0,1,2);
       printOnOff (energyAuto,200,0,2);
       tft.setTextColor(TFT_RED, TFT_BLACK);
       printScreen ("Screen TimeOut",0,23,2);
       printOnOff (scrAuto,200,23,2);
       tft.setTextColor(TFT_YELLOW, TFT_BLACK);
       printScreen ("Audio ",0,46,2);
       printOnOff (playTone,200,46,2);
       printScreen ("Show Energy ",0,69,2);
       printOnOff (energyM,200,69,2);
       
       //printScreen (String(scrR),200,95,2);
       printScreen ("Alarm ",0,95,2);
       printOnOff (alarmS,200,95,2);
       printScreen ("Flip Screen ",0,115,2);
    break;
  case 2 :
       //tft.fillScreen(TFT_BLACK);
       tft.setTextColor(TFT_YELLOW, TFT_BLACK);        
       printScreen ("Energy TimeOut",0,1,2);
       printOnOff (energyAuto,200,0,2);
       
       printScreen ("Screen TimeOut",0,23,2);
       printOnOff (scrAuto,200,23,2);
       tft.setTextColor(TFT_RED, TFT_BLACK);
       printScreen ("Audio ",0,46,2);
       printOnOff (playTone,200,46,2);
       tft.setTextColor(TFT_YELLOW, TFT_BLACK);
       printScreen ("Show Energy ",0,69,2);
       printOnOff (energyM,200,69,2);
             
       printScreen ("Alarm ",0,95,2);
       printOnOff (alarmS,200,95,2);
       printScreen ("Flip Screen ",0,115,2);
    break;
  case 3 :
      // tft.fillScreen(TFT_BLACK);
       tft.setTextColor(TFT_YELLOW, TFT_BLACK);        
       printScreen ("Energy TimeOut",0,1,2);
       printOnOff (energyAuto,200,0,2);
       
       printScreen ("Screen TimeOut",0,23,2);
       printOnOff (scrAuto,200,23,2);
       
       printScreen ("Audio ",0,46,2);
       printOnOff (playTone,200,46,2);
       tft.setTextColor(TFT_RED, TFT_BLACK);
       printScreen ("Show Energy ",0,69,2);
       printOnOff (energyM,200,69,2);
       tft.setTextColor(TFT_YELLOW, TFT_BLACK);
       printScreen ("Alarm ",0,95,2);
       printOnOff (alarmS,200,95,2);
       printScreen ("Flip Screen ",0,115,2);
    break ; 
   case 5 :
      // tft.fillScreen(TFT_BLACK);
       tft.setTextColor(TFT_YELLOW, TFT_BLACK);        
       printScreen ("Energy TimeOut",0,1,2);
       printOnOff (energyAuto,200,0,2);
       
       printScreen ("Screen TimeOut",0,23,2);
       printOnOff (scrAuto,200,23,2);
       
       printScreen ("Audio ",0,46,2);
       printOnOff (playTone,200,46,2);
       
       printScreen ("Show Energy ",0,69,2);
       printOnOff (energyM,200,69,2);

       printScreen ("Alarm ",0,95,2);
       printOnOff (alarmS,200,95,2);
       tft.setTextColor(TFT_RED, TFT_BLACK);
       printScreen ("Flip Screen ",0,115,2);
       tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    break  ;
   case 4 :
     //  tft.fillScreen(TFT_BLACK);
       tft.setTextColor(TFT_YELLOW, TFT_BLACK);        
       printScreen ("Energy TimeOut",0,1,2);
       printOnOff (energyAuto,200,0,2);
       
       printScreen ("Screen TimeOut",0,23,2);
       printOnOff (scrAuto,200,23,2);
       
       printScreen ("Audio ",0,46,2);
       printOnOff (playTone,200,46,2);
       
       printScreen ("Show Energy ",0,69,2);
       printOnOff (energyM,200,69,2);
       
       
       tft.setTextColor(TFT_RED, TFT_BLACK);
       printScreen ("Alarm ",0,95,2);
       printOnOff (alarmS,200,95,2);
       tft.setTextColor(TFT_YELLOW, TFT_BLACK);
       
       
       printScreen ("Flip Screen ",0,115,2); //("Flip Screen ",0,92,2);

       
    break;
  }
}
