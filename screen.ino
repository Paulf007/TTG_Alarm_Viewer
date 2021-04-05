void displayInverter (){
//  int soc = 0 ;
//int grid = 0 ;
//int bat = 0 ;
     tft.setFreeFont(FSB24);
     tft.setTextSize(NULL);
     char invS  [15]="";
     char socS  [15]="";
     char solS  [15]="";
     char gridS [15]="";
     char batS  [15]="";
     sprintf(invS ,"%s%d%s","Inv:",inv,"w");  
     sprintf(socS,"%s%d%s","Soc:",soc,"%");
     sprintf(solS,"%s%d%s","Sol:",sol,"w");    
     sprintf(gridS ,"%s%d%s","Grd:",grid,"w");
     sprintf(batS,"%s%d%s","Bat:",bat,"w");
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

void screenOff(){
  if (scrAuto == 1 ){
    //tft.fillScreen(TFT_BLACK);
    MenueDisplay = 0;
    digitalWrite(TFT_BL, LOW);
    snd = 0;
    energyM = 1;
    alarmActive = 0;
    timer = 60;
  }

}

void startScrn (){
  //timer = 60;
  tft.init();
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK); // Note: the new fonts do not draw the background colour
  tft.fillScreen(TFT_BLACK);

  printScreen ("Screen Off",0,1,1);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  printScreen (String(timer),70,1,1);

  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  printScreen ("Audio",105,1,1);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  printOnOff (playTone,145,1,1);
  //printScreen (String(playTone),140,1,1);

  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  printScreen ("Energy ",170,1,1);
  tft.setTextColor(TFT_RED, TFT_BLACK);
  printOnOff (energyM,215,1,1);
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
