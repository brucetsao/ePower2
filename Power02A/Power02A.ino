#define relay1pin 8
#define relay2pin 9
#define relay3pin 10
#define turnon true
#define turnoff false

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

#define readCurrentCount 1000 


//----------------AC  Current Measure  ASC712 -------------
/*


     long adc_raw = analogRead(currentPin) - adc_zero;
     currentAcc += (unsigned long)(adc_raw * adc_raw);
     
     */

unsigned int adc_zero1 = 500;                                                     // relative digital zero of the arudino input from ACS712 (could make this a variable and auto-adjust it)
unsigned int adc_zero2 = 500;                                                     // relative digital zero of the arudino input from ACS712 (could make this a variable and auto-adjust it)
unsigned int adc_zero3 = 500;       

const double mi = 39.9 ;
  // relative digital zero of the arudino input from ACS712 (could make this a variable and auto-adjust it)
LiquidCrystal lcd(5,6,7,22,24,26,28,30,32,34,36);   //ok
void setup()
{
  initall() ;
    Serial.begin(9600);
   Serial.println("ACS712 20A Test");
  lcd.begin(16, 2);
// 設定 LCD 的行列數目 (16 x 2)  16　行2　列
 lcd.setCursor(0,0);
  // 列印 "Hello World" 訊息到 LCD 上 
lcd.print("hello, world!"); 
  Serial.println("hello, world!");
   initcurrent() ;
}




void loop()
{

  
 double currentAcc1 = 0;
 double currentAcc2 = 0;
 double currentAcc3 = 0;


currentAcc1 =  Current1() ;
currentAcc2 =  Current2() ;
currentAcc3 =  Current3() ;
 Serial.print("now Current is :(");
 Serial.print(currentAcc1);
 Serial.print("/");
 Serial.print(currentAcc2);
 Serial.print("/");
 Serial.print(currentAcc3);
 Serial.print(")");
 
 Serial.print("   \n");

LCDCurrentStatus(currentAcc1,currentAcc2,currentAcc3) ;
delay(3000);
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

double Current1()
{

  double tmp ;
  tmp = (double)read_Current1()  ;
  return (  (tmp -adc_zero1) * mi) ;
  
}

double Current2()
{

  double tmp ;
  tmp = (double)read_Current2()  ;
  return (  (tmp -adc_zero2) * mi) ;
  
}

double Current3()
{

  double tmp ;
  tmp = (double)read_Current3()  ;
  return (  (tmp -adc_zero3) * mi) ;
  
}


double read_CurrentRMS1()
{
  
  int sensorValue=0;

  int tmp = 0 ;
  long summ = 0 ;

 
  //讀取一千次，取得最高與最低值，相減得到峰對峰值
  for(int i=0;i<readCurrentCount;i++)
  {
    sensorValue = analogRead(current02);   
 //   Serial.println(sensorValue) ;
     tmp =  (sensorValue - adc_zero2)*10 ;   
      summ = summ + tmp * tmp;
   //   Serial.println(sensorValue) ;
   //   Serial.println(tmp) ;
  //    Serial.println(summ) ;
  //    Serial.println("============") ;
   // delayMicroseconds(150);
  }

  return (sqrt((summ/readCurrentCount) ) ) ;
}

unsigned int read_Current1()
{

  unsigned int sensorValue=0;
 unsigned int  uiCurrentMaxValue = 0;
  unsigned int  uiCurrentMinValue = 65535;
 
  //讀取一千次，取得最高與最低值，相減得到峰對峰值
  for(int i=0;i<readCurrentCount;i++)
  {
    sensorValue = analogRead(current01);            
    if(sensorValue > uiCurrentMaxValue)
    {
      uiCurrentMaxValue = sensorValue;
    }
    if(sensorValue < uiCurrentMinValue)
    {
      uiCurrentMinValue = sensorValue;
    }
  }

  return (uiCurrentMaxValue-uiCurrentMinValue) ;
}



unsigned int read_Current2()
{

  unsigned int sensorValue=0;
 unsigned int  uiCurrentMaxValue = 0;
  unsigned int  uiCurrentMinValue = 65535;
 
  //讀取一千次，取得最高與最低值，相減得到峰對峰值
  for(int i=0;i<readCurrentCount;i++)
  {
    sensorValue = analogRead(current02);            
    if(sensorValue > uiCurrentMaxValue)
    {
      uiCurrentMaxValue = sensorValue;
    }
    if(sensorValue < uiCurrentMinValue)
    {
      uiCurrentMinValue = sensorValue;
    }
  }

  return (uiCurrentMaxValue-uiCurrentMinValue) ;
}

unsigned int read_Current3()
{

  unsigned int sensorValue=0;
 unsigned int  uiCurrentMaxValue = 0;
  unsigned int  uiCurrentMinValue = 65535;
 
  //讀取一千次，取得最高與最低值，相減得到峰對峰值
  for(int i=0;i<readCurrentCount;i++)
  {
    sensorValue = analogRead(current03);            
    if(sensorValue > uiCurrentMaxValue)
    {
      uiCurrentMaxValue = sensorValue;
    }
    if(sensorValue < uiCurrentMinValue)
    {
      uiCurrentMinValue = sensorValue;
    }
  }

  return (uiCurrentMaxValue-uiCurrentMinValue) ;
}

void initcurrent()
{
  int i ;
  long sum1 = 0 , sum2 = 0 , sum3 = 0 ;
  unsigned tmp1 , tmp2 , tmp3 ;  
    digitalWrite(relay1pin, turnoff) ;
  digitalWrite(relay2pin, turnoff) ;
  digitalWrite(relay3pin, turnoff) ;
  delay(100);
      
      adc_zero1 = (unsigned int)read_Current1;
      adc_zero2 = (unsigned int)read_Current2;
      adc_zero3 = (unsigned int)read_Current3;
      Serial.println(adc_zero1) ;
      Serial.println(adc_zero2) ;
      Serial.println(adc_zero3) ;
           Serial.println("=================") ;
    // delay(1000);
   digitalWrite(relay1pin, turnon) ;
  digitalWrite(relay2pin, turnon) ;
  digitalWrite(relay3pin, turnon) ;
}     

void initall()
{
  pinMode(relay1pin, OUTPUT) ;
  pinMode(relay2pin, OUTPUT) ;
  pinMode(relay3pin, OUTPUT) ;
  digitalWrite(relay1pin, turnon) ;
  digitalWrite(relay2pin, turnon) ;
  digitalWrite(relay3pin, turnon) ;

}


