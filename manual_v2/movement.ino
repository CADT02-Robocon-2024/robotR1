void movement(){
  float Vx = map1(data.ch[1], 282, 1722, 200.00, -200.00);
  float Vy = map1(data.ch[0], 282, 1722, -200.00, 200.00);
  float omega = map1(data.ch[3], 282, 1722, -1.00, 1.00);
  // Serial.print("Vx:");
  // Serial.println(Vx);
  // Serial.print("Vy:");
  // Serial.println(Vy);
  // Serial.print("omega:");
  // Serial.println(omega);
  
  
  float lx = 40;
  float ly = 30;
  float r = 6.35;

  M[0] = (Vx - Vy - (lx + ly) * omega) * 1 / r;
  M[1] = (Vx + Vy + (lx + ly) * omega) * 1 / r;
  M[2] = (Vx - Vy + (lx + ly) * omega) * 1 / r;
  M[3] = (Vx + Vy - (lx + ly) * omega) * 1 / r;

  // Serial.print("M1:");
  // Serial.println(M[0]);
  // Serial.print("M2:");
  // Serial.println(M[1]);
  // Serial.print("M3:");
  // Serial.println(M[2]);
  // Serial.print("M4:");
  // Serial.println(M[3]);

  motor_control_speed(1, M[0]);
  motor_control_speed(2, -M[1]);
  motor_control_speed(3, -M[2]);
  motor_control_speed(4, M[3]);

}