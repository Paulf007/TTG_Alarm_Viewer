// byte linkSwitches[]= {energyAuto,scrAuto,  playTone , energyM, alarmS};

void runCommand (byte com){
  if (com == 5){
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
  }else{
       linkSwitches[com] = invTest(linkSwitches[com]);
       loopMenue (com); 
  }
}


void setupMenue (){
    
   MenueDisplay = 1;                               // Activate Menue
   tft.fillScreen(TFT_BLACK);
       showMenueItems (0,0,1,1,0,linkSwitches[0]);     // MenuItem , x , y , line A ,line B , ON/OFF
       showMenueItems (1,0,23,0,0,linkSwitches[1]);
       showMenueItems (2,0,46,0,0,linkSwitches[2]);
       showMenueItems (3,0,69,0,0,linkSwitches[3]);
       showMenueItems (4,0,92,0,0,linkSwitches[4]);
       printScreen (menueItems[5],0,116,2); 
}

void loopMenue (byte loc){
  menuRunner (loc);
}

void showMenueItems (int menueItm  ,  int x , int y , int lineColorA, int lineColorB , int onOff) {
  if (lineColorA == 0){
   tft.setTextColor(TFT_YELLOW, TFT_BLACK);  
  }else{
   tft.setTextColor(TFT_RED, TFT_BLACK); 
  }
  printScreen (menueItems[menueItm],x,y,2);
  printOnOff (onOff,200,y,2);
  if (lineColorB == 0){
   tft.setTextColor(TFT_YELLOW, TFT_BLACK);  
  }else{
   tft.setTextColor(TFT_RED, TFT_BLACK); 
  }
}
  int invTest (int a){
    if (a == 0){
      return 1;
    }else{
      return 0;
    }
  }

  int test(int a , int b){
    if (a == b){
      return 1;
    }else{
      return 0;
    }
  }

void menuRunner (int line){
       showMenueItems (0,0,1,test(0,line),0,linkSwitches[0]);     // MenuItem , x , y , line A ,line B , ON/OFF
       showMenueItems (1,0,23,test(1,line),0,linkSwitches[1]);
       showMenueItems (2,0,46,test(2,line),0,linkSwitches[2]);
       showMenueItems (3,0,69,test(3,line),0,linkSwitches[3]);
       showMenueItems (4,0,92,test(4,line),0,linkSwitches[4]);
       if (line == 5){
         tft.setTextColor(TFT_RED, TFT_BLACK);
         printScreen (menueItems[5],0,116,2);
       }else{
        printScreen (menueItems[5],0,116,2);
       } 
}
