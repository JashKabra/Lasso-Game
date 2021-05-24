#include <simplecpp>
#include <cstdio>
#include <cstdlib>
#include <string>
#include<fstream>
#include "MovingObject.h"
#include "lasso.h"
#include "coin.h"

void printscore(char name[6][100], int score[6]){
  int a;
  if(score[5]>=score[0]){a=0;}
  else if(score[5]>=score[1]){a=1;}
  else if(score[5]>=score[2]){a=2;}
  else if(score[5]>=score[3]){a=3;}
  else if(score[5]>=score[4]){a=4;}
  else a=5;
  char final_name[6][100];
  int final_score[6];
  strcpy(final_name[a],name[5]);
  final_score[a]=score[5];
  for(int i=0;i<a;i++){
    final_score[i]=score[i];
    strcpy(final_name[i],name[i]);
  }
  for(int i=a+1;i<6;i++){
    final_score[i]=score[i-1];
    strcpy(final_name[i],name[i-1]);
  }
  ofstream print_name("Names.txt");
    for(int i=0;i<5;i++){
        print_name<<final_name[i]<<endl;
    }
  //Names file updated
  print_name.close();
  ofstream print_score("Scores.txt");
    for(int i=0;i<6;i++){
        print_score<<final_score[i]<<endl;
    }
  //Scores file updated
  print_score.close();
  cout<<"Congratulations your final score is "<<score[5]<<endl;
  cout<<"Here is the final scoreboard"<<endl;
  cout<<"Rank   Score   Name"<<endl;
  for(int i=1;i<6;i++){
  cout<<i<<"      "<<final_score[i-1]<<"       "<<final_name[i-1]<<endl;
  }

}

using namespace simplecpp;
main_program {
  char player_name[6][100];
  int player_score[6];
  cout<<"Enter your name."<<endl;
  cin.getline(player_name[5],100);

  ifstream read_name("Names.txt");
  for(int i=0;i<5;i++){
    read_name.getline(player_name[i],100);
  }
  read_name.close();

  ifstream read_score("Scores.txt");
  for(int i=0;i<5;i++){
    read_score>>player_score[i];
  }
  read_score.close();

  cout<<"Here is the scoreboard to beat."<<endl;
  cout<<"Rank   Score   Name"<<endl;
  for(int i=1;i<6;i++){
  cout<<i<<"      "<<player_score[i-1]<<"       "<<player_name[i-1]<<endl;
  }
  wait(1);

  initCanvas("Lasso", WINDOW_X, WINDOW_Y);
  Rectangle r(WINDOW_X/2,WINDOW_Y/2,WINDOW_X+50,WINDOW_Y+50);
  r.setColor(COLOR(0,250,250));
  r.setFill(true);
  int stepCount = 0;
  float stepTime = STEP_TIME;
  float runTime = -1; // sec; -ve means infinite
  float currTime = 0;

  // Draw lasso at start position
  int release_speed = INIT_RELEASE_SPEED; // m/s
  double release_angle_deg = INIT_RELEASE_ANGLE_DEG; // degrees
  double lasso_ax = 0;
  double lasso_ay = LASSO_G;
  bool paused = true;
  bool rtheta = true;
  Lasso lasso(release_speed, release_angle_deg, lasso_ax, lasso_ay, paused, rtheta);

  Line b1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);
  b1.setColor(COLOR("blue"));
  Line b2(PLAY_X_START, 0, PLAY_X_START, WINDOW_Y);
  b2.setColor(COLOR("blue"));

  //Printing the different types of coins
  string coin1(": Normal Coin");
  Text charcoin1(WINDOW_X-95,10, coin1);
  string coin2(": Bomb");
  Text charcoin2(WINDOW_X-116,25, coin2);
  string coin3(": Speedup Coin");
  Text charcoin3(WINDOW_X-90,40, coin3);
  string coin4(": Slowdown Coin");
  Text charcoin4(WINDOW_X-85,55, coin4);
  string coin5(": Negative Coin");
  Text charcoin5(WINDOW_X-85,70, coin5);

  Circle c1(WINDOW_X-150,10,COIN_SIZE);
  c1.setColor(COLOR("yellow"));
  c1.setFill(true);
  Circle c2(WINDOW_X-150,25,COIN_SIZE);
  c2.setColor(COLOR("red"));
  c2.setFill(true);
  Circle c3(WINDOW_X-150,40,COIN_SIZE);
  c3.setColor(COLOR("blue"));
  c3.setFill(true);
  Circle c4(WINDOW_X-150,55,COIN_SIZE);
  c4.setColor(COLOR(0,150,0));
  c4.setFill(true);
  Circle c5(WINDOW_X-150,70,COIN_SIZE);
  c5.setColor(COLOR(200,0,200));
  c5.setFill(true);
  Rectangle r2(WINDOW_X-90,40,140,76);
  r2.setColor(COLOR("white"));

  //Printing the stats of current player
  string msg("Cmd: _");
  Text charPressed(PLAY_X_START+50, PLAY_Y_HEIGHT+20, msg);
  char coinScoreStr[256];
  sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
  Text coinScore(PLAY_X_START+50, PLAY_Y_HEIGHT+40, coinScoreStr);
  char levelStr[256];
  sprintf(levelStr, "Level: %d", lasso.getLevel());
  Text lev(PLAY_X_START+50, PLAY_Y_HEIGHT+60, levelStr);
  char speedStr[256];
  sprintf(speedStr, "Speed: %d", lasso.getSpeed());
  Text speed(PLAY_X_START+50, PLAY_Y_HEIGHT+80, speedStr);
  Rectangle r3(PLAY_X_START+50,PLAY_Y_HEIGHT+50,80,80);
  r3.setColor(COLOR("white"));

  //Printing the different commands
  string cmd1("t: Throw");
  Text Throw(WINDOW_X-100, PLAY_Y_HEIGHT+15, cmd1);
  string cmd2("y: Yank");
  Text yank(WINDOW_X-100, PLAY_Y_HEIGHT+30, cmd2);
  string cmd3("l: Loop");
  Text Loop(WINDOW_X-100, PLAY_Y_HEIGHT+45, cmd3);
  string cmd4("]: Angle +");
  Text AngleIncr(WINDOW_X-95, PLAY_Y_HEIGHT+60, cmd4);
  string cmd5("[: Angle -");
  Text AngleDecr(WINDOW_X-95, PLAY_Y_HEIGHT+75, cmd5);
  string cmd6("q: Quit");
  Text Quit(WINDOW_X-100, PLAY_Y_HEIGHT+90, cmd6);
  Rectangle r1(WINDOW_X-100,PLAY_Y_HEIGHT+50,100,95);
  r1.setColor(COLOR("white"));
  paused = true; rtheta = true;

  double coin_speed = COIN_SPEED;
  double coin_angle_deg=COIN_ANGLE_DEG_LEVEL1;
  double coin_ax = 0;
  double coin_ay = COIN_G;
  Coin coin(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
  Coin coin_new(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
  coin_new.throwCoin();
  Coin negativecoin(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
  negativecoin.setColourPurple();
  negativecoin.throwCoin();
  Coin coin_fast(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
  Coin coin_slow(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
  coin_fast.throwCoin();
  coin_slow.throwCoin();
  coin_fast.setColourBlue();
  coin_slow.setColourGreen();
  Coin bomb(coin_speed, coin_angle_deg, coin_ax, coin_ay, paused, rtheta);
  bomb.throwCoin();
  bomb.setColourRed();
  // After every COIN_GAP sec, make the coin jump
  double last_coin_jump_end = 0;

  // When t is pressed, throw lasso
  // If lasso within range, make coin stick
  // When y is pressed, yank lasso
  // When l is pressed, loop lasso
  // When q is pressed, quit


  for(;;) {
    if((runTime > 0) && (currTime > runTime)) { break; }

    XEvent e;
    bool pendingEv = checkEvent(e);
    if(pendingEv) {
      char c = charFromEvent(e);
      msg[msg.length()-1] = c;
      charPressed.setMessage(msg);
      switch(c) {
      case 't':
	lasso.unpause();
	break;
      case 'y':
	lasso.yank();
	break;
      case 'l':
	lasso.loopit();
	if(lasso.getLevel()<3){
      lasso.check_for_coin(&coin);
	}
	if(lasso.getLevel()==3){
      lasso.check_for_both_coins(&coin,&coin_new);
	}
	if(lasso.getLevel()==4){
      //If bomb is caught game over
      if(lasso.check_for_coin_speed(&bomb)){
        Rectangle r4(WINDOW_X/2,WINDOW_Y/2,WINDOW_X+50,WINDOW_Y+50);
        r4.setColor(COLOR("red"));
        r4.setFill(true);
        Text t(WINDOW_X/2,WINDOW_Y/2,"GAME OVER");
        t.scale(100);
        t.setColor(COLOR("blue"));
        wait(3);
        player_score[5]=lasso.getNumCoins();
        printscore(player_name,player_score);
	    exit(3);
      }
      lasso.check_for_coin(&coin);
	}
	if(lasso.getLevel()==5){
      lasso.check_for_coin(&coin);
      if(lasso.check_for_coin_speed(&coin_fast)){
        lasso.addSpeed(+RELEASE_SPEED_STEP);
        lasso.yank();
      }
      if(lasso.check_for_coin_speed(&coin_slow)){
        lasso.addSpeed(-RELEASE_SPEED_STEP);
        lasso.yank();
      }
	}
	if(lasso.getLevel()==6){
      lasso.check_for_negativecoin(&negativecoin);
      lasso.check_for_coin(&coin);
	}

	wait(STEP_TIME*5);
	lasso.unloopit();
	break;
      case '[':
	if(lasso.isPaused()) { lasso.addAngle(-RELEASE_ANGLE_STEP_DEG);	}
	break;
      case ']':
	if(lasso.isPaused()) { lasso.addAngle(+RELEASE_ANGLE_STEP_DEG); }
	break;
      case 'q':
    player_score[5]=lasso.getNumCoins();
    printscore(player_name,player_score);
	exit(3);
      default:
	break;
      }
    }

    lasso.nextStep(stepTime);
    bomb.nextStep(stepTime);
    coin.nextStep(stepTime);
    coin_new.nextStep(stepTime);
    negativecoin.nextStep(stepTime);
    coin_fast.nextStep(stepTime);
    coin_slow.nextStep(stepTime);

    if(coin.isPaused()) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
	    coin.unpause();
      }
    }
    if(coin_new.isPaused()&&lasso.getLevel()>=3) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
        if(lasso.getLevel()==3){coin_new.unthrowCoin();}
	    coin_new.unpause();
      }
    }
    if(bomb.isPaused()&&lasso.getLevel()>=4) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
        if(lasso.getLevel()==4){bomb.unthrowBomb();}
	    bomb.unpause();
      }
    }
    if(coin_fast.isPaused()&&lasso.getLevel()>=5) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
        if(lasso.getLevel()==5){coin_fast.unthrowCoin_right();}
	    coin_fast.unpause();
      }
    }
    if(coin_slow.isPaused()&&lasso.getLevel()>=5) {
      if((currTime-last_coin_jump_end) >= COIN_GAP) {
        if(lasso.getLevel()==5){coin_slow.unthrowCoin();}
	    coin_slow.unpause();
      }
    }
    if(negativecoin.isPaused()&&lasso.getLevel()>=6) {
      if((currTime-last_coin_jump_end) >= BOMB_GAP) {
        if(lasso.getLevel()==6){negativecoin.unthrowBomb();}
	    negativecoin.unpause();
      }
    }

    if(coin.getYPos() > PLAY_Y_HEIGHT) {
      if(lasso.getLevel()==1){
        coin.resetCoin1();
      }
      if(lasso.getLevel()==2){
        coin.resetCoin2();
      }
      if(lasso.getLevel()==3){
        coin.resetCoin3();
      }
      if(lasso.getLevel()==4){
        coin.resetCoin2();
      }
      if(lasso.getLevel()>=5){
        coin.resetCoin1();
      }
      last_coin_jump_end = currTime;
    }

    if(coin_new.getYPos() > PLAY_Y_HEIGHT) {

      if(lasso.getLevel()==3){
        coin_new.resetCoin4();
      }
      if(lasso.getLevel()>3){
        coin_new.resetCoin5();
      }
      last_coin_jump_end = currTime;
    }
    if(bomb.getYPos() > PLAY_Y_HEIGHT) {

      if(lasso.getLevel()==4){
        bomb.resetCoin1();
      }
      if(lasso.getLevel()>4){
        bomb.resetCoin5();
      }
      last_coin_jump_end = currTime;
    }
    if(coin_fast.getYPos() > PLAY_Y_HEIGHT) {

      if(lasso.getLevel()==5){
        coin_fast.resetCoin3();
      }
      if(lasso.getLevel()>5){
        coin_fast.resetCoin5();
      }
      last_coin_jump_end = currTime;
    }
    if(coin_slow.getYPos() > PLAY_Y_HEIGHT) {

      if(lasso.getLevel()==5){
        coin_slow.resetCoin4();
      }
      if(lasso.getLevel()>5){
        coin_slow.resetCoin5();
      }
      last_coin_jump_end = currTime;
    }
    if(negativecoin.getYPos() > PLAY_Y_HEIGHT) {

      if(lasso.getLevel()==6){
        negativecoin.resetCoin1();
      }
      if(lasso.getLevel()>6){
        negativecoin.resetCoin5();
      }
      last_coin_jump_end = currTime;
    }
    if(lasso.getLevel()==7){
        //6 levels only 7th level reached implies won
        Rectangle r4(WINDOW_X/2,WINDOW_Y/2,WINDOW_X+50,WINDOW_Y+50);
        r4.setColor(COLOR("red"));
        r4.setFill(true);
        Text t(WINDOW_X/2,WINDOW_Y/2,"CONGRATS YOU COMPLETED THE GAME");
        t.scale(100);
        t.setColor(COLOR("blue"));
        wait(3);
        player_score[5]=lasso.getNumCoins();
        printscore(player_name,player_score);
	    exit(3);
    }

    sprintf(coinScoreStr, "Coins: %d", lasso.getNumCoins());
    coinScore.setMessage(coinScoreStr);
    sprintf(levelStr, "Level: %d", lasso.getLevel());
    lev.setMessage(levelStr);
    sprintf(speedStr, "Speed: %d", lasso.getSpeed());
    speed.setMessage(speedStr);

    stepCount++;
    currTime += stepTime;
    //wait(stepTime/100);
  } // End for(;;)


  wait(3);
} // End main_program

