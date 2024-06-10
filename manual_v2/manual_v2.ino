#include "R1_header.h"
#include "PIN_ASSIGN.h"
#include "logic.h"

/*x1 -> 0
  y1 -> 1
  y2 -> 2
  x2 -> 3
  E  -> 4
  y3 -> 5
  x3 -> 6
  F  -> 7
  A  -> 8
  B  -> 9
  C  -> 10
  D  -> 11
*/

void setup() {
  Serial.begin(115200);
  // Wire.begin(); // Initialize I2C communication as Master
  sbus_rx.Begin();
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
  pinMode(col_ball,OUTPUT);
  pinMode(stop_ball_sensor, OUTPUT);

}

void loop() {
  if (sbus_rx.Read()) {
    data = sbus_rx.data();
    // sbus_data();
    // sbus_tran();
  }
    
    // sbus_data();
  if (data.ch[8] == max_value) {
    // sbus_tran();
    manual = true;        
  }else{
    manual = false;
  }
  if(manual == true) {
    movement();
    control_shoot_ball(); 
  }
  
  
}

void control_shoot_ball(){
    if (data.ch[10] == max_value){
      solenoid_take_ball(1);
    }else{
      solenoid_take_ball(0);
    }
    if (data.ch[7] == max_value){
      motor_shoot_ball(700);
    }else if (data.ch[7] == mid_value){
      motor_shoot_ball(0);
    }
    if (data.ch[4] == max_value) {
      motor_take_ball(300);
    }else if(data.ch[4] == mid_value){
      motor_take_ball(0);
    }
}
