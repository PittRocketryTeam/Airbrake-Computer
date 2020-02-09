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

int LaunchVehicle::isWithinImmediateDeploymentRange()
{
    bool ret = -1;

    Data data = imu->poll(data);

    if (data.altimeterData.altitude >= IMMEDIATE_DEPLOYMENT_LOWER_BOUND)
    {
        ret = 1;
    }
    
    return ret;
}

int LaunchVehicle::isWithinPartialDeploymentRange()
{
    int ret = -1; // Bias toward no action

    float predicted_apogee = predictApogee(); // make this private-class scoped so deployment incrementation can use it -rachel

    if (predicted_apogee < PARTIAL_DEPLOYMENT_LOWER_BOUND)
    {
        ret = -1;   // Predicted apogee < target apogee (do nothing)
    }
    else if ((predicted_apogee >= PARTIAL_DEPLOYMENT_LOWER_BOUND) && 
             (predicted_apogee <= PARTIAL_DEPLOYMENT_UPPER_BOUND))
    {
        ret = 0;    // Predicted apogee = target apogee (do nothing)
    }
    else if (predicted_apogee > PARTIAL_DEPLOYMENT_UPPER_BOUND) 
    {
        ret = 1;    // Predicted apogee > target apogee (trigger deployment)
    }

    return ret;
}

int LaunchVehicle::calculatePercentDeployment()
{
    int percent_deployment = 0;

    float err = predictApogee() - TARGET_APOGEE;    // use private-scoped prediction -rachel
    if (err <= 0)   // flip this -rachel
    {
        return 0;
    }

    float weight = 0.02; // TODO TUNE VALUE // move to constants -rachel

    percent_deployment = (int)fmaxf(err * weight, 4) * 25; // should be fmin -matt/patrick
    
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