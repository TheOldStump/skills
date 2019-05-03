#include "main.h"
#include "config.h"
#include "Func.h"

using namespace okapi;
void opcontrol()
{
	double ss;
	rightBase1.setBrakeMode(AbstractMotor::brakeMode::hold);
	rightBase2.setBrakeMode(AbstractMotor::brakeMode::hold);
	leftBase1.setBrakeMode(AbstractMotor::brakeMode::hold);
	leftBase2.setBrakeMode(AbstractMotor::brakeMode::hold);
	angle.setBrakeMode(AbstractMotor::brakeMode::hold);
	intake.setBrakeMode(AbstractMotor::brakeMode::hold);
	ernur.setBrakeMode(AbstractMotor::brakeMode::hold);
	chassis.resetSensors();
	int getBallIntakeDuration = 1000;
	bool grad = true;
	bool fast = false;
	bool pre_drive = true;
	bool palka = true;
	bool rumbled = false;
	int startTime = pros::millis();
	bool gyro_0 = false;

	//otvrat();
	while (true)
	{
		if (controller.getDigital(ControllerDigital::A))
		{
			fast = !fast;
			pros::delay(300);
		}
		//base
		if (!fast)
		{

			chassis.tank(controller.getAnalog(ControllerAnalog::leftY),
						 controller.getAnalog(ControllerAnalog::rightY));
			// leftBase2.moveVelocity(controller.getAnalog(ControllerAnalog::leftY) * 200.0);
			// leftBase1.moveVelocity(controller.getAnalog(ControllerAnalog::leftY) * 200.0);
			// rightBase2.moveVelocity(controller.getAnalog(ControllerAnalog::rightY) * 200.0);
			// rightBase1.moveVelocity(controller.getAnalog(ControllerAnalog::rightY) * 200.0);
		}
		if (fast)
		{
			chassis.tank(controller.getAnalog(ControllerAnalog::leftY) / 1.2,
						 controller.getAnalog(ControllerAnalog::rightY) / 1.2);
			// leftBase2.moveVelocity(controller.getAnalog(ControllerAnalog::leftY) * 160.0);
			// leftBase1.moveVelocity(controller.getAnalog(ControllerAnalog::leftY) * 160.0);
			// rightBase2.moveVelocity(controller.getAnalog(ControllerAnalog::rightY) * 160.0);
			// rightBase1.moveVelocity(controller.getAnalog(ControllerAnalog::rightY) * 160.0);
		}

		//intake
		if (controller.getDigital(ControllerDigital::L1))
		{

			intake.move(-100);
		}
		else if (controller.getDigital(ControllerDigital::L2))
		{
			//ernurController.setTarget(0.0);
			intake.move(127);
		}

		else
		{
			intake.move(0);
		}

		//puncher
		if (controller.getDigital(ControllerDigital::R1))
		{
			//ernurController.setTarget(100.0);
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
			angleController.setTarget(grad ? 58.0 : 0.0);
			grad = !grad;
		}

		//shoot twice
		if (controller.getDigital(ControllerDigital::up))
		{
			//Ernur(1);
			shoot_twice();
		}

		// if (controller.getDigital(ControllerDigital::right))
		// {
		// 	Ernur(2);
		// 	//no_palka(20);
		// }

		// if (controller.getDigital(ControllerDigital::left))
		// {
		// 	//palka_2();
		// 	Ernur(3);
		// 	//salam();
		//  }
		// if (controller.getDigital(ControllerDigital::down))
		// {
		// 	Ernur(0);
		// 	//ss = sonic.get() / 10;
		// }
		// if (controller.getDigital(ControllerDigital::B))
		// {
		// 	no_palka(8);
		// }

		// if (controller.getDigital(ControllerDigital::X))
		// {
		// 	while (controller.getDigital(ControllerDigital::X))
		// 	{
		// 		pros::delay(20);
		// 	}
		// 	ernurController.setTarget(palka ? 100.0 : 0.0);
		// 	palka = !palka;
		// }

		//printf("gyro = %f\n", gyro1.get() / 10);
		//
		//pros::lcd::print(8, std::to_string(sonic.get() / 10));
		pros::lcd::print(0, "gyro: %f\n ", gyro1.get() / 10);
		pros::lcd::print(3, "light: %d\n", line.get_value());
		pros::lcd::print(4, "sonic: %f\n", sonic.get() / 10);
		pros::lcd::print(5, "Ernur: %f\n", ernur.getPosition());
		pros::delay(20);
	}
}