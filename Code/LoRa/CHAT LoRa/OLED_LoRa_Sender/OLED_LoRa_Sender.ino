#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include "SH1106Wire.h"   // legacy: #include "SH1106.h"
#include "images.h"

#define SCK     18    // GPIO5  -- SX1278's SCK
#define MISO    19   // GPIO19 -- SX1278's MISnO
#define MOSI    23   // GPIO27 -- SX1278's MOSI
#define SS      5   // GPIO18 -- SX1278's CS
#define RST     2   // GPIO14 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define BAND  868E6

unsigned int counter = 0;

SH1106Wire display(0x3c, 17, 16);     // ADDRESS, SDA, SCL

String rssi = "RSSI --";
String packSize = "--";
String packet ;

unsigned long Balise_DernierEnvoi = 0; // heure du dernier envoi LoRa



void setup() {
  pinMode(16, OUTPUT);
  pinMode(2, OUTPUT);

  digitalWrite(16, LOW);    // set GPIO16 low to reset OLED
  delay(50);
  digitalWrite(16, HIGH); // while OLED is running, must set GPIO16 in high

  Serial.begin(115200);
  while (!Serial);
  Serial.println();
  Serial.println("LoRa Sender Test");

  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DI0);
  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.enableCrc(); // activer le check de CRC 
  //LoRa.setSpreadingFactor(7);
  //LoRa.onReceive(cbk);
  //  LoRa.receive();
  Serial.println("init ok");
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

  delay(1500);
}

void loop() {
String Message = "";
  
    if (Serial.available()){
      while (Serial.available()){
    Message += Serial.readString();
      }
      //Serial.println(Message);
      counter = 0;
          LoRa.beginPacket();
              Serial.print("Moi: ");
              Serial.println(Message);
    LoRa.print(Message);
    //LoRa.print(counter);
    LoRa.endPacket();
  }

 int packetSize = LoRa.parsePacket();   // onregarde si quelque chose est reçu
  if (packetSize) {
    cbk(packetSize);
  }
  
  /*if (micros() - Balise_DernierEnvoi > 1000000 && counter == 0) {
    Balise_DernierEnvoi = micros();
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_10);

    display.drawString(0, 0, "Sending packet: ");
    display.drawString(90, 0, String(counter));
    Serial.println(String(counter));
    display.display();

    // send packet
    LoRa.beginPacket();
    LoRa.print(Message);
    //LoRa.print(counter);
    LoRa.endPacket();
counter ++;

  }


 int packetSize = LoRa.parsePacket();   // onregarde si quelque chose est reçu
  if (packetSize) {
    cbk(packetSize);
  }

  // wait for a second*/
}
