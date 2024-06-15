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
  pinMode(stop_ball_sensor, INPUT);
  motor_take_ball(0);
  motor_shoot_ball(0);

}

void loop() {
  stop_ball = digitalRead(stop_ball_sensor);
  Serial.println(stop_ball);
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
    // if(data.ch[7] == max_value && !ch7MaxExecuted){
    //   robot_flow = SHOOT_ON;
    //   control_shoot_ball(); 
    //   ch7MaxExecuted = true;
    //   ch7MinExecuted = false;
    // }else if (data.ch[7] == min_value && !ch7MinExecuted){
    //   robot_flow = SHOOT_OFF;
    //   control_shoot_ball(); 
    //   ch7MinExecuted = true;
    //   ch7MaxExecuted = false;
    // }
    // if(data.ch[4] == max_value && !ch4MaxExecuted){
    //   robot_flow = COLLECT_ON;
    //   control_shoot_ball(); 
    //   ch4MaxExecuted = true;
    //   ch4MinExecuted = false;
    // }else if (data.ch[4] == min_value && !ch4MinExecuted){
    //   robot_flow = COLLECT_OFF;
    //   control_shoot_ball(); 
    //   ch4MinExecuted = true;
    //   ch4MaxExecuted = false;
    // }    
    // if(data.ch[10] == max_value && !ch10MaxExecuted){
    //   robot_flow = COLLECT_BALL;
    //   control_shoot_ball(); 
    //   ch10MaxExecuted = true;
    //   ch10MinExecuted = false;
    // }else if (data.ch[10] == min_value && !ch10MinExecuted){
    //   robot_flow = SHOOT_BALL;
    //   control_shoot_ball(); 
    //   ch10MinExecuted = true;
    //   ch10MaxExecuted = false;
    // }    
    control_shoot_ball();
  }
  
  
}

void control_shoot_ball(){
    if (data.ch[10] == max_value){
      solenoid_take_ball(1);
      if(stop_ball == 0){
        ball_sensor = true;
        stop_motor(m_takeBall);

      }
      ch10MinExecuted = true;
    }else if (data.ch[10] == min_value && ch10MinExecuted){
      
      
      motor_take_ball(200);
      // delayForSeconds(1);
      if(stop_ball == 1){
        ch10MinExecuted =false;
        ball_sensor = false;
        solenoid_take_ball(0);
      }
      // solenoid_take_ball(0);
    }
    if (data.ch[7] == max_value){
      motor_shoot_ball(800);
    }else if (data.ch[7] == mid_value){
      stop_motor(m_shoot);
    }
    if (data.ch[4] == max_value && !ball_sensor) {
      motor_take_ball(200);
    }else if(data.ch[4] == mid_value){
      stop_motor(m_takeBall);
    }
}
// void control_shoot_ball(){
//   switch (robot_flow) {
//     case SHOOT_ON:
//       motor_shoot_ball(800);
//       break;
//     case SHOOT_OFF:
//       motor_shoot_ball(0);
//       break;
//     case COLLECT_ON:
//       motor_take_ball(200);
//       break;
//     case COLLECT_OFF:
//       motor_take_ball(0);
//       break;
//     case COLLECT_BALL:
//       solenoid_take_ball(1);
//       if(stop_ball == 1){
//         motor_take_ball(0);
//         solenoid_take_ball(0);
//       }
//       break;
//     case SHOOT_BALL:
//       motor_take_ball(200);
//       break;
//   }
// }
void delayForSeconds(unsigned int seconds) {
  unsigned long end = millis() + seconds * 1000;
  while (millis() < end) {
    // Do nothing, just wait
  }
}

