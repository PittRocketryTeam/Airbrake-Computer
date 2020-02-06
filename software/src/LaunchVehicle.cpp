#include "LaunchVehicle.hpp"
#include <cmath>// std::abs

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

bool LaunchVehicle::onPad()
{
    //must fill in detection
    return true;
}

bool LaunchVehicle::launchDetected()
{
    bool ret = false;
    Data data;
    uint8_t accelCounter = 0, margError = 1.5;//count for continuous acceleartion

    if(VERBOSE) {
        data = readFromSensors(data);
        Serial.printf("Acceleration: %f", data.imuData.acceleration_y);
    }

    //typical launch acceleration from our motor is -39.93. Ocurrs at 309 in loggylog.csv from december (col H is acceleration, col D is altitude)
        //if acceleration constant and over around 35m/s^2 for a short period of time (5 cycles), then proceed
    //after accel, look at altitude. Keep a mean, if new data is over mean by a certain amount == launched
        //maybe look to detect the initial subbtle up and down of the data (best option?) -- best for everything else
        //maybe you keep track of altitude during accel, see the big jump while checking for conintuity there? -- best for air brake
    for(data = readFromSensors(data); data.altimeterData.altitude < 100.00; data = readFromSensors(data)){//while under 100 meters -- 100 meters is the fail safe, if haven't detect launch by now, we're certainly lanuching
        if((std::abs(data.imuData.acceleration_y) > 38.50 || std::abs(data.imuData.acceleration_y) + margError > 38.50) && accelCounter < 5)
        {
            accelCounter++;
        }
        else if(std::abs(data.imuData.acceleration_y) + margError < 38.50)//acceleration was just a fluke, and not the constant acceleration the motor would provide
        {
            accelCounter = 0;
        }
        if(accelCounter >= 5)
        {
            if(data.altimeterData.altitude >= 30.00)
            {
                if(VERBOSE) { Serial.println("Launch Detected"); }
                return true;
            }
        }
    }

    if(VERBOSE) { Serial.println("Launch Detected"); }

    return true;//assumes if the rocket is above 100m high, that it is launching. If it isn't launching, it'll just stay in the loop
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

    float predicted_apogee = predictApogee();

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