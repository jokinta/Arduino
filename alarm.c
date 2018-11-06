
#include <Wire.h>
#include<EEPROM.h>
#include "RTClib.h"
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
RTC_DS1307 RTC;
int tmp,Inc,hor,mIn,add=11; 
int in1 = 6;
int alarm = 7;
int set=8;  
int cge=9;   
int mod=10; 
int off=0;
int count=0;
#define buz 13 
int Hor,Min,Sec; 
int i=1;
int busmatrix[27][11]={
                      1,-1,-2,-3,-4,-5,-6,-7,-8,-9,-10,
                      2,-1,-2,-3,-4,-5,-6,-7,-8,-9,-10,
                      3,-1,-2,-3,-4,-5,-6,-7,-8,-9,-10,
                      4,-1,-2,-3,-4,-5,-6,-7,-8,-9,-10,
                      5,3,18,33,47,60,-1,-1,-1,-1,-1,
                      6,12,35,45,54,-1,-1,-1,-1,-1,-1,
                      7,2,9,15,21,27,33,39,45,51,57,
                      8,3,9,15,21,27,33,40,47,55,-1,
                      9,2,10,17,25,29,32,40,47,55,-1,
                      10,2,6,10,18,22,26,33,41,49,57,
                      11,5,12,20,28,35,43,50,57,-1,-1,
                      12,5,13,21,29,36,44,52,59,-1,-1,
                      13,7,14,21,29,37,45,53,60,-1,-1,
                      14,8,16,23,31,38,45,53,-1,-1,-1,
                      15,1,9,17,24,32,40,47,55,-1,-1,
                      16,2,9,16,23,30,37,44,50,56,-1,
                      17,2,8,14,20,26,32,38,44,51,57,
                      18,4,7,10,17,23,30,36,43,50,57,
                      19,5,14,23,28,33,40,48,53,58,-1,
                      20,3,10,18,25,33,40,48,55,-1,-1,
                      21,3,18,33,48,-1,-1,-1,-1,-1,-1,
                      22,3,18,33,48,-1,-1,-1,-1,-1,-1,
                      23,3,18,33,48,-1,-1,-1,-1,-1,-1,
                      24,3,-1,-1,-1,-1,-1,-1,-1,-1,-1
                     };


void bustime(){
  
  Serial.println(busmatrix[Hor][i]);
  Serial.println(busmatrix[Hor][i+1]);
  Serial.println(busmatrix[1][10]);
  Serial.println(i);
  
if(i=11||i>11){
while(i!=1){
  i--;
}
}
while(busmatrix[Hor][i]<0){
  i++;
}
while(busmatrix[Hor][i]-Min<0){
  i++;
}
 if(count%10==0){
 if(busmatrix[Hor][i]-Min==0){
  i++;
 }
 if(busmatrix[Hor][i]>0){
   lcd.clear();
  lcd.print("94 sled: ");
  
  /*lcd.print(minbus[i]/60);
  lcd.print(":");
  lcd.print(minbus[i]%60);*/
   lcd.print("~");
  lcd.print(busmatrix[Hor][i]-Min);
  lcd.print(",");
   lcd.print("~");
   if(busmatrix[Hor][i+1]-Min<0){
    lcd.print((busmatrix[Hor+1][1]+60)-Min);
   }
   else{
    lcd.print(busmatrix[Hor][i+1]-Min);
   }
  lcd.print("min");
  lcd.setCursor(0,1);
  lcd.print("280 sled: ~10,~13");
  lcd.print(i);
  delay(3000);
 }
 }
}

void time()                             
{
    int tmp=1,mins=0,hors=0,secs=0;
    while(tmp==1)
    {
     off=0;
     if(digitalRead(cge)==0)
     {
      Hor++;
      if(Hor==24)
      {
       Hor=0;
      }
     }
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Set Alarm Time ");

    lcd.setCursor(0,1);
    if(Hor<=9)
    lcd.print("0");
    lcd.print(Hor);
    lcd.print(":");
    lcd.print(Min);
    lcd.print(":");
    lcd.print(Sec);
    delay(200);
    lcd.setCursor(0,1);
    lcd.print("  ");
    lcd.print(":");
    lcd.print(Min);
    lcd.print(":");
    lcd.print(Sec);
    delay(200);
    if(digitalRead(set)==0)
    {
      hor=Hor;
      EEPROM.write(add++,hor);
     tmp=2;
     while(digitalRead(set)==0);
    }
    }
    
    while(tmp==2)
    {
     if(digitalRead(cge)==0)
     {
      Min++;
      if(Min==60)
      {Min=0;}
     }
    lcd.setCursor(0,1);
    lcd.print(Hor);
    lcd.print(":");
     if(Min<=9)
    lcd.print("0");
    lcd.print(Min);
    lcd.print(":");
    lcd.print(Sec);
    lcd.print("  ");
    delay(200);
     lcd.setCursor(0,1);
    lcd.print(Hor);
    lcd.print(":");
    lcd.print("  ");
    lcd.print(":");
    lcd.print(Sec);
    lcd.print("  ");
    delay(200);
      if(digitalRead(set)==0)
      {
       mIn=Min;
       EEPROM.write(add++, mIn);
       tmp=0;
       while(digitalRead(set)==0);
      }
    }
    off=1;
    delay(10);
}
///////////////////////////////////////////function to sound the buzzer//////////////////////////////////
void Buz()
{
  if(digitalRead(set)==0)
  off=0;
  if(off==1)
  {
   digitalWrite(buz,HIGH);
   delay(500);
  
   digitalWrite(buz, LOW);
   delay(500);
  }
}
//////////////////////////////////////////function to compare the alarm time with current RTC time//////////////////
void TimeCheck()
{
  int tem[17];
  for(int i=11;i<17;i++)
  {
    tem[i]=EEPROM.read(i);
  }
  if(Hor == tem[11] && Min == tem[12] && off==1) 
  {
  
   lcd.clear();
   lcd.print("    ! Alarm !");
   lcd.setCursor(0,1);
   lcd.print("!!! Budi se !!!");
   digitalWrite(in1, HIGH);
   digitalWrite(alarm, HIGH);
        digitalWrite(in1, LOW);

   
    }
     if(Hor == tem[11] && Min == tem[12]-3 && off==1) 
  {
     digitalWrite(in1, HIGH);

    }
  
  }

////////////////////////////////////////////////////////////setup///////////////////////////
void setup()
{
 Wire.begin();
 RTC.begin();
 lcd.begin(16,2);
 pinMode(cge, INPUT);
 pinMode(set, INPUT);
 pinMode(mod, INPUT);
 pinMode(buz, OUTPUT);
 pinMode(in1, OUTPUT);
  digitalWrite(in1, LOW);
    pinMode(alarm, OUTPUT);
  digitalWrite(alarm, LOW);
 digitalWrite(set, HIGH);
 digitalWrite(mod, HIGH);
 digitalWrite(cge, HIGH);
 
  Serial.begin(9600);  
   lcd.setCursor(0,0);
   lcd.print("   Jokinta   ");
   lcd.setCursor(0,1);
   lcd.print("  Alarm Clock  ");
   delay(2000);
   lcd.clear();
 if(!RTC.isrunning())
 {
 RTC.adjust(DateTime(__DATE__,__TIME__));
 }
}


////////////////////////////////////////////////////////////loop/////////////////////////////////////
void loop()
{
  /*for(
for(j=0;j<60;j++){
  minbus[j]*=60;
}*/

//minbus[i]*=60;
   DateTime now = RTC.now();
   if(digitalRead(mod) == 0)      
   { 
    current();
    time();
    delay(1000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("  Alarm On");
    delay(2000);
   }
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Time:");
 lcd.setCursor(6,0);
 Hor=now.hour(),DEC; 
 if(Hor<=9)
 {
  lcd.print("0");
  lcd.print(Hor=now.hour(),DEC);
 }
 else
 lcd.print(Hor=now.hour(),DEC);
 lcd.print(":");
 Min=now.minute(),DEC;
 if(Min<=9)
 {
 lcd.print("0");
 lcd.print(Min=now.minute(),DEC);
 }
 else
 lcd.print(Min=now.minute(),DEC);
 
 lcd.print(":");
 Sec=now.second(),DEC;
 if(Sec<=9)
 {
  lcd.print("0");
  lcd.print(Sec=now.second(),DEC);
 }
 else
 lcd.print(Sec=now.second(),DEC);
 lcd.setCursor(0,1);
 lcd.print("Date: ");
 lcd.print(now.day(),DEC);
 lcd.print("/");
 lcd.print(now.month(),DEC);
 lcd.print("/");
 lcd.print(now.year(),DEC);
 TimeCheck();
   delay(200);
 /* if(Hor==16){

  }else{
      digitalWrite(in1, LOW);

  }*/
   if(Hor!=00&&Hor!=1&&Hor!=2&&Hor!=3&&Hor!=4){
  

      for(;;){
         
  
 count++;
//minbus[i]--;
 delay(1000);
 break;
 }
 bustime();
   }
}
///////////////////////////////////////////////////////function to get current RTC time//////////////////////////////
void current()
{
  lcd.setCursor(0,1);
  lcd.print(Hor);
  lcd.print(":");
  lcd.print(Min);
  lcd.print(":");
  lcd.print(Sec);

}