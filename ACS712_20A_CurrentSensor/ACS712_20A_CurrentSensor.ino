//ACS712-20A_CurrentSensor/ACS712_20A_CurrentSensor/ACS712_20A_CurrentSensor.ino
//https://github.com/bavensky/ACS712-20A_CurrentSensor/blob/master/ACS712_20A_CurrentSensor/ACS712_20A_CurrentSensor.ino

  /******************************************************************************
   * Project  : 20 A Current Sensor                                              *
   * Compiler : Arduino 1.5.5-r2                                                 *
   * Board    : Arduino UNO                                                      *
   * Shield   : -                                                                *
   * Module   : ACS712 Module                                                    *
   *          :                                                                  *
   * Author   : Bavensky :3                                                      *
   * E-Mail   : Aphiruk_Sang-ngenchai@hotmail.com                                *
   * Date     : 09/11/2014 [dd/mm/yyyy]                                          *
   *******************************************************************************/
  
  float mmm = 0;            // ประกาศตัวแปรแบบเลขทศนิยมตั้งชื่อว่า mmm มีค่าเท่ากับ 0 
  int i=0;                  // ประกาศตัวแปรแบบเลขจำนวนเต็มชื่อว่า i   มีค่าเท่ากับ 0 
  int sensorValue =0;       // ประกาศตัวแปรแบบเลขจำนวนเต็มชื่อว่า sensorValue  มีค่าเท่ากับ 0 
  
  void setup() {
    Serial.begin(9600);    // เปิดใช้งาน UART ที่อัดตราบอด 9600
  }
  
  void loop() 
  {    
    
    /*************** The formula for AC ***************************************************************************
    - sensorValue - 512)
        sensorValue คือ ค่าที่อ่านได้จากขา analog A0
            จาก output voltage versus sensed current ใน datasheet ถ้าระดับแรงดันเป็น 2.5 V กระแสจะได้ 0 A ที่ Ip = 20 A
          เช่น ถ้า analogRead อ่านได้ 0 เปลี่ยนเป็นแรงดันก็จะได้ 0 v แต่ถ้าอ่านได้ 1023 แรงดันก็จะได้ 5 v ส่วนกึ่งกลางคือ 1024/2 = 512
        512 คือ ค่ากึ่งกลางหรือ 2.5 V ก็จะได้กระแสเท่ากับ 0 A 
    - * (5.0 / 1023.0) แปลงให้เป็นแรงดัน มีหน่วยเป็น V 
    - 0.1 คือเปลี่ยนหน่วยจาก  mV เป็น V  เนื่องจาก Typ. 100 mV/A = 0.1 คือค่า Sensitivity ซึ่งมีหน่วยเป็น mV/A
    ***************************************************************************************************************/
  
    sensorValue = analogRead(A1);        // อ่านค่าจากขา Analog A0 เก็บไว้ในตัวแปร sensorValue
    float voltage = (  (sensorValue - 512) * (5.0 / 1023.0)  ) / 0.1;    // แปลงแรงดันให้เป็นกระแส
    
    mmm = mmm + abs(voltage);     // เก็บไว้ในตัวแปร mmm โดยใช้คำสั่ง abs เพื่อไม่ให้มีค่าลบ(-) เนื่องจากอ่านค่าจากไฟฟ้ากระแสสลับจึงมีทั้งบวกและลบ
  
    // อ่านค่าทุก ๆ 100 มิลลิวินาที
    i++;
    if(i>99) 
    {
      
      mmm = mmm / 100;
      Serial.print("Current : ");
      Serial.print(mmm);
      Serial.println(" A");
      mmm=0;    // กำหนดให้ mmm = 0 เพื่อเริ่มเก็บค่าใหม่
      i=0;      // กำหนดให้ i = 0 เพื่อเริ่มการแสดงผลใหม
    }  
    delay(1);
    
    
    
    /*************** The formula for DC ********************************
    float average = 0;
    for(int i = 0; i < 1000; i++) {
      average = average + (0.049 * analogRead(A0) - 25) / 1000;
      delay(1);
    }
    Serial.println(average);  
    ********************************************************************/
  }
