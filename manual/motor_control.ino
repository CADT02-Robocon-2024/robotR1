void motor_control_speed(int motor_id, float desired_speed) {
  motor.speedMode = true;
  motor.stop = false;
  motor.reset = false;
  motor.voltageMode = false;
  motor.goal = desired_speed;
  motor.getCommand(commandData);
  can_msg_transmit.can_id = 0x00 + motor_id; // example ID for the motor controller
  can_msg_transmit.can_dlc = 8; // data length code
  memcpy(can_msg_transmit.data, commandData, 8);
  mcp2515.sendMessage(&can_msg_transmit);

  if (mcp2515.readMessage(&can_msg_receive) == MCP2515::ERROR_OK) {  
    if (can_msg_receive.can_id == 254){
      memcpy(&feedback_position, can_msg_receive.data, sizeof(float));
      memcpy(&feedback_speed, can_msg_receive.data + 4, sizeof(float));
      // Serial.println(feedback_position);
      // Serial.println(feedback_speed);
    }
  }
  delay(10);
}
void motor_control_stop(int motor_id) {
  motor.speedMode = true;
  motor.stop = true;
  motor.reset = false;
  motor.voltageMode = false;
  motor.goal = 0;
  motor.getCommand(commandData);
  can_msg_transmit.can_id = 0x00 + motor_id; // example ID for the motor controller
  can_msg_transmit.can_dlc = 8; // data length code
  memcpy(can_msg_transmit.data, commandData, 8);
  mcp2515.sendMessage(&can_msg_transmit);

  if (mcp2515.readMessage(&can_msg_receive) == MCP2515::ERROR_OK) {  
    if (can_msg_receive.can_id == 254){
      memcpy(&feedback_position, can_msg_receive.data, sizeof(float));
      memcpy(&feedback_speed, can_msg_receive.data + 4, sizeof(float));
      // Serial.println(feedback_position);
      // Serial.println(feedback_speed);
    }
  }
  delay(10);
}
// void motor_control_position(int motor_id, float desired_position) {
//   motor.speedMode = false;
//   motor.stop = false;
//   motor.reset = false;
//   motor.voltageMode = false;
//   motor.goal = desired_position;
//   motor.getCommand(commandData);
//   can_msg_transmit.can_id = 0x00 + motor_id; // example ID for the motor controller
//   can_msg_transmit.can_dlc = 8; // data length code
//   memcpy(can_msg_transmit.data, commandData, 8);
//   mcp2515.sendMessage(&can_msg_transmit);

//   if (mcp2515.readMessage(&can_msg_receive) == MCP2515::ERROR_OK) {  
//     if (can_msg_receive.can_id == 254){
//       memcpy(&feedback_position, can_msg_receive.data, sizeof(float));
//       memcpy(&feedback_speed, can_msg_receive.data + 4, sizeof(float));
//       // Serial.println(feedback_position);
//       // Serial.println(feedback_speed);
//     }
//   }
//   delay(10);
// }