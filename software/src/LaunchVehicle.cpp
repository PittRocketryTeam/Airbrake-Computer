#include "LaunchVehicle.hpp"
#include <cmath>// std::abs

LaunchVehicle::LaunchVehicle() :
    RTC_set_successfully(false),
    altitude_of_burnout(0)
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

    // Initialize RTC
    setSyncProvider(getTeensy3Time);
    delay(100);
    RTC_set_successfully = (timeStatus() == timeSet);

    if (VERBOSE) { Serial.println("Vehicle init complete"); }
}

bool LaunchVehicle::onPad()
{
    //must fill in detection
    return true;
}

bool LaunchVehicle::launchDetected()
{
    Data data;
    uint8_t accelCounter = 0, margError = 1.5;//count for continuous acceleartion

    //typical launch acceleration from our motor is -39.93. Ocurrs at 309 in loggylog.csv from december (col H is acceleration, col D is altitude)
        //if acceleration constant and over around 35m/s^2 for a short period of time (5 cycles), then proceed
    //after accel, look at altitude. Keep a mean, if new data is over mean by a certain amount == launched
        //maybe look to detect the initial subbtle up and down of the data (best option?) -- best for everything else
        //maybe you keep track of altitude during accel, see the big jump while checking for conintuity there? -- best for air brake
    //for(data = readFromSensors(data); data.altimeterData.altitude < 100.00; data = readFromSensors(data))//while under 100 meters -- 100 meters is the fail safe, if haven't detect launch by now, we're certainly lanuching
    data = readFromSensors(data);
    if(data.altimeterData.altitude < 100.00)
    {
        if(VERBOSE) { Serial.printf("%d, Accel: %.5f, Alt: %.5f, accelCounter: %d\n", data.timestamp, data.imuData.acceleration_y, data.altimeterData.altitude, accelCounter); }
        
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
        
        return false;//if accelCounter isn't at 5 and rocket isn't above 30m, launch has not been detected
    }
    else//if the rocket is above 100m, assume it's launched already
    {
        if(VERBOSE) { Serial.println("Launch Detected at 100m"); }
        return true;
    }
    
}

bool LaunchVehicle::motorBurnoutDetected()
{
    bool ret = false;

    // Three checks for motor burnout to be detected: 
    // (1) A certain amount of time has passed (burn time of motor), AND
    // (2) Altitude is greater than expected motor burnout altitude, AND
    // (3) Vehicle is no longer accelerating up/

    // check for decrease in acceleration 
    Data before = readFromSensors();
    delay(50);
    Data after = readFromSensors();
    bool criteria_3 = (before.imuData.acceleration_z < after.imuData.acceleration_z);

    ret = criteria_3;
        
    if (ret)
    {
        Data data = readFromSensors();
        altitude_of_burnout = data.altimeterData.altitude;
    }

    return ret;
}

int LaunchVehicle::calculatePercentDeployment()
{
    int percent_deployment = 0;

    // TODO: Implement
    
    return percent_deployment;
}

float LaunchVehicle::predictApogee()
{
    float predicted_apogee = 0.0;
    
    // Find coefficients
    std::vector<float> coeffs;
    std::vector<float> timestamps_floats(timestamps.begin(), timestamps.end());

    polyFit(timestamps_floats, altitudes, coeffs);

    // Find global maximum 
    predicted_apogee = findGlobalMax(coeffs);

    return predicted_apogee;
}

bool LaunchVehicle::descentDetected()
{
    bool ret = false;

    // TODO: Implement

    return ret;
}

bool LaunchVehicle::daqThresholdMet()
{
    bool ret = false;

    // Collect data points for use in predictApogee()
    Data data = readFromSensors();
    timestamps.push_back(data.timestamp);
    altitudes.push_back(data.altimeterData.altitude);

    // Number of data points read since burnout
    int points = timestamps.size();

    ret = (meetsDaqDataPointThreshold(points) 
           && meetsDaqHeightThreshold(data.altimeterData.altitude));

    return ret;
}

int LaunchVehicle::isWithinImmediateDeploymentRange()
{
    bool ret = -1;

    Data data = readFromSensors();

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

Data LaunchVehicle::readFromSensors()
{
    Data data;

    if (MANUAL_MODE)
    {
        data = altimeter->poll(data);
    }
    else
    {
        data = altimeter->poll(data);
        data = imu->poll(data);
    }
    
    return data;
}

bool LaunchVehicle::meetsDaqHeightThreshold(float current_altitude)
{
    bool ret = false;

    uint64_t diff = current_altitude - altitude_of_burnout;
    ret = (diff >= DAQ_THRESHOLD_ALTITUDE);

    return ret;
}

bool LaunchVehicle::meetsDaqDataPointThreshold(int points_read_since_burnout)
{
    bool ret = false;
    ret = (points_read_since_burnout >= DAQ_THRESHOLD_DATA_POINTS);
    return ret;
}

void LaunchVehicle::polyFit(std::vector<float> &x, std::vector<float> &y, std::vector<float> &coeffs)
{
    if (x.size() != y.size())
    {
        if (VERBOSE) { Serial.printf("LaunchVehicle::polyFit() - vector sizes do not match\n"); }
        return;
    }

    if ((x.size() == 0) || (y.size() == 0))
    {
        if (VERBOSE) { Serial.printf("LaunchVehicle::polyFit() - one or more vector has a size of 0\n"); }
        return;
    }

    int N = x.size(); // Number of data points
    int n = 2;        // 2nd degree polynomial
    int np1 = n + 1;
    int np2 = n + 2;
    int tnp1 = (2 * n) + 1;

    float tmp;
    std::vector<float> X(tnp1);
    for (int i = 0; i < tnp1; ++i) 
    {
        X[i] = 0;
        for (int j = 0; j < N; ++j)
        {
            X[i] += (float)pow(x.at(j), i);
        }
    }

    std::vector<float> a(np1); // a = vector to store final coefficients

    // B = normal augmented matrix that stores the equations
    std::vector<std::vector<float> > B(np1, std::vector<float> (np2, 0));

    for (int i = 0; i <= n; ++i) 
    {
        for (int j = 0; j <= n; ++j) 
        {
            B[i][j] = X[i + j];
        }
    }

    std::vector<float> Y(np1); // Y = vector to store values of sigma(xi^n * yi)
    for (int i = 0; i < np1; ++i) 
    {
        Y[i] = (float)0;
        for (int j = 0; j < N; ++j) 
        {
            Y[i] += (float)pow(x[j], i)*y[j];
        }
    }

    for (int i = 0; i <= n; ++i)  // Load values of Y as last column of B
    {
        B[i][np1] = Y[i];
    }

    n += 1;
    int nm1 = n-1;

    for (int i = 0; i < n; ++i)  // Pivotisation of the B matrix
    {
        for (int k = i+1; k < n; ++k) 
        {
            if (B[i][i] < B[k][i]) 
            {
                for (int j = 0; j <= n; ++j) 
                {
                    tmp = B[i][j];
                    B[i][j] = B[k][j];
                    B[k][j] = tmp;
                }
            }
        }  
    }

    // Performs the Gaussian elimination
    for (int i=0; i<nm1; ++i) 
    {
        for (int k =i+1; k<n; ++k) 
        {
            float t = B[k][i] / B[i][i];
            for (int j=0; j<=n; ++j) 
            {
                B[k][j] -= t*B[i][j];  // Make all elements below the pivot equals to zero or eliminate
            }
        }
    }
    // Back substitution 
    for (int i=nm1; i >= 0; --i) 
    {
        a[i] = B[i][n];                   // Set the variable as the rhs of last equation
        for (int j = 0; j<n; ++j)
        {
            if (j != i)
            {
                a[i] -= B[i][j] * a[j];       // Subtract all lhs values except the target coefficient.
            }
        }
        a[i] /= B[i][i];                  // Divide rhs by coefficient of variable being calculated.
    }

    coeffs.resize(a.size());

    for (size_t i = 0; i < a.size(); ++i) 
    {
        coeffs.push_back(a[i]);
    }
}

float LaunchVehicle::findGlobalMax(std::vector<float> &coeffs)
{
    float global_max = 0.0;

    // y = c + b*x + c*x^2
    float c = coeffs.at(0), b = coeffs.at(1), a = coeffs.at(2);
    
    // If a > 0, parabola opens up
    float global_max_x = -b / (2 * a);

    global_max = c + (b * global_max_x) + (c * global_max_x * global_max_x);

    return global_max;
}

static time_t LaunchVehicle::getTeensy3Time()
{
    return Teensy3Clock.get();
}
