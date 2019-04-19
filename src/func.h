#ifndef FUNC_H_
#define FUNC_H_

#include "main.h"

using namespace okapi;

void shoot_twice();
void TurnAngle(double degrees);
void drive(double dis);
void stop();
void calib(bool frwd, int millis);
void no_palka(int x);
void ball_in_the_middle(int x);
void getBallIntake(void* params);
void pre_driving();

#endif