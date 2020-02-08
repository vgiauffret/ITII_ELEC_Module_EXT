void cbk(int packetSize) {
  packet ="";
  packSize = String(packetSize,DEC);
  for (int i = 0; i < packetSize; i++) { 
    if (readRegisterCRC(0x3F) == true){
    packet += (char) LoRa.read(); 
    }
    else
    {
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0 , 15 , "Received "+ packSize + " bytes");
  display.drawStringMaxWidth(0 , 26 , 128, packet);
  display.drawString(0, 0, "erreur CRC"); 
  display.display();
  while(1);
    }
    }
    Serial.print("Lui: ");
      Serial.println(packet);
  rssi = "RSSI " + String(LoRa.packetRssi(), DEC) ;
  loraData();
}

void loraData(){
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0 , 15 , "Received "+ packSize + " bytes");
  display.drawStringMaxWidth(0 , 26 , 128, packet);
  display.drawString(0, 0, rssi); 
  display.display();
}
