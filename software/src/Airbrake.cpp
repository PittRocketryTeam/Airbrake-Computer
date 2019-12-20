#include "Airbrake.hpp"

Airbrake::Airbrake():
    deployment_percentage(0)
{

}

Airbrake::~Airbrake()
{

}

void Airbrake::setAbsoluteDeployment(int percent)
{
    // TODO: Implement

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