
//----------------AC  Current Measure  ASC712 --------------
#define current01  A1
#define ananlogmax 1024 
#define ACS712_5A 185
#define ACS712_20A 100
#define ACS712_20A 66




//----------------AC  Current Measure  ASC712 -------------
/*


     long adc_raw = analogRead(currentPin) - adc_zero;
     currentAcc += (unsigned long)(adc_raw * adc_raw);
     
     */

const int adc_zero = 510;                                                     // relative digital zero of the arudino input from ACS712 (could make this a variable and auto-adjust it)

void setup()
{
    Serial.begin(9600);
   Serial.println("ACS712 5A Test");
  
   
}




void loop()
{

  
 double currentAcc = 0;
     int count = 0;
     int adc_raw =0 ; 
     int Max_adc_raw = 0 ;
     int Max_current = 0 ;
     int now_current = 0 ;
     while (count <100)
     {      now_current = analogRead(current01) ;
           adc_raw = abs(now_current - adc_zero); 
          if (Max_adc_raw <= adc_raw)
            {
                 Max_adc_raw = adc_raw ;
                Max_current = now_current ;
            }
          count ++ ;
     }
     
     currentAcc = (Max_adc_raw * 1000)/ACS712_20A ;

 


 Serial.print(currentAcc);
 Serial.print("/");
 Serial.print(Max_current);

 Serial.print("\n");

delay(200);
}



void initCurrentStatus()
{
  
  
}

