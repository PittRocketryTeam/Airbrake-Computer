#include "Airbrake.hpp"

Airbrake::Airbrake():
    deployment_percentage(0),
    motor(STEPS_FOR_100_PERCENT, M_DIR, M_STEP)
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
    float difference = (float)percent - (float)deployment_percentage;

    Serial.printf("Deployment percentage: %lf\n", deployment_percentage);
    Serial.printf("Commanded percentage: %lf\n", percent);

    Serial.printf("Difference: %lf\n", difference);

    deployment_percentage = difference;

    float steps = -(STEPS_FOR_100_PERCENT * MICROSTEPS * (float)(difference/100.0));

    Serial.printf("Steps: %f\n", steps);

    motor.move(steps);
}

void Airbrake::deployCompletely()
{
    setAbsoluteDeployment(100);
}

void Airbrake::retractCompletely()
{
    setAbsoluteDeployment(0);
}

int Airbrake::getDeploymentPercentage()
{
    return deployment_percentage;
}