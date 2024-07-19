#include <LEDs.h>

LEDs led(1);

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println(led.getLEDState());
}
