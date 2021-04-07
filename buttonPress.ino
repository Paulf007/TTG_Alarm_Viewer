

void changed(Button2& btn) {
 // Serial.println (btn);
 if (btn == buttonA) {
    timer = 60;
            if (MenueDisplay == 1){             // Click == Next in Menue
                startTone(1 , 100);
                menueSelect++ ;
                startTime();
                 //printScreen (String(menueSelect),200,115,2);
                 loopMenue (menueSelect);
              if (menueSelect > 5){             // Loop Back to Top
                menueSelect = 0;
                 //printScreen (String(menueSelect),200,115,2);
                 loopMenue (menueSelect);
              }
              
  }else{
     
      byte scr = digitalRead(TFT_BL);
      Serial.println("A clicked: ");
      
      Serial.print(scr);
      
      if (scr == 1){
        digitalWrite(TFT_BL, LOW);
      }else{
        digitalWrite(TFT_BL, HIGH);
        startTime();
        
      }
   }    
} else if (btn == buttonB) {
  if (MenueDisplay == 1){ 
    startTone(2 , 100);
    runCommand(menueSelect);
  }else{
   
   startTone(1 , 150);
   if (linkSwitches[4] == 0){
    linkSwitches[4] = 1;
    startScrn ();
   }else  if (solPos < 5){
      solPos++;
      displayInverter ();
    }else{
      solPos = 1;
      displayInverter ();
    }
   }
   
  }

    }


/////////////////////////////////////////////////////////////////
void longClickDetected(Button2& btn) {
   // Serial.println("long click detected\n");
     if (btn == buttonA) {
      if (MenueDisplay == 0){
        startTime();
        setupMenue ();
      }else{
       menueSelect = 0;
       MenueDisplay = 0;
       startScrn ();  
      }
            
            }else if (btn == buttonB) {
             // if (energyAuto == 1){
             //   energyAuto = 0 ;
             //   printScreen ("Energy On ",170,1,1); 
             // }else{
             //   energyAuto = 1 ;
             //     printScreen ("Energy On*",170,1,1);   
              //}
             
     }
}


void handler(Button2& btn) {
  Serial.print("Click:");
  Serial.println(btn.getClickType());
    switch (btn.getClickType()) {
      
        case SINGLE_CLICK:
          if (btn == buttonA) {
                  
          }           
            break;
        case DOUBLE_CLICK:
            if (btn == buttonA) {
            //  if (scrAuto == 0){
            //    scrAuto = 1;
            //    startTime();
            //    printScreen ("Screen Auto On ",0,1,1);
               // tft.setCursor(0, 1, 1); 
                //tft.print("Screen Auto On ");
           //   }else{
           //     scrAuto = 0;
           //     printScreen ("Screen Auto Off",0,1,1);
                //tft.setCursor(0, 1, 1); 
                //tft.print("Screen Auto Off");
               
            //  }
            }else if (btn == buttonB){
           //   if (linkSwitches[3] == 1){
           //     linkSwitches[3] = 0 ;
          //      printScreen ("Audio OFF",100,1,1);
         //     }else{
         //      linkSwitches[3] = 1 ;
         //      printScreen ("Audio On",100,1,1);
         //     }
              //
            }
        
         //   Serial.print("double ");
            break;
        case TRIPLE_CLICK:
        Serial.print("triple ");
        // Setup Screen Rotate
         if (btn == buttonB) {
       //   Serial.println("triple B");
       //   byte scrR = EEPROM.read(0);
       //   if (scrR > 3){
      //      tft.setRotation(3);
       //     EEPROM.write(0, 3);
       //     EEPROM.commit();
      //      ESP.restart();
      //    }else if (scrR == 3){
      //      tft.setRotation(1);
     //       EEPROM.write(0, 1);
      //      EEPROM.commit(); 
     //       ESP.restart();
     //     }else if (scrR == 1){
      //      tft.setRotation(3);
     //       EEPROM.write(0, 3);
      //      EEPROM.commit(); 
      //      ESP.restart();
      //    }
          
         }
            Serial.print("triple ");
            //tft.fillScreen(TFT_BLACK);
            break;
        case LONG_CLICK:
         //   Serial.println(btn);


            
            break;
    }
    Serial.print("click");
    Serial.print(" (");
    Serial.print(btn.getNumberOfClicks());    
    Serial.println(")");
}
