#ifndef CONFIG_H_
#define CONFIG_H_

#include "main.h"
using namespace okapi;
extern okapi::Motor leftBase1;
extern okapi::Motor leftBase2;

extern okapi::Motor rightBase1;
extern okapi::Motor rightBase2;

extern okapi::Motor intake;

extern okapi::Motor shoot;
extern okapi::Motor angle;
extern okapi::AsyncPosIntegratedController angleController;

extern okapi::Controller controller;

extern okapi::ADIGyro gyro1;
extern pros::ADILineSensor line;

extern okapi::IterativePosPIDController left_PID;
extern okapi::IterativePosPIDController right_PID;

extern okapi::IterativePosPIDController turnAngle_PID;

extern okapi::MotorGroup leftBase;
extern okapi::MotorGroup rightBase;
extern okapi::ChassisControllerIntegrated chassis;

#endif