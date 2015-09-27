#include <EEPROM.h>

int address = 20;
int val ;

void setup() {
  Serial.begin(9600);

  // 在 address = 20 上寫入數值120
  EEPROM.write(address, 120);

  // 讀取 address =20 上的內容
  val = EEPROM.read(address);


  Serial.print(val,DEC);  //  十進位為印出 val
  Serial.print("/");
  Serial.print(val,HEX);  //  十六進位為印出 val
  Serial.println("");
}

void loop() {
}


