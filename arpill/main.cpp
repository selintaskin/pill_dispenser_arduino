//
//  main.cpp
//  arpill
//
//  Created by selin taskin  on 17.12.2021.
//

#include <Keypad.h>
#include <Wire.h>
#include <ds3231.h>
#include <StreamLib.h>
#include <LiquidCrystal_I2C.h>
#include<Servo.h>
//init servo
Servo micro;
// initialize LCD,
LiquidCrystal_I2C lcd(0x27, 16, 2);
//initialize time
struct ts t;
const byte r= 4;
const byte c=4;
//keypad buttons
char keys[r][c]={
  {'1', '4', '7', '*'},
  {'2', '5', '8', '0'},
  {'3', '6', '9', '#'},
  {'A', 'B', 'C', 'D'}
};
// 4 pins are rows
byte rPins[r]= {9,8,7,6};
// 4 pins are columns
byte cPins[c] = {5,4,3,2};
Keypad myK= Keypad ( makeKeymap(keys),rPins,cPins,r,c);
int h_1,h_2,h;
int m_1,m_2,m;
//initialize red LED
const int LED_R=13;
//initialize yellow LED;
const int LED_Y=12;
//initialize buzzer
const int buzz= 11;



int post=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
  //pinMode(10,INPUT);
  micro.attach(10);
  //initialize RTC
  DS3231_init(DS3231_CONTROL_INTCN);
  //initialize LEDs
  pinMode(LED_R, OUTPUT);
  pinMode(LED_Y,OUTPUT);
  pinMode(buzz,OUTPUT);
  pinMode(1,INPUT);
  //init lcd
  lcd.init();
  //lcd.setBacklight((uint8_t)1);
  lcd.home();
  lcd.print("Enter Date");
  delay(4000);
  lcd.clear();
  char d1,d2,m1,m2,ye1,ye2,ye3,ye4;
  int di1,di2,moi1,moi2,yei1,yei2,yei3,yei4;
//set initial date:
  d1 = myK.waitForKey();
  if( d1){
    Serial.println(d1);
    lcd.home();
    lcd.print(d1);
    di1= (d1-'0');
  }
  d2 = myK.waitForKey();
  if( d2){
    Serial.println(d2);
    lcd.setCursor(1,0);
    lcd.print(d2);
    di2= (d2-'0');
  }
  int d=di1*10+di2;
  lcd.setCursor(3,0);
  lcd.print(".");
  m1= myK.waitForKey();
  if( m1){
    Serial.println(m1);
    lcd.setCursor(3,0);
    lcd.print(m1);
    moi1= (m1-'0');
  }
  m2= myK.waitForKey();
  if( m2){
    Serial.println(m2);
    lcd.setCursor(4,0);
    lcd.print(m2);
    moi2= (m2-'0');
  }
  int mo=moi1*10+moi2;
  lcd.setCursor(5,0);
  lcd.print(".");
  ye1= myK.waitForKey();
  if( ye1){
    Serial.println(ye1);
    lcd.setCursor(6,0);
    lcd.print(ye1);
    yei1= (ye1-'0');
  }
  ye2= myK.waitForKey();
  if( ye2){
    Serial.println(ye2);
    lcd.setCursor(7,0);
    lcd.print(ye2);
    yei2= (ye2-'0');
  }
  ye3= myK.waitForKey();
  if( ye3){
    Serial.println(ye3);
    lcd.setCursor(8,0);
    lcd.print(ye3);
    yei3= (ye3-'0');
   }
   ye4= myK.waitForKey();
   if( ye4){
     Serial.println(ye4);
     lcd.setCursor(9,0);
    lcd.print(ye4);
     yei4= (ye4-'0');
   }
   int yea= yei1*1000+yei2*100+yei3*10+yei4;
  // set rtc time
  t.mday=d;
  t.mon=mo;
  t.year=yea;
  lcd.clear();
  lcd.home();
  //Set initial time
  lcd.print("Enter Time");
  delay(4000);
  lcd.clear();
  lcd.home();
  char b1,b2,y1,y2;
  int hi1,hi2,mi1,mi2,hi,mi;
  b1 = myK.waitForKey();
  if( b1){
    Serial.println(b1);
    lcd.print(b1);
    hi1= (b1-'0');
  }
  b2 = myK.waitForKey();
  if( b2){
    Serial.println(b2);
    lcd.setCursor(1,0);
    lcd.print(b2);
    hi2= (b2-'0');
   }
   hi=(hi1*10+hi2)%24;
   lcd.setCursor(2,0);
   lcd.print(".");
   y1= myK.waitForKey();
   if( y1){
     Serial.println(y1);
     lcd.setCursor(3,0);
     lcd.print(y1);
     mi1= (y1-'0');
   }
   y2= myK.waitForKey();
   if( y2){
      lcd.setCursor(4,0);
      lcd.print(y2);
     Serial.println(y2);
     mi2= (y2-'0');
   }
   
   mi=(mi1*10+mi2)%60;
   
    t.sec=30;
    t.min=mi;
    t.hour=hi;
    
  
   //set rtc time
  DS3231_set(t);
}

void turn(){
     for (post = 0; post <= 50; post += 1) {
        // in steps of 1 degree
        micro.write(post);
        delay(15);
      }
      for (post = 50; post >= 0; post -= 1) {
        micro.write(post);
        delay(15);
      }

}

void led_blink(){
//function for led blinking
  digitalWrite(LED_R,HIGH);
  digitalWrite(LED_Y,HIGH);
  delay(100);
  digitalWrite(LED_R,LOW);
  digitalWrite(LED_Y,LOW);
  delay(100);
  digitalWrite(LED_R,HIGH);
  digitalWrite(LED_Y,HIGH);
  delay(100);
  digitalWrite(LED_R,LOW);
  digitalWrite(LED_Y,LOW);
  delay(100);
  digitalWrite(LED_R,HIGH);
  digitalWrite(LED_Y,HIGH);
  delay(100);
  digitalWrite(LED_R,LOW);
  digitalWrite(LED_Y,LOW);
  delay(100);
}


void loop() {
  int gate;
  //0-> not pressed
  //1-> pressed
  
//check if the button is pressed, if button is not pressed set gate to 0.
  if(digitalRead(1) == HIGH){
    gate=0;
    
  }
  // put your main code here, to run repeatedly:
  char ba1,ba2,ya1,ya2;
  int hia1,hia2,mia1,mia2,hia,mia;
  char a1,a2,v1,v2;
  DS3231_get(&t);
  char g=myK.getKey();
//set alarm time if A key is pressed
  if( g=='A'){
    lcd.clear();
    lcd.home();
     a1 = myK.waitForKey();
    if( a1){
      Serial.println(a1);
      lcd.print(a1);
      h_1= (a1-'0');
    }
    a2 = myK.waitForKey();
    if( a2){
      lcd.setCursor(1,0);
      lcd.print(a2);
      Serial.println(a2);
      h_2= (a2-'0');
    }
    v1= myK.waitForKey();
    lcd.setCursor(2,0);
    lcd.print(".");
    if( v1){
      Serial.println(v1);
      lcd.setCursor(3,0);
      lcd.print(v1);
      m_1= (v1-'0');
    }
    v2= myK.waitForKey();
    if( v2){
      Serial.println(v2);
      lcd.setCursor(4,0);
      lcd.print(v2);
      delay(1000);
      m_2= (v2-'0');
    }
    h=(h_1*10+h_2)%24;
    m=(m_1*10+m_2)%60;
    lcd.clear();
    lcd.home();
    lcd.print("Alarm Set");
    delay(2000);
    lcd.clear();
    lcd.home();
  }
// re-set the initial time if D key is pressed.
  if(g=='D'){
    lcd.clear();
    lcd.home();
    lcd.print("Set new time:");
    delay(2000);
    lcd.clear();
    ba1 = myK.waitForKey();
    if( ba1){
      Serial.println(ba1);
      lcd.home();
      lcd.print(ba1);
      hia1= (ba1-'0');
    }
    ba2 = myK.waitForKey();
    if( ba2){
      Serial.println(ba2);
      lcd.setCursor(1,0);
      lcd.print(ba2);
      hia2= (ba2-'0');
     }
     hia=(hia1*10+hia2)%24;
     ya1= myK.waitForKey();
     
     lcd.setCursor(2,0);
     lcd.print(".");
     if( ya1){
       Serial.println(ya1);
       lcd.setCursor(3,0);
       lcd.print(ya1);
       mia1= (ya1-'0');
     }
     ya2= myK.waitForKey();
     if( ya2){
        lcd.setCursor(4,0);
        lcd.print(ya2);
        delay(1000);
       Serial.println(ya2);
       mia2= (ya2-'0');
     }
     mia=(mia1*10+mia2)%60;
     t.hour = hia;
     t.min=mia;
     t.sec=0;
     DS3231_set(t);
  }
  
//if the current time and alarm time matches => buzz and blink
  if(t.hour== h&& t.min==m && t.sec==0 && gate==0){
    do{
      if(digitalRead(1) ==LOW){
        Serial.print("a");
        
        gate=1;
              
      }
      led_blink();
      if(digitalRead(1) ==LOW){
        Serial.print("b");
        
        gate=1;
      }
        tone(buzz,1000);
        if(digitalRead(1) ==LOW){
          Serial.print("c");
          
        gate=1;
        
      }
        delay(1000);
        if(digitalRead(1) ==LOW){
          Serial.print("d");
         
        gate=1;
      }
        noTone(buzz);
        if(digitalRead(1) ==LOW){
          Serial.print("e");
          
        gate=1;
               
      }
        lcd.clear();
        if(digitalRead(1) ==LOW){
          Serial.print("f");
          
        gate=1;
           
      }
        lcd.home();
        if(digitalRead(1) ==LOW){
          Serial.print("g");
          
        gate=1;
          
      }
        lcd.print("ALARM");
        if(digitalRead(1) ==LOW){
          Serial.print("h");
          
        gate=1;
         
      }
        delay(2000);
        if(digitalRead(1) ==LOW){
          Serial.print("l-");
          
        gate=1;
          
      }
    }while(gate == 0);
    
    lcd.clear();

   }
   // if the button is pressed when the alarm was buzzing, turn the servo.
  if(gate==1){
    turn();
  }
  
// normally RTC goes beyond 24 hours, so this turn the time to 0 so that the time can only be between 0-23.
  if( t.hour ==24 ){
    t.hour = 0;
    t.min=t.min;
    t.sec=t.sec;
    DS3231_set(t);
  }
// write time and date to LCD all the time
  lcd.home();
  lcd.print("Date:");
  lcd.setCursor(5,0);
  lcd.print(t.mday);
  lcd.setCursor(7,0);
  lcd.print(".");
  lcd.setCursor(8,0);
  lcd.print(t.mon);
  lcd.setCursor(10,0);
  lcd.print(".");
  lcd.setCursor(11,0);
  lcd.print(t.year);
  lcd.setCursor(0,1);
  lcd.print("Time:");
  lcd.setCursor(5,1);
  lcd.print(t.hour);
  lcd.setCursor(7,1);
  lcd.print(".");
  lcd.setCursor(8,1);
  lcd.print(t.min);
  lcd.setCursor(10,1);
  lcd.print(".");
  lcd.setCursor(11,1);
  lcd.print(t.sec);
  
  
}
