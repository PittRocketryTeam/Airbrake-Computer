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
    // TODO: Implement

}

void Airbrake::retractCompletely()
{
    // TODO: Implement

}

int Airbrake::getDeploymentPercentage()
{
    return deployment_percentage;
}