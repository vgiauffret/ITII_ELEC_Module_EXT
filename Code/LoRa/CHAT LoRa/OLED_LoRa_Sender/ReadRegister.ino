bool readRegisterCRC(uint8_t val){
 uint8_t receivedVal = (0000010 | SPI.transfer(val))>>1;
 return (bool)receivedVal;
}

