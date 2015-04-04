// Configuration files
#include "pin_declaration.h"

// External libraries
#include <avr/wdt.h>

// Internal Libraries
#include "PolledUpdate.h"
#include "PololuDC.h"

// Threads
#include "ProgramHalt.h"
#include "Watchdog.h"


// Parameters
#define ENABLE_WATCHDOG


// Global variables
unsigned long time;

long encoder_position = 0;
unsigned int encoder_errors = 0;


// Threads
Thread Belt_Encoder_Updater(&encoder_cb, 1);
//Thread Debug_Updater(&debug_cb, 100);
//Thread Motor_Updater(&motor_cb, 50);

#ifdef ENABLE_WATCHDOG
Thread Feed_Watchdog_Thread(&feed_watchdog_cb, 100);
#endif

void setup() {
#ifdef ENABLE_WATCHDOG
  wdt_reset();
#endif

  establishSafeState(); // Immediately place system into a safe state



  pinSetup();


#ifdef ENABLE_WATCHDOG
  wdt_enable(WDTO_500MS); // set watch dog to 500 ms
#endif

  Serial.begin(9600);

  waitForEnable();

#ifdef ENABLE_WATCHDOG
  wdt_reset();
#endif
}

void loop() {
  time = millis();

#ifdef ENABLE_WATCHDOG
  Feed_Watchdog_Thread.update(time);
#endif

}

void establishSafeState() {

}

void waitForEnable() {
  static boolean val = true, prev_val = true;
  boolean wait = true;
  while (wait) {
    if (val && !prev_val) {
      wait = false;
    }

    prev_val = val;
    val = digitalRead(CFSW_PAUSE_ENABLE_PIN);
#ifdef ENABLE_WATCHDOG
    wdt_reset();
#endif
    delay(100);
  }

}



void pinSetup() {
  pinMode(CFSW_PAUSE_ENABLE_PIN, INPUT);
  pinMode(ENCR_BELT_LINEAR_A_PIN, INPUT_PULLUP);
  pinMode(ENCR_BELT_LINEAR_B_PIN, INPUT_PULLUP);
}

