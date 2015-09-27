float amps = 0;
float maxAmps = 0;
float minAmps = 0;
float lastAmps = 0;
float noise = 0;

void setup() {
Serial.begin(9600);
}

void loop() {
amps = (516 - analogRead(A2)) * 27.03 / 1023;
amps = (amps + lastAmps) / 2;
lastAmps = amps;
maxAmps = max(maxAmps, amps);
minAmps = min(minAmps, amps);
noise = maxAmps - minAmps;
Serial.print(amps);
Serial.print(" ");
Serial.println(noise);
if (Serial.read() != -1) {maxAmps = amps; minAmps = amps;}
delay(100);
}


/*

https://www.youtube.com/watch?v=UF5jrnXvTlM

http://youtu.be/UF5jrnXvTlM
Using the ACS712 current sensor to measure current in a circuit. Benefits are that it can measure current in the high side of the circuit, adds just 1.2 milliohms to the cuicuit to be measured and includes all the amplification electronics on chip.

float amps = 0;
float maxAmps = 0;
float minAmps = 0;
float lastAmps = 0;
float noise = 0;

void setup() {
Serial.begin(9600);
}

void loop() {
amps = (516 - analogRead(A0)) * 27.03 / 1023;
amps = (amps + lastAmps) / 2;
lastAmps = amps;
maxAmps = max(maxAmps, amps);
minAmps = min(minAmps, amps);
noise = maxAmps - minAmps;
Serial.print(amps);
Serial.print(" ");
Serial.println(noise);
if (Serial.read() != -1) {maxAmps = amps; minAmps = amps;}
delay(100);
}

*/
