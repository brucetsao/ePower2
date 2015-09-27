//  Author Bruce 
/* LiquidCrystal display with:

LiquidCrystal(rs, enable, d4, d5, d6, d7) 
LiquidCrystal(rs, rw, enable, d4, d5, d6, d7) 
LiquidCrystal(rs, enable, d0, d1, d2, d3, d4, d5, d6, d7) 
LiquidCrystal(rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7) 
R/W Pin Read = LOW / Write = HIGH   // if No pin connect RW , please leave R/W Pin for Low State

*/
#include <LiquidCrystal.h>
LiquidCrystal lcd(5,6,7,38,40,42,44);   //ok

void setup(){

  Serial.begin(9600);
  Serial2.begin(9600);
  Serial.println("program start here");
 
lcd.begin(20, 4);
// 設定 LCD 的行列數目 (20 x 4)  20　行4　列
 lcd.setCursor(0,0);
  // 列印 "Hello World" 訊息到 LCD 上 
lcd.print("BlueTooth Test"); 
  Serial.println("BlueTooth Test...");

}
  
void loop(){
  char val ;
  if (Serial2.available())
    {
      val = Serial2.read();
        lcd.setCursor(1,1);
        lcd.print("Key:"); 
        lcd.print(val); 
        // now result is printed on Serial COnsole
          Serial.print("receiev from bluetooth  :") ;
         Serial.println(val, DEC);
    }
    delay(200);  

}


