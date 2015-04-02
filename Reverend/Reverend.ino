#include "pin_declaration.h"
#include "PolledUpdate.h"
// To Do:
//     io latch manager



unsigned long time;

long encoder_position = 0;
unsigned int encoder_errors = 0;

void debug_cb(unsigned long time) {
  Serial.print(encoder_errors);
  Serial.print('\t');
  Serial.println(encoder_position);
}

PolledUpdate Belt_Encoder_Updater(&encoder_cb, 1);
PolledUpdate Debug_Updater(&debug_cb, 100);

void setup() {
  Serial.begin(9600);

  // Pin setup
  pinMode(ENCR_BELT_LINEAR_A_PIN, INPUT_PULLUP);
  pinMode(ENCR_BELT_LINEAR_B_PIN, INPUT_PULLUP);
}

void loop() {
  time = millis();
  Belt_Encoder_Updater.update(time);
  Debug_Updater.update(time);
}



