


void displayInverter (){
     tft.setFreeFont(FSB24);
     tft.setTextSize(NULL);
     char invS  [15]="";
     char socS  [15]="";
     char solS  [15]="";
     char gridS [15]="";
     char batS  [15]="";
     sprintf(invS ,"%s%d%s","Inv:",solarData[0],"w");  
     sprintf(socS,"%s%d%s","Soc:",solarData[1],"%");
     sprintf(solS,"%s%d%s","Sol:",solarData[2],"w");
     sprintf(gridS ,"%s%d%s","Grd:",solarData[3],"w");
     sprintf(batS,"%s%d%s","Bat:",solarData[4],"w");
     //solPos = 1
     switch (solPos) {
       case 1 :
               tft.drawString("                                ",1,30,GFXFF); 
               tft.drawString(invS,1,30,GFXFF);
               printScreen (socS,1,80,2); 
               printScreen (solS,120,80,2); 
               printScreen (gridS ,1,110,2);
               printScreen (batS,120,110,2);
       break; 
       case 2 :
               tft.drawString("                                ",1,30,GFXFF); 
               tft.drawString(socS,1,30,GFXFF);
               printScreen (invS,1,80,2); 
               printScreen (solS,120,80,2); 
               printScreen (gridS ,1,110,2);
               printScreen (batS,120,110,2);
       break; 
       case 3 :
               tft.drawString("                                ",1,30,GFXFF); 
               tft.drawString(solS,1,30,GFXFF);
               printScreen (socS,1,80,2); 
               printScreen (invS,120,80,2); 
               printScreen (gridS ,1,110,2);
               printScreen (batS,120,110,2);
       break;     
       case 4 :
               tft.drawString("                                ",1,30,GFXFF); 
               tft.drawString(gridS,1,30,GFXFF);
               printScreen (socS,1,80,2); 
               printScreen (solS,120,80,2); 
               printScreen (invS,1,110,2);
               printScreen (batS,120,110,2);
       break; 
       case 5 :
               tft.drawString("                                ",1,30,GFXFF); 
               tft.drawString(batS,1,30,GFXFF);
               printScreen (socS,1,80,2); 
               printScreen (solS,120,80,2); 
               printScreen (gridS ,1,110,2);
               printScreen (invS,120,110,2);
       break;             
     }
}



void printOnOff (byte i,int x,int y,int f){
  if (i == 1){
                 tft.setFreeFont(NULL); 
                 tft.setTextSize(f);
                 tft.setCursor(x, y); 
                 tft.print("       ");
                 tft.setCursor(x, y); 
                 tft.print("On");
    
  }else{
                 tft.setFreeFont(NULL); 
                 tft.setTextSize(f);
                 tft.setCursor(x, y); 
                 tft.print("       ");
                 tft.setCursor(x, y); 
                 tft.print("Off"); 
  }

}

void screenOn(){
        digitalWrite(TFT_BL, HIGH);
        
        screenStatus = 1 ;
        startScrn ();               // Setup Screen
        startTime();
}

void screenOff(){
  if (linkSwitches[1] == 1 ){
    alarmActive = 0 ;
    screenStatus = 0;
    MenueDisplay = 0;
    digitalWrite(TFT_BL, LOW);
    snd = 0;
    linkSwitches[4] = 0;
    alarmActive = 0;
   
  }

}

void startScrn (){
  //timer = 60;
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK); // Note: the new fonts do not draw the background colour
  tft.fillScreen(TFT_BLACK);

  printScreen ("Alarm",0,1,1);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  printOnOff  (linkSwitches[0],40,1,1);

  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  printScreen ("Audio",85,1,1);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  printOnOff (linkSwitches[2],125,1,1);
  //printScreen (String(linkSwitches[3]),140,1,1);

  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  printScreen ("Energy ",170,1,1);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  printOnOff (linkSwitches[3],215,1,1);
  //printScreen (String(energyM),215,1,1);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  //
}

void printScreen (String str,int x,int y,int f){
                 tft.setFreeFont(NULL); 
                 tft.setTextSize(f);
                 tft.setCursor(x, y); 
                 tft.print("         ");
                 tft.setCursor(x, y); 
                 tft.print(str);
}
