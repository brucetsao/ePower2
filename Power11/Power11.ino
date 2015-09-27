
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
#define SW1  A1
#define SW2  A2
#define SW3  A3

#define ananlogmax 1024 
#define ACS712_5A 185
#define ACS712_20A 100
#define ACS712_30A 66

#define readCurrentCount 300 


//----------------AC  Current Measure  ASC712 -------------
/*


     long adc_raw = analogRead(currentPin) - adc_zero;
     currentAcc += (unsigned long)(adc_raw * adc_raw);
     
     */

 int adc_zero1 = 500;                                                     // relative digital zero of the arudino input from ACS712 (could make this a variable and auto-adjust it)
 int adc_zero2 = 500;                                                     // relative digital zero of the arudino input from ACS712 (could make this a variable and auto-adjust it)
 int adc_zero3 = 500;          
  int RelayPinSet[] = {7,6,5} ;
  boolean RelayStatus[] = {false,false,false} ;

String CmdStringDate ;
String CmdStringStartTime ;
String CmdStringEndTime ;
char CmdStringSocketNum ;
char CmdStringSocketStatus ;


  
const int mi = 54 ;
// relative digital zero of the arudino input from ACS712 (could make this a variable and auto-adjust it)
LiquidCrystal lcd(8, 9, 10, 27,29,31,33,35,37,39,41);
void setup()
{
  initall() ;
    Serial.begin(9600);
        Serial2.begin(9600);
   Serial.println("ACS712 20A Test");
  lcd.begin(20, 4);
// 設定 LCD 的行列數目 (20 x 4)  20　行4　列
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

if (RelayStatus[0])
    {
      currentAcc1 =  Current1() ;
    }
    else
    {
      currentAcc1 = 0 ;
    }
if (RelayStatus[1])
    {
      currentAcc2 =  Current2() ;
    }
    else
    {
      currentAcc2 = 0 ;
    }
if (RelayStatus[2])
    {
      currentAcc3 =  Current3() ;
    }
    else
    {
      currentAcc3 = 0 ;
    }
 Serial.print("now Current is :(");
 Serial.print(currentAcc1);
 Serial.print("/");
 Serial.print(currentAcc2);
 Serial.print("/");
 Serial.print(currentAcc3);
 /*
  Serial.print("|");
 Serial.print(read_CurrentRMS1());
 Serial.print("/");
 Serial.print(read_CurrentRMS2());
 Serial.print("/");
 Serial.print(read_CurrentRMS3());

*/
 Serial.print(")");
 
 Serial.print("   \n");

/*
 Serial.print("now RMS Current is :(");
 Serial.print(read_CurrentRMS1());
 Serial.print("/");
 Serial.print(read_CurrentRMS2());
 Serial.print("/");
 Serial.print(read_CurrentRMS3());
 Serial.print(")");
 Serial.print("   \n");

*/

  LCDCurrentStatus(currentAcc1,currentAcc2,currentAcc3) ;
  CheckCommand() ;
  
delay(1000);
}



void LCDCurrentStatus(long no1, long no2, long no3)
{
  showACSonLCD(1,no1,RelayStatus[0]) ;   // 列印 ACS712  訊息到 LCD 上 
  showACSonLCD(2,no2,RelayStatus[1]) ;  // 列印 ACS712  訊息到 LCD 上 
  showACSonLCD(3,no3,RelayStatus[2]) ;  // 列印 ACS712  訊息到 LCD 上 
  
  
}

int Current1()
{

  int tmp ;
  tmp = read_CurrentRMS1()  ;
  return ( tmp * mi) ;
  
}

int Current2()
{

  int tmp ;
  tmp = read_CurrentRMS2()  ;
  return ( tmp * mi) ;
  
}

int Current3()
{

  int tmp ;
  tmp = read_CurrentRMS3()  ;
  return ( tmp * mi) ;
  
}

double read_CurrentRMS1()
{
  
  int sensorValue=0;

  int tmp = 0 ;
  long summ = 0 ;

 
  //讀取一千次，取得最高與最低值，相減得到峰對峰值
  for(int i=0;i<readCurrentCount;i++)
  {
    sensorValue = analogRead(SW1);   
 //   Serial.println(sensorValue) ;
     tmp =  (sensorValue - adc_zero1) ;   
      summ = summ + tmp * tmp;
   //   Serial.println(sensorValue) ;
   //   Serial.println(tmp) ;
  //    Serial.println(summ) ;
  //    Serial.println("============") ;
   // delayMicroseconds(150);
  }

  return (sqrt((summ/readCurrentCount) ) ) ;
}


double read_CurrentRMS2()
{
  
  int sensorValue=0;

  int tmp = 0 ;
  long summ = 0 ;

 
  //讀取一千次，取得最高與最低值，相減得到峰對峰值
  for(int i=0;i<readCurrentCount;i++)
  {
    sensorValue = analogRead(SW2);   
 //   Serial.println(sensorValue) ;
     tmp =  (sensorValue - adc_zero2) ;   
      summ = summ + tmp * tmp;
   //   Serial.println(sensorValue) ;
   //   Serial.println(tmp) ;
  //    Serial.println(summ) ;
  //    Serial.println("============") ;
   // delayMicroseconds(150);
  }

  return (sqrt((summ/readCurrentCount) ) ) ;
}

double read_CurrentRMS3()
{
  
  int sensorValue=0;

  int tmp = 0 ;
  long summ = 0 ;

 
  //讀取一千次，取得最高與最低值，相減得到峰對峰值
  for(int i=0;i<readCurrentCount;i++)
  {
    sensorValue = analogRead(SW3);   
 //   Serial.println(sensorValue) ;
     tmp =  (sensorValue - adc_zero3) ;      
      summ = summ + tmp * tmp;
   //   Serial.println(sensorValue) ;
   //   Serial.println(tmp) ;
  //    Serial.println(summ) ;
  //    Serial.println("============") ;
   // delayMicroseconds(150);
  }

  return (sqrt((summ/readCurrentCount) ) ) ;
}



 int read_Current1()
{

  unsigned int sensorValue=0;
 unsigned int  uiCurrentMaxValue = 0;
  unsigned int  uiCurrentMinValue = 65535;
 
  //讀取一千次，取得最高與最低值，相減得到峰對峰值
  for(int i=0;i<readCurrentCount;i++)
  {
    sensorValue = analogRead(SW1);            
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



 int read_Current2()
{

  unsigned int sensorValue=0;
 unsigned int  uiCurrentMaxValue = 0;
  unsigned int  uiCurrentMinValue = 65535;
 
  //讀取一千次，取得最高與最低值，相減得到峰對峰值
  for(int i=0;i<readCurrentCount;i++)
  {
    sensorValue = analogRead(SW2);            
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

 int read_Current3()
{

  unsigned int sensorValue=0;
 unsigned int  uiCurrentMaxValue = 0;
  unsigned int  uiCurrentMinValue = 65535;
 
  //讀取一千次，取得最高與最低值，相減得到峰對峰值
  for(int i=0;i<readCurrentCount;i++)
  {
    sensorValue = analogRead(SW3);            
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
  int sensorV1,sensorV2,sensorV3 ;
  long sum1 = 0 , sum2 = 0 , sum3 = 0 ;
  

  delay(500);
      
       for(int i=0;i<readCurrentCount;i++)
  {
    sensorV1 = analogRead(SW1);            
      sum1 = sum1 + sensorV1 ;
    sensorV2 = analogRead(SW2);            
      sum2 = sum2 + sensorV2 ;
    sensorV3 = analogRead(SW3);            
      sum3 = sum3 + sensorV3 ;
  }
      adc_zero1 = (unsigned int)(sum1 / readCurrentCount) ;
      adc_zero2 = (unsigned int)(sum2 / readCurrentCount) ;
      adc_zero3 = (unsigned int)(sum3 / readCurrentCount) ;

          
       Serial.print("init Current is :(");
 Serial.print(adc_zero1);
 Serial.print("/");
 Serial.print(adc_zero2);
 Serial.print("/");
 Serial.print(adc_zero3);
 Serial.print(")\n");



}     

void initall()
{
  initRelayStatus() ;

}

void showACSonLCD(int sockno,long ACSCurrent  ,boolean status )
{
   lcd.setCursor(0,sockno);
   lcd.print("                ");  
   
   lcd.setCursor(0,sockno);
   lcd.print(ACSCurrent,DEC);  
   if (status)
      {
             lcd.setCursor(8,sockno); 
             lcd.print("On ");
      }
      else
      {
             lcd.setCursor(8,sockno); 
             lcd.print("Off");
      }
      

}

void initRelayStatus()
{
    for (int i = 0 ; i <3 ; i++)
    {
          pinMode(RelayPinSet[i], OUTPUT) ;
          digitalWrite(RelayPinSet[i], turnon) ;
          RelayStatus[i] = true ;
    }

}

void ChangeRelay(int relayno, char Relaystatus)
{
    if (Relaystatus == '0')
        {
                   digitalWrite(RelayPinSet[relayno], turnoff) ;
                   RelayStatus[relayno]= turnoff ;
                   Serial.print("Now Close Socket :") ;
                   Serial.print(relayno) ;
                   Serial.print("/") ;
                   Serial.print(Relaystatus) ;
                   Serial.print("/Close \n") ;
                   
        }
        else
        {
                   digitalWrite(RelayPinSet[relayno], turnon) ;
                   RelayStatus[relayno]= turnon ;
                   Serial.print("Now Close Socket :") ;
                   Serial.print(relayno) ;
                   Serial.print("/") ;
                   Serial.print(Relaystatus) ;
                   Serial.print("/Open \n")  ;
        }
}

void   CheckCommand()
{
  char cmd ;
    if (Serial2.available())
        {
            cmd = Serial2.read() ;
            if  (cmd != 'C')
              {
                Serial.print("Error Read:(");
                Serial.print(cmd,HEX) ;
                Serial.print("/");
                Serial.print(cmd,DEC) ;
                Serial.print(")\n");
                  return ;
              }
        }

  switch (cmd)
    {
        case 'C' :
            ReadSocketControl() ;
            break ;
        default :
              break ;
    }
}



void ReadSocketControl()
{
    char cmd ;
    boolean ck1 = false ;
    boolean ck2 = false ;
       if (Serial2.available())
        {
            cmd = Serial2.read() ;
            if (isDigit(cmd))
              {
                    CmdStringSocketNum = cmd ;
                    ck1 = true ; 
                    Serial.print("CMD1 :(") ;
                    Serial.print(CmdStringSocketNum) ;
                    Serial.print(")\n") ;
              }
              
        }
       if (Serial2.available())
        {
            cmd = Serial2.read() ;
            if (isDigit(cmd))
              {
                    CmdStringSocketStatus  = cmd ;
                    ck2 = true ; 
                    Serial.print("CMD1 :(") ;
                    Serial.print(CmdStringSocketStatus) ;
                    Serial.print(")\n") ;
              }
        }
      if (ck1 && ck2)
          {
              Serial.print("now Change Scoket Status \n");
            ChangeRelay(int(CmdStringSocketNum)-49 , CmdStringSocketStatus ) ;
          }
}



