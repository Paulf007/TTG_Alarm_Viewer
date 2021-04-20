

void changed(Button2& btn) {
 // Serial.println (btn);
 if (btn == buttonA) {
    timer = 60;
            if (MenueDisplay == 1){             // Click == Next in Menue
                startTone(1 , 100);
                menueSelect++ ;
                startTime();
                loopMenue (menueSelect);
              if (menueSelect > 5){             // Loop Back to Top
                menueSelect = 0;

                 loopMenue (menueSelect);
              }
              
  }else{
     
      byte scr = digitalRead(TFT_BL);
      Serial.println("A clicked: ");
      
      Serial.print(scr);
      
      if (scr == 1){
        digitalWrite(TFT_BL, LOW);
        screenStatus = 0 ;
      }else{
        digitalWrite(TFT_BL, HIGH);
        linkSwitches[3] = 1;       // Activate Energy Screen even if it was off
        screenStatus = 1 ;
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

            }else if (btn == buttonB){

            }
        
         //   Serial.print("double ");
            break;
        case TRIPLE_CLICK:
        Serial.print("triple ");
        // Setup Screen Rotate
         if (btn == buttonB) {
 
          
         }
            Serial.print("triple ");

            break;
        case LONG_CLICK:



            
            break;
    }
    Serial.print("click");
    Serial.print(" (");
    Serial.print(btn.getNumberOfClicks());    
    Serial.println(")");
}
