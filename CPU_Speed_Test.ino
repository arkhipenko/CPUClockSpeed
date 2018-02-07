// These lines are for testing on an Arduino ATTiny:
#include <Arduino.h>
#include <SoftSerial.h>
const int rx = 4;
const int tx = 3;
#define   S   mySerial
SoftSerial mySerial(rx, tx); // RX, TX
// end

// Uncomment this to test on Arduino UNO, Nano, ESPx, Teensy:
//#define S Serial
// end

unsigned long t1, t2, cnt;
void setup() {
  // put your setup code here, to run once:
  S.begin(9600);
  S.println(F("Processor speed test"));
  S.println("====================");
  S.print(F("Reported speed=")); S.println((float)(F_CPU/1000000.0));
  S.println();
  delay(5000);
  
  t1 = micros();
  delay(1000);
  t2 = micros();
  S.print(F("Method 1 sec delay (micros): t1=")); S.print(t1); S.print("\tt2="); S.print(t2); S.print("\tdiff="); S.println(t2-t1);
  S.println(); S.flush(); delay(100);

  cnt = 1987895UL; // This takes ~1 second on 16MHz Uno
  unsigned long tmp=0;
  t1 = micros();
  while (cnt-- > 0) {
    asm("nop");
  }
  t2 = micros();
  S.print(F("Method 2: 1M for loop (micros) t1=")); S.print(t1); S.print("\tt2="); S.print(t2); S.print("\tdiff="); S.println(t2-t1);
  S.println(); S.flush();
  float d = (float) t2-t1;
  
  // reverse relationaship:
  // 16 mhz = 1000000 micros
  // X mhz = d micros
  // x = 16 * d / 993937;
  float mhz = 16000000.0 / d;
  S.print(F("Calculated MHz = ")); S.print(mhz); S.println("MHz");
}


void loop() {
  // put your main code here, to run repeatedly:

}
