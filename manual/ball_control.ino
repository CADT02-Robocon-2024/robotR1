void motor_shoot_ball(float value){
    motor_control_speed(m_shoot,value);
}
void motor_take_ball(float value) {
    motor_control_speed(m_takeBall,value);
}
void solenoid_take_ball(bool value){
  digitalWrite(col_ball,value);
  
}
void stop_motor(int id){
  motor_control_stop(id);
}
// void stop_ball(){

// }