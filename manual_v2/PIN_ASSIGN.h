#define min_value 282
#define mid_value 1002
#define max_value 1722

#define col_ball 6
#define stop_ball_sensor 7

#define m_shoot 6
#define m_takeBall 5



float map1(float Input, float Min_Input , float Max_Input , float Min_Output, float Max_Output) {

  return (float) ((Input - Min_Input) * (Max_Output - Min_Output) / (Max_Input - Min_Input) + Min_Output);
}