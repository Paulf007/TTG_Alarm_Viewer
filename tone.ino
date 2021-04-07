void startTone(int cnt , unsigned long tmr ){
  //Serial.print ("Play:");
  //Serial.println(linkSwitches[3]);
 if (linkSwitches[2] == 1){
  //  Serial.print ("Run Tone:"); 
  //Serial.println (cnt); 
        startMTone = millis();
        runT = 1;
        count = cnt ;
        toneTmer = tmr ;
  }
}

void runTone (){

    
    unsigned long currentMill = millis();
if (lp < count){
    if (currentMill - startMTone > toneTmer && runT == 1  ){ //
    ledcSetup(0,1E5,12);
    ledcAttachPin(15,0);  
    
      if ( tn == 0){
      //Serial.println ("Run Tone On");  
      ledcWriteTone(0,1500);
      tn = 1;
      startMTone = millis();
      }else{
      //Serial.println ("Run Tone off");    
      ledcWriteTone(0,0);
      tn = 0;
      
      startMTone = millis();
      lp ++ ;
     // Serial.println (lp);
      }
      }
    
   // Serial.print 
  }else{
        runT = 0;
        lp = 0;
  }
}
//}
    
  
