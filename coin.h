#ifndef __COIN_H__
#define __COIN_H__

#include "MovingObject.h"

class Coin : public MovingObject {
  double coin_start_x;
  double coin_start_y;
  int release_speed;
  double release_angle_deg;
  double coin_ax;
  double coin_ay;

  // Moving parts
  Circle coin_circle;

 public:
 Coin(double speed, double angle_deg, double argax, double argay, bool argpaused, bool rtheta) : MovingObject(speed, angle_deg, argax, argay, argpaused, rtheta) {
    release_speed = speed;
    release_angle_deg = angle_deg;
    coin_ax = argax;
    coin_ay = argay;
    initCoin();
  }

  void initCoin();
  void throwCoin();
  void unthrowCoin();
  void unthrowCoin_right();
  void unthrowBomb();
  void unthrowCoin_left();

  void resetCoin1();
  void resetCoin2();
  void resetCoin3();
  void resetCoin4();
  void resetCoin5();

  void setColourRed();
  void setColourBlue();
  void setColourGreen();
  void setColourPurple();
}; // End class Coin

#endif

