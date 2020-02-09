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
    Data data = altimeter->poll(data);  // use readFromSensors() -rachel
    long altitude = data.altimeterData.altitude; 
    //CHECK: Has the highest_alt variable been initialized to a value? If this is the
    //first time executing the descentDetected code, set the highest_alt variable to 
    //the first altitude reading. 
    if(!hasMax)
    {
        highest_alt = altitude;
        hasMax = true; //Setting the hasMax flag to true as the highest_alt variable has been initialized.  
    }
    if(altitude < highest_alt)
    {
        //Let's say here that if multiple data points have decreased in altitude in a row, then increment
        //isConsistent variable. The max value of of isConsistent needs to be refined through testing. 
        //Basically the variable is verifying that the launch vehicle is indeed descending after multiple
        //iterations.
        if(isConsistent < 10) // make these constants -rachel
        {
            isConsistent += 1; //incrementing the counter means altitude is decreasing 
        }
        else if(isConsistent == 10)
        {
            //After multiple iterations, the altimeter data has been consistently decreasing to
            //the point that the isConsistent variable has reached its threshold. 
            ret = true; //Descent has been detected
        }
    }
    else if(altitude > highest_alt)
    {
        isConsistent = 0; //The data shows that there has been an increase in altitude so reset the counter 
        highest_alt = altitude; 
    }

    // TODO: Look for false positive cases 
    //      (a) When the rocket is rotating rapidly 
    //      (b) Noisy altimeter data 
    //   -Find a way to determine descent with the IMU data --have to research this--
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