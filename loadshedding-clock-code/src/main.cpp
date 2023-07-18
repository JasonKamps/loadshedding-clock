#include <Arduino.h>

void setup() {
  // setup serial
  Serial.begin(19200);

  while (!Serial) {
    // wait for serial port to connect
  }

  Serial.println("Hello World!");
}

void loop() {
  Serial.print(".");
  delay(1000);
}
