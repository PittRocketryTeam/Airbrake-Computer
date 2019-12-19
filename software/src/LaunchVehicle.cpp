#include "LaunchVehicle.hpp"

LaunchVehicle::LaunchVehicle()
{

}

LaunchVehicle::~LaunchVehicle()
{

}

bool LaunchVehicle::launchDetected()
{
    // TODO: Implement

    return false;
}

bool LaunchVehicle::motorBurnoutDetected()
{
    // TODO: Implement

    return false;
}

bool LaunchVehicle::daqThresholdMet()
{
    // TODO: Implement

    return false;
}

bool LaunchVehicle::isWithinImmediateDeployment()
{
    // TODO: Implement

    return false;
}

bool LaunchVehicle::descentDetected()
{
    // TODO: Implement

    return false;
}

long LaunchVehicle::predictApogee()
{
    // TODO: Implement

    return 0.0;
}

int LaunchVehicle::withinPartialDeploymentRange()
{
    float predicted_apogee = predictApogee();

    if (predicted_apogee < PARTIAL_DEPLOYMENT_LOWER_BOUND)
        return -1;
    else if (predicted_apogee > PARTIAL_DEPLOYMENT_UPPER_BOUND)
        return 1;

    return 0;
}

int LaunchVehicle::calculateDeploymentAction()
{
    // TODO: Implement
    
    return 0;
}