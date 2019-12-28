#include "LaunchVehicle.hpp"

LaunchVehicle::LaunchVehicle()
{

}

LaunchVehicle::~LaunchVehicle()
{

}

void LaunchVehicle::init(AbstractImu* i, AbstractAltimeter* a)
{
    // imu = i;
    // altimeter = a;

    // altimeter.init();
    // altimeter.setBaselinePressure();

    // imu->init();
}

// bool LaunchVehicle::launchDetected()
// {
//     // TODO: Implement

//     return false;
// }

// bool LaunchVehicle::motorBurnoutDetected()
// {
//     // TODO: Implement

//     return false;
// }

// bool LaunchVehicle::daqThresholdMet()
// {
//     // TODO: Implement

//     return false;
// }

// bool LaunchVehicle::isWithinImmediateDeployment()
// {
//     bool ret = false;

//     // Data data = imu->poll(data);
//     // float current_altitude = data.altimeterData.altitude;

//     // if ((current_altitude >= IMMEDIATE_DEPLOYMENT_LOWER_BOUND) && 
//     //     (current_altitude <= IMMEDIATE_DEPLOYMENT_UPPER_BOUND))
//     // {
//     //     ret = true;
//     // }
    
//     return ret;
// }

// bool LaunchVehicle::descentDetected()
// {
//     // TODO: Implement

//     return false;
// }

// long LaunchVehicle::predictApogee()
// {
//     // TODO: Implement

//     return 0.0;
// }

// int LaunchVehicle::withinPartialDeploymentRange()
// {
//     int ret = -1; // Bias toward no action

//     // float predicted_apogee = predictApogee();

//     // if (predicted_apogee < PARTIAL_DEPLOYMENT_LOWER_BOUND)
//     // {
//     //     ret = -1;
//     // }
//     // else if (predicted_apogee > PARTIAL_DEPLOYMENT_UPPER_BOUND) 
//     // {
//     //     ret = 1;
//     // }
//     // else if ((predicted_apogee >= PARTIAL_DEPLOYMENT_LOWER_BOUND) && 
//     //          (predicted_apogee <= PARTIAL_DEPLOYMENT_UPPER_BOUND))
//     // {
//     //     ret = 0;
//     // }

//     return ret;
// }

// int LaunchVehicle::calculateDeploymentAction()
// {
//     // TODO: Implement
    
//     return 0;
// }