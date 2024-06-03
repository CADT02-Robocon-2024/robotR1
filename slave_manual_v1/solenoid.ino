void right_up_slider(bool value){
  digitalWrite(solen_S_up_R, value);
}
void right_do_slider(bool value){
  digitalWrite(solen_S_do_R, value);
}
void right_up_griper(bool value){
  digitalWrite(solen_G_up_R, value);
}
void right_do_griper(bool value){
  digitalWrite(solen_G_do_R, value);
}
void left_griper(bool value){
  digitalWrite(solen_G_L, value);
}
void slider(bool value){
  right_up_slider(value);
  right_do_slider(value);
}
