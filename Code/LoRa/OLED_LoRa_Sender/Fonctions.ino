void cbk(int packetSize) {
  packet ="";
  packSize = String(packetSize,DEC);
  for (int i = 0; i < packetSize; i++) {    ////on parcours les messages stockés 
    if (readRegisterCRC(0x3F) == true){    
    packet += (char) LoRa.read();          // en les stockant dans un string
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
    }
    }
  rssi = "RSSI " + String(LoRa.packetRssi(), DEC) ;
  loraData();  //// Affichage sur l'ecran.
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
