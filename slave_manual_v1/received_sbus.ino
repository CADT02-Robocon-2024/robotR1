void printsbus() {
  // Do whatever you want with the received SBUS data
  // For example, print it to the serial monitor
  for (int i = 0; i < 12; i++) {
    Serial.print(sbusData[i]);
    Serial.print("\t");
  }
  Serial.println();
  delay(10); // Adjust delay as necessary
}

void receiveData(int byteCount) {
  // Receive data from the master
  int i = 0;
  while (Wire.available() >= 2 && i < 12) {
    byte highByte = Wire.read(); // Read the high byte
    byte lowByte = Wire.read();  // Read the low byte
    sbusData[i++] = (highByte << 8) | lowByte; // Reconstruct the value
  }
}
