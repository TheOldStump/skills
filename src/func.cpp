#include "main.h"
#include "config.h"

void ball_in_the_middle(int x)
{
    int line_value = line.get_value();
    int start_time = pros::millis();
    while (true)
    {
        int current_time = pros::millis();

        int current_line_value = line.get_value();
        int diff = abs(current_line_value - line_value);

        intake.move(x);
        if (diff > 30 || (current_time - start_time > 3000))
        {
            break;
        }
        pros::delay(1);
    }
    intake.move(0);
}
//stop the base
void stop()
{
    leftBase.moveVoltage(0);
    rightBase.moveVoltage(0);
}

//delay drive to calibrate
void calib(bool frwd, int millis)
{
    if (frwd)
    {
        leftBase.moveVoltage(5000);
        rightBase.moveVoltage(5000);
        pros::delay(millis);
    }
    else
    {
        leftBase.moveVoltage(-5000);
        rightBase.moveVoltage(-5000);
        pros::delay(millis);
    }
}

//two flags(middle and highest)
void shoot_twice()
{
    angleController.setTarget(0.0);
    angleController.waitUntilSettled();
    shoot.move(127);
    pros::delay(650);
    shoot.move(0);
    intake.move(-127);
    pros::delay(350);
    intake.move(0);
    angleController.setTarget(55.0);
    angleController.waitUntilSettled();
    shoot.move(127);
    pros::delay(700);
    shoot.move(0);
}

//PID turning
void TurnAngle(double degrees)
{
    gyro1.reset();
    turnAngle_PID.reset();
    turnAngle_PID.setTarget(degrees);
    while (!turnAngle_PID.isSettled())
    {
        double position = gyro1.get() / 10;
        double power = turnAngle_PID.step(position);
        leftBase.controllerSet(power);
        rightBase.controllerSet(-power);
        pros::delay(10);
    }
    stop();
}

//PID driving(backwards and forward)
double circumference = 3.1415 * 10.16;
void drive(double dis)
{
    leftBase.tarePosition();
    rightBase.tarePosition();
    left_PID.reset();
    right_PID.reset();

    double deg = (dis / circumference) * 360.0;

    left_PID.setTarget(deg);
    right_PID.setTarget(deg);

    while (!left_PID.isSettled() && !right_PID.isSettled())
    {
        double left_position = leftBase.getPosition();
        double right_position = rightBase.getPosition();

        double left_power = left_PID.step(left_position);
        double right_power = right_PID.step(right_position);

        leftBase.controllerSet(left_power);
        rightBase.controllerSet(right_power);
        pros::delay(10);
    }
    stop();
}

int intakeX = 30;
void getBallIntake(void *params)
{
    ball_in_the_middle(intakeX);
}

//no palka (1min auton)
void no_palka(int x)
{
    int startTime = pros::millis();
    if (x == 20)
    {
        pros::lcd::print(5, "Start time: %d\n", startTime);
        chassis.resetSensors();
        gyro1.reset();
        intake.move(127); //first flags
        drive(103);
        intakeX = -127;
        pros::Task(getBallIntake, NULL);
        drive(15);
        drive(-90);
        calib(false, 800);
        drive(16);
        TurnAngle(-90);
        shoot_twice();
        TurnAngle(-9);
        intake.move(-127);
        drive(110);
        calib(true, 900);
        drive(-15);
        pros::delay(300);
        drive(-98);
        intake.move(100);
        pros::delay(400);
        TurnAngle(90);
        intake.move(0);
        calib(false, 550);
        drive(12); //getting a ball from the top of a cap
        TurnAngle(-51);
        drive(37);
        intakeX = -127;
        pros::Task(getBallIntake, NULL);
        drive(12);
        drive(-20);
        pros::delay(100);
        drive(-27);
        TurnAngle(50);
        calib(false, 400);
        drive(106); //second pole with flags
        TurnAngle(-72);
        angleController.setTarget(0.0);
        angleController.waitUntilSettled();
        shoot.move(127);
        pros::delay(650);
        shoot.move(0);
        intake.move(-127);
        pros::delay(300);
        intake.move(0);
        TurnAngle(-6);
        angleController.setTarget(55.0);
        angleController.waitUntilSettled();
        shoot.move(127);
        pros::delay(700);
        shoot.move(0);
        intake.move(-127);
        leftBase.moveVoltage(8900);
        rightBase.moveVoltage(10000);
        pros::delay(1600);
        leftBase.moveVoltage(0);
        rightBase.moveVoltage(0);
        pros::delay(400);
        drive(-91);
        pros::delay(20);
        TurnAngle(90);
        intake.move(-127);
        drive(82);
        intake.move(-127);
        drive(12.5);
        drive(-10);
        pros::delay(700);
        angleController.setTarget(25.0);
        angleController.waitUntilSettled();
        intakeX = 127;
        pros::Task(getBallIntake, NULL);
        TurnAngle(-52);
        shoot.move(127);
        pros::delay(650);
        shoot.move(0);
        intake.move(-127);
        TurnAngle(46);
        intake.move(100);
        drive(40);
        TurnAngle(17);
        TurnAngle(-90);
        drive(50);
        calib(true, 600);
        pros::delay(100);
        drive(-128);
        TurnAngle(7);
        angleController.setTarget(55.0);
        angleController.waitUntilSettled();
        shoot.move(127);
        pros::delay(700);
        shoot.move(0);
        pros::delay(100);
        TurnAngle(-97);
        intake.move(127); //first flags
        drive(50);
        intake.move(-127);
        drive(20);
        drive(-45);
        pros::delay(500);
        intake.move(0);
        TurnAngle(105);
        angleController.setTarget(55.0);
        angleController.waitUntilSettled();
        shoot.move(127);
        pros::delay(700);
        shoot.move(0);
        intake.move(0);
        TurnAngle(-15);
        drive(-72);
        pros::delay(50);
        TurnAngle(90);
        pros::delay(50);
        calib(false, 500);
        drive(-57);
        stop();
        pros::lcd::print(6, "End time: %d\n", (pros::millis() - startTime));
    }

    else if (x == 15)
    {
        chassis.resetSensors();
        gyro1.reset();
        intake.move(127); //1 step
        drive(105);
        pros::Task(getBallIntake, NULL);
        drive(20);
        drive(-90);
        calib(false, 1000);
        drive(12);
        TurnAngle(-90);
        shoot_twice(); //2 step
        intake.move(-127);
        drive(80);
        TurnAngle(-30);
        drive(20);
        TurnAngle(25);
        drive(15);
        calib(true, 1000);
        stop();
        drive(-127);
        TurnAngle(90);
        calib(false, 500);
        drive(8);
        TurnAngle(-52);
        intake.move(0);
        chassis.resetSensors();
        drive(37);
        intake.move(-127);
        pros::delay(300);
        TurnAngle(11);
        shoot.move(127);
        pros::delay(650);
        shoot.move(0);
        TurnAngle(-20);
        //TurnAngle(-18);
        intake.move(-127);
        drive(23);
        drive(-20);
        stop();
        pros::delay(200);
        drive(7);
        intake.move(127);
        drive(50);
        drive(-78);
        TurnAngle(45);
        calib(false, 500);
        drive(117);
        TurnAngle(-90);
        calib(false, 600);
        drive(12);
        TurnAngle(15);
        angleController.setTarget(0.0);
        angleController.waitUntilSettled();
        shoot.move(127);
        pros::delay(650);
        shoot.move(0);
        leftBase.moveVoltage(-10000);
        pros::delay(100);
        leftBase.moveVoltage(0);
        drive(22);
        TurnAngle(90);
        drive(-117);
        calib(false, 500);
        drive(15);
        TurnAngle(-94);
        drive(-65);
        TurnAngle(-90);
        calib(true, 700);
        drive(-50);
        pros::delay(50);
        drive(-72);
        pros::delay(50);
        drive(-65);
        stop();
    }

    else if (x == 12)
    {
        chassis.resetSensors();
        gyro1.reset();
        intake.move(127); //1 step
        drive(105);
        pros::Task(getBallIntake, NULL);
        drive(20);
        drive(-90);
        calib(false, 1000);
        drive(12);
        TurnAngle(-90);
        shoot_twice(); //2 step
        intake.move(-127);
        drive(80);
        TurnAngle(-30);
        drive(20);
        TurnAngle(25);
        drive(15);
        calib(true, 1000);
        stop();
        drive(-180);
        TurnAngle(-90);
        calib(true, 1000);
        drive(-50);
        pros::delay(50);
        drive(-72);
        pros::delay(50);
        drive(-65);
        stop();
    }
    else if (x == 8)
    {
        angleController.setTarget(55.0);
        angleController.waitUntilSettled();
        shoot.move(127);
        pros::delay(650);
        shoot.move(0);
        drive(-55);
        TurnAngle(-90);
        calib(true, 600);
        drive(-50);
        pros::delay(50);
        drive(-72);
        pros::delay(50);
        drive(-65);
        stop();
    }
}

void pre_driving(){
        chassis.resetSensors();
        gyro1.reset();
        intake.move(127); //1 step
        drive(105);
        pros::Task(getBallIntake, NULL);
        drive(20);
        drive(-90);
        calib(false, 1000);
        drive(12);
        TurnAngle(-90);
        shoot_twice(); //2 step
        stop();
}