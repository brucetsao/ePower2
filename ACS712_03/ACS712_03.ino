#include <LiquidCrystal.h>
/* LiquidCrystal display with:

LiquidCrystal(rs, enable, d4, d5, d6, d7) 
LiquidCrystal(rs, rw, enable, d4, d5, d6, d7) 
LiquidCrystal(rs, enable, d0, d1, d2, d3, d4, d5, d6, d7) 
LiquidCrystal(rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7) 
R/W Pin Read = LOW / Write = HIGH   // if No pin connect RW , please leave R/W Pin for Low State

Parameters
*/


//----------------AC  Current Measure  ASC712 --------------
#define current01  A1
#define current02  A2
#define current03  A3

#define ananlogmax 1024 
#define ACS712_5A 185
#define ACS712_20A 100
#define ACS712_30A 66




//----------------AC  Current Measure  ASC712 -------------
/*


     long adc_raw = analogRead(currentPin) - adc_zero;
     currentAcc += (unsigned long)(adc_raw * adc_raw);
     
     */

const int adc_zero = 510;                                                     // relative digital zero of the arudino input from ACS712 (could make this a variable and auto-adjust it)
LiquidCrystal lcd(5,6,7,22,24,26,28,30,32,34,36);   //ok
void setup()
{
    Serial.begin(9600);
   Serial.println("ACS712 20A Test");
  lcd.begin(16, 2);
// 設定 LCD 的行列數目 (16 x 2)  16　行2　列
 lcd.setCursor(0,0);
  // 列印 "Hello World" 訊息到 LCD 上 
lcd.print("hello, world!"); 
  Serial.println("hello, world!");
   
}




void loop()
{

  
 double currentAcc1 = 0;
 double currentAcc2 = 0;
 double currentAcc3 = 0;
     int count = 0;
     int adc_raw1 =0 ; 
     int adc_raw2 =0 ; 
     int adc_raw3 =0 ; 
     int Max_adc_raw1 = 0 ;
     int Max_adc_raw2 = 0 ;
     int Max_adc_raw3 = 0 ;
     int Max_current1 = 0 ;
     int now_current1 = 0 ;
     int Max_current2 = 0 ;
     int now_current2 = 0 ;
     int Max_current3 = 0 ;
     int now_current3 = 0 ;
     while (count <100)
     {
           // here read ACS712 set 1
           now_current1 = analogRead(current01) ;
           adc_raw1 = abs(now_current1 - adc_zero); 
          if (Max_adc_raw1 < adc_raw1)
            {
                 Max_adc_raw1 = adc_raw1 ;
                Max_current1 = now_current1 ;
            }

           // here read ACS712 set 2
           now_current2 = analogRead(current02) ;
           adc_raw2 = abs(now_current2 - adc_zero); 
          if (Max_adc_raw2 < adc_raw2)
            {
                 Max_adc_raw2 = adc_raw2 ;
                Max_current2 = now_current2 ;
            }


           // here read ACS712 set 3
           now_current3 = analogRead(current03) ;
           adc_raw3 = abs(now_current3 - adc_zero); 
          if (Max_adc_raw3 < adc_raw3)
            {
                 Max_adc_raw3 = adc_raw3 ;
                Max_current3 = now_current3 ;
            }

          count ++ ;
     }
     


     currentAcc1 = (Max_adc_raw1 * 1000)/ACS712_20A ;
     currentAcc2 = (Max_adc_raw2 * 1000)/ACS712_20A ;
     currentAcc3 = (Max_adc_raw3 * 1000)/ACS712_20A ;

 

 Serial.print("(");

 Serial.print(currentAcc1);
 Serial.print("/");
 Serial.print(Max_current1);
 Serial.print("/");
 Serial.print(currentAcc2);
 Serial.print("/");
 Serial.print(Max_current2);
 Serial.print("/");
 Serial.print(currentAcc3);
 Serial.print("/");
 Serial.print(Max_current3);
 Serial.print(")");

 Serial.print("\n");
LCDCurrentStatus(currentAcc1,currentAcc2,currentAcc3) ;
delay(200);
}



void LCDCurrentStatus(long no1, long no2, long no3)
{
   lcd.setCursor(0,1);
   lcd.print("                ");  
   
  // 列印 "Hello World" 訊息到 LCD 上 
   lcd.setCursor(0,1);
   lcd.print(no1,DEC);  
   lcd.setCursor(7,1);
  // 列印 ACS712  訊息到 LCD 上 
lcd.print(no2,DEC);  
   lcd.setCursor(13,1);
  // 列印 ACS712  訊息到 LCD 上 
lcd.print(no3,DEC);  
  // 列印 ACS712  訊息到 LCD 上 
  
}

