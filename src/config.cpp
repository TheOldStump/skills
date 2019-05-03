#include "main.h"
using namespace okapi;

auto leftBase1 = Motor(1, false, AbstractMotor::gearset::green);
auto leftBase2 = Motor(3, false, AbstractMotor::gearset::green);

auto rightBase1 = Motor(2, true, AbstractMotor::gearset::green);
auto rightBase2 = Motor(9, true, AbstractMotor::gearset::green);

auto intake = Motor(7, false, AbstractMotor::gearset::green);

auto shoot = Motor(8, false, AbstractMotor::gearset::green);
auto angle = Motor(10, false, AbstractMotor::gearset::green);
auto angleController = AsyncControllerFactory::posIntegrated(angle, 200);

auto gyro1 = ADIGyro(1, 1.0);
auto line = pros::ADILineSensor(2);

auto sonic = ADIUltrasonic(3, 4);

auto controller = Controller();

//Driving PID config
const double drive_P = 0.0023;      //0.008      
const double drive_I = 0.0009;        //0.0     
const double drive_D = 0.000003;     //0.0001   

auto left_PID = IterativeControllerFactory::posPID(drive_P, drive_I, drive_D);
auto right_PID = IterativeControllerFactory::posPID(drive_P, drive_I, drive_D);

auto turnAngle_PID = IterativeControllerFactory::posPID(0.00705, 0.0087, 0.00003);

auto leftBase = MotorGroup({leftBase1, leftBase2});
auto rightBase = MotorGroup({rightBase1, rightBase2});
auto chassis = ChassisControllerFactory::create(leftBase, rightBase, AbstractMotor::gearset::green, {4_in, 245_mm});

auto ernur = Motor(11, true, AbstractMotor::gearset::green);
auto ernurController = AsyncControllerFactory::posIntegrated(ernur, 200);