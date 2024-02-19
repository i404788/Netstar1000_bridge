#include <DigiCDC.h>

/*
UPS Bridge for NetStar 1600 using a Digispark Tiny

Connection map (Digispark -> DB9):
- 1 <-> 6 (Not actually connected since it may have different voltage)
- 2 <-> 5
- 0 <-> 2

*/

#define UPS_SHUTDOWN_PIN 1
#define LOW_BAT_PIN 2
#define MAINS_FAILURE_PIN 0

void setup() {
  SerialUSB.begin();
  pinMode(UPS_SHUTDOWN_PIN, INPUT); // Pin 6 (PB1) (UPS shutdown on 1s high, LED used as pull-down)
  pinMode(LOW_BAT_PIN, INPUT_PULLUP); // Pin 5 (PB0) (Pulled low on Low Battery)
  pinMode(MAINS_FAILURE_PIN, INPUT_PULLUP); // Pin 7 (PB2) (Pull low on Mains Falure)
}

// the loop routine runs over and over again forever:
void loop() {
  if (SerialUSB.available()) {
    byte v = SerialUSB.read();
  //   SerialUSB.write(v);
  //   SerialUSB.write(v);
    bool low_battery = !digitalRead(LOW_BAT_PIN);
    bool main_failure = !digitalRead(MAINS_FAILURE_PIN);
    bool ups_shutdown = digitalRead(UPS_SHUTDOWN_PIN);

    byte state = low_battery | main_failure << 1 | ups_shutdown << 2 | 1 << 3;
    SerialUSB.write(state);
  }
  SerialUSB.refresh();
  // SerialUSB.delay(100);
   /*
   if you don't call a SerialUSB function (write, print, read, available, etc) 
   every 10ms or less then you must throw in some SerialUSB.refresh(); 
   for the USB to keep alive - also replace your delays - ie. delay(100); 
   with SerialUSB.delays ie. SerialUSB.delay(100);
   */
}

