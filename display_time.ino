void displayTime (){
if (clockActive == 1 && MenueDisplay == 0 && alarmActive == 0){
  
    timeClient.update();
  //Serial.print("Time:");
  //Serial.println(timeClient.getFormattedTime());
  

String formattedDate = timeClient.getFormattedTime();
String dayStamp;
String timeStamp;
//formattedDate = timeClient.getFormattedDate();

  printScreen (formattedDate,15,50,4);
  printScreen (daysOfTheWeek[timeClient.getDay()],15,90,2);
  //printScreen (getTimeStampString(2),120,90,2);
  printScreen (getTimeStampString(3),75,90,2);
  int month = getTimeStampString(2).toInt()-1;
  printScreen (monthsOfYear[month],100,90,2);
  printScreen (getTimeStampString(1),175,90,2);
  
 }
}



String getTimeStampString(byte cmd ) {        // 1) Year , 2) Month 3) Day 
   time_t rawtime = timeClient.getEpochTime();
   struct tm * ti;
   ti = localtime (&rawtime);

   switch (cmd) {
       case 1 :
       {
             uint16_t year = ti->tm_year + 1900;
             String yearStr = String(year);
             return yearStr;
       }
             //break;
       case 2 : 
       {     
            uint8_t month = ti->tm_mon + 1;
            String monthStr = String(month);
            //String monthStr = month < 10 ? "0" + String(month) : String(month);
            return monthStr;
       }
            // break;
      case 3 :
      {
             uint8_t day = ti->tm_mday;
             String dayStr = day < 10 ? "0" + String(day) : String(day);
             return dayStr;
      }
            // break;
   }
}
