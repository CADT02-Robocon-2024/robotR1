void sbus_data(){
  channels = "";
  for (int8_t i = 0; i < 12; i++) {
    Serial.print(i);
    Serial.print(":");
    Serial.print(data.ch[i]);
    Serial.print("\t");
  }
  Serial.println(channels);
}
// void sbus_tran(){
//   // data = sbus_rx.data();
//     // Send SBUS data over I2C
//   Wire.beginTransmission(8); // Address of the slave Arduino
//   for (int8_t i = 0; i < 12; i++) {
//     // Split the SBUS data into two bytes
//     byte highByte = data.ch[i] >> 8;
//     byte lowByte = data.ch[i] & 0xFF;
    
//     Wire.write(highByte); // Send the high byte
//     Wire.write(lowByte);  // Send the low byte
//   }
//   Wire.endTransmission();

//   // Delay if needed to avoid flooding the I2C bus
//   delay(10); // Adjust delay as necessary
// }