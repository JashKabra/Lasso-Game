#include "coin.h"
#include "lasso.h"

void Coin::initCoin() {
  coin_start_x = (PLAY_X_START+WINDOW_X)/2;
  coin_start_y = PLAY_Y_HEIGHT;
  coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);
  coin_circle.setColor(COLOR("yellow"));
  coin_circle.setFill(true);
  addPart(&coin_circle);
}

void Coin::resetCoin1() {
  coin_start_x = (PLAY_X_START+WINDOW_X)/2;
  coin_start_y = PLAY_Y_HEIGHT;
  coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG_LEVEL1;
  coin_ax = 0;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
} //Resets to default position

void Coin::resetCoin2() {
  coin_start_x = (PLAY_X_START+WINDOW_X)/2 -150;
  coin_start_y = PLAY_Y_HEIGHT;
  coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG_LEVEL2;
  coin_ax = 0;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
} //Resets to parabola

void Coin::resetCoin3() {
  coin_start_x = (PLAY_X_START+WINDOW_X)/2+150;
  coin_start_y = PLAY_Y_HEIGHT;
  coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG_LEVEL1;
  coin_ax = 0;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
} // Resets to straight line on right

void Coin::resetCoin4() {
  coin_start_x = (PLAY_X_START+WINDOW_X)/2-150;
  coin_start_y = PLAY_Y_HEIGHT;
  coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG_LEVEL1;
  coin_ax = 0;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
} //Resets to straight line on left

void Coin::resetCoin5() {
  coin_start_x = (PLAY_X_START+WINDOW_X)/2-1000;
  coin_start_y = PLAY_Y_HEIGHT;
  coin_circle.reset(coin_start_x, coin_start_y, COIN_SIZE);
  double coin_speed = COIN_SPEED;
  double coin_angle_deg = COIN_ANGLE_DEG_LEVEL1;
  coin_ax = 0;
  coin_ay = COIN_G;
  bool paused = true, rtheta = true;
  reset_all(coin_start_x, coin_start_y, coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
}// Resets to outside the canvas(Used to destroy coin after level)

void Coin::throwCoin() {
  coin_start_x = 1000;
  reset_cord(coin_start_x, coin_start_y);
}//Throws coin out of window after creation only to call it back later

void Coin::unthrowCoin() {
  coin_start_x = (PLAY_X_START+WINDOW_X)/2-150;
  reset_cord(coin_start_x, coin_start_y);
}//Calls thrown coin back to left position

void Coin::unthrowCoin_right() {
  coin_start_x = (PLAY_X_START+WINDOW_X)/2+150;
  reset_cord(coin_start_x, coin_start_y);
}//Calls coin back to right position

void Coin::unthrowBomb() {
  coin_start_x = (PLAY_X_START+WINDOW_X)/2;
  reset_cord(coin_start_x, coin_start_y);
}//Calls coin back to middle position

void Coin::setColourRed(){
  coin_circle.setColor(COLOR("red"));
  coin_circle.setFill(true);
}

void Coin::setColourBlue(){
  coin_circle.setColor(COLOR("blue"));
  coin_circle.setFill(true);
}

void Coin::setColourGreen(){
  coin_circle.setColor(COLOR(0,150,0));
  coin_circle.setFill(true);
}
void Coin::setColourPurple(){
  coin_circle.setColor(COLOR(200,0,200));
  coin_circle.setFill(true);
}
