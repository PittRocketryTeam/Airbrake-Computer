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
    Serial.println("inited airbrake");
    motor.begin(RPM, MICROSTEPS);
}

void Airbrake::setAbsoluteDeployment(int percent)
{
    Serial.println("running backward");
    // TODO: Implement
    deployment_percentage = percent;

    // Negative motor steps yields CCW when looking at motor
    // Positive motor steps yields CW when looking at motor

    motor.move(MOTOR_STEPS * MICROSTEPS * (percent/100.00));
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