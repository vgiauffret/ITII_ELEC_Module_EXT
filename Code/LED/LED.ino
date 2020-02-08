
#include <Arduino.h>

#define LED 33
#define LED1 25

void setup()
{
  // initialize LED digital pin as an output.
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(LED1, OUTPUT);

}

void loop()
{
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED, HIGH);
  digitalWrite(LED1, HIGH);
  // wait for a second
  delay(1000);
  // turn the LED off by making the voltage LOW
  digitalWrite(LED, LOW);
  digitalWrite(LED1, LOW);
  Serial.println("Blink");
  //wait for a second
  delay(1000);
}
