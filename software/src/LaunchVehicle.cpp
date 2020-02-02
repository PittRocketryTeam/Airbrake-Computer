#include "LaunchVehicle.hpp"

LaunchVehicle::LaunchVehicle() :
    altitude_of_burnout(0),
    data_points_read_at_burnout(0)
{

}

LaunchVehicle::~LaunchVehicle()
{

}

void LaunchVehicle::init(AbstractImu* i, AbstractAltimeter* a)
{
    imu = i;
    altimeter = a;

    altimeter->init();
    altimeter->setBaselinePressure();
    
    imu->init();
    delay(1000);

    if (VERBOSE) { Serial.println("Vehicle init complete"); }
}

bool LaunchVehicle::launchDetected()
{
    bool ret = false;

    // TODO: Implement

    Data data;
    data = imu->poll(data);
    Serial.println(data.timestamp);

    return ret;
}

bool LaunchVehicle::motorBurnoutDetected()
{
    bool ret = false;

    // TODO: Implement

    return ret;
}

bool LaunchVehicle::daqThresholdMet()
{
    bool ret = false;

    // TODO: Implement

    return ret;
}

bool LaunchVehicle::isWithinImmediateDeploymentRange()
{
    bool ret = false;

    // TODO: Implement

    // Data data = imu->poll(data);
    // float current_altitude = data.altimeterData.altitude;

    // if ((current_altitude >= IMMEDIATE_DEPLOYMENT_LOWER_BOUND) && 
    //     (current_altitude <= IMMEDIATE_DEPLOYMENT_UPPER_BOUND))
    // {
    //     ret = true;
    // }
    
    return ret;
}

bool LaunchVehicle::descentDetected()
{
    bool ret = false;

    // TODO: Implement

    return ret;
}

long LaunchVehicle::predictApogee()
{
    long predicted_apogee = 0.0;
    
    // TODO: Implement

    return predicted_apogee;
}

int LaunchVehicle::isWithinPartialDeploymentRange()
{
    int ret = -1; // Bias toward no action

    // TODO: Implement 

    // float predicted_apogee = predictApogee();

    // if (predicted_apogee < PARTIAL_DEPLOYMENT_LOWER_BOUND)
    // {
    //     // Predicted is less than target apogee (do nothing)
    //     ret = -1;
    // }
    // else if (predicted_apogee > PARTIAL_DEPLOYMENT_UPPER_BOUND) 
    // {
    //     // Predicted apogee is greater than target apogee 
    //     ret = 1;
    // }
    // else if ((predicted_apogee >= PARTIAL_DEPLOYMENT_LOWER_BOUND) && 
    //          (predicted_apogee <= PARTIAL_DEPLOYMENT_UPPER_BOUND))
    // {
    //     // Predicted apogee close enough to target apogee
    //     ret = 0;
    // }

    return ret;
}

int LaunchVehicle::calculatePercentDeployment()
{
    int percent_deployment = 0;

    // TODO: Implement
    
    return percent_deployment;
}

Data LaunchVehicle::readFromSensors(Data data)
{
    data = altimeter->poll(data);

    data = imu->poll(data);

    return data;
}

bool LaunchVehicle::meetsDaqHeightThreshold()
{
    bool ret = false;

    Data data;
    data = altimeter->poll(data);

    uint64_t diff = data.altimeterData.altitude - altitude_of_burnout;

    ret = (diff >= DAQ_THRESHOLD_ALTITUDE);

    return ret;
}

bool LaunchVehicle::meetsDaqDataPointThreshold()
{
    bool ret = false;

    uint64_t diff = altimeter->getNumDataPoints() - data_points_read_at_burnout;

    ret = (diff >= 50.0);

    return ret;
}