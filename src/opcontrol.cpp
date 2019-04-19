#include "main.h"
#include "config.h"
#include "Func.h"

using namespace okapi;
void opcontrol()
{
	rightBase1.setBrakeMode(AbstractMotor::brakeMode::hold);
	rightBase2.setBrakeMode(AbstractMotor::brakeMode::hold);
	leftBase1.setBrakeMode(AbstractMotor::brakeMode::hold);
	leftBase2.setBrakeMode(AbstractMotor::brakeMode::hold);
	angle.setBrakeMode(AbstractMotor::brakeMode::hold);
	intake.setBrakeMode(AbstractMotor::brakeMode::hold);
	chassis.resetSensors();
	int getBallIntakeDuration = 1000;
	bool grad = true;
	bool fast = false;
	//pre_driving();
	while (true)
	{
		if (controller.getDigital(ControllerDigital::A))
		{
			fast = !fast;
			pros::delay(300);
		}
		//base
		if (fast)
		{
			chassis.tank(controller.getAnalog(ControllerAnalog::leftY),
						 controller.getAnalog(ControllerAnalog::rightY));
			// leftBase2.moveVelocity(controller.getAnalog(ControllerAnalog::leftY));
			// leftBase1.moveVelocity(controller.getAnalog(ControllerAnalog::rightY));
		}
		if (!fast)
		{
			chassis.tank(controller.getAnalog(ControllerAnalog::leftY) / 1.2,
						 controller.getAnalog(ControllerAnalog::rightY) / 1.2);
		}

		//intake
		if (controller.getDigital(ControllerDigital::L1))
		{
			intake.move(-100);
		}
		else if (controller.getDigital(ControllerDigital::L2))
		{
			intake.move(100);
		}

		else
		{
			intake.move(0);
		}

		//puncher
		if (controller.getDigital(ControllerDigital::R1))
		{
			shoot.move(127);
		}
		else
		{
			shoot.move(0);
		}

		//angle control
		if (controller.getDigital(ControllerDigital::R2))
		{
			while (controller.getDigital(ControllerDigital::R2))
			{
				pros::delay(20);
			}
			angleController.setTarget(grad ? 55.0 : 0.0);
			grad = !grad;
		}

		//shoot twice
		if (controller.getDigital(ControllerDigital::up))
		{
			shoot_twice();
		}

		if (controller.getDigital(ControllerDigital::right))
		{
			no_palka(20);
		}

		printf("gyro = %f\n", gyro1.get() / 10);
		pros::lcd::print(0, "gyro: %f\n ", gyro1.get() / 10);
		pros::lcd::print(3, "light: %d\n", line.get_value());
		pros::delay(20);
	}
}
