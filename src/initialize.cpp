#include "main.h"
#include "config.h"

using namespace pros;

void initialize()
{
	printf("init\n");
    pros::lcd::initialize();
}

void disabled() {}

void competition_initialize() {}
