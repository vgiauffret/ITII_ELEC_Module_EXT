#include <ESPmDNS.h>

#define sensorPin 27 // pin where we connected the LDR and the resistor
#define VBAT 34 // pin where we connected the LDR and the resistor
#define VALIM 35 // 


float sensorValue = 0, sensorVbat = 0, sensorValim =0; // variable to store the value coming from the sensor
void setup() {
Serial.begin(9600); //sets serial port for communication
}
void loop() {
//sensorValue = analogRead(sensorPin); // read the value from the sensor
//sensorVbat = (analogRead(VBAT) * (3.3 / 4095.0)) + 0.27; // read the value from the sensor
sensorVbat = (analogRead(VBAT)+330) * (3.3 / 4095.0); // read the value from the sensor
sensorValim = ((analogRead(VALIM)) * (12 / 4095.0))-1; // read the value from the sensor

//Serial.println(sensorValue); //prints the values coming from the sensor on the screen
Serial.println(sensorVbat); //prints the values coming from the sensor on the screen
Serial.println(sensorValim); //prints the values coming from the sensor on the screen

delay(1000);

}
