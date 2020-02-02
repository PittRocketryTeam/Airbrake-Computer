#include "Airbrake.hpp"

Airbrake::Airbrake():
    deployment_percentage(0),
    motor(MOTOR_STEPS, M_DIR, M_STEP)
{

}

Airbrake::~Airbrake()
{

}

void Airbrake::init()
{
    motor.begin(RPM, MICROSTEPS);
}

void Airbrake::setAbsoluteDeployment(int percent)
{
    // TODO: Implement
    deployment_percentage = percent;

    // motor.move(MOTOR_STEPS * MICROSTEPS);
}

void Airbrake::deployCompletely()
{
    deployment_percentage = 100;
    setAbsoluteDeployment(100);
}

void Airbrake::retractCompletely()
{
    deployment_percentage = 0;
    setAbsoluteDeployment(0);
}

int Airbrake::getDeploymentPercentage()
{
    return deployment_percentage;
}