bool ball_sensor = false;
bool manual;

bool ch7MaxExecuted = true;
bool ch7MidExecuted = false;
bool ch4MaxExecuted = true;
bool ch4MidExecuted = false;
bool ch10MaxExecuted = true;
bool ch10MinExecuted = false;

int stop_ball;

enum State {
  SHOOT_ON,
  SHOOT_OFF,
  COLLECT_ON,
  COLLECT_OFF,
  COLLECT_BALL,
  SHOOT_BALL,
};
State robot_flow;
