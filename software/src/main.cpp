#include <Arduino.h>

#include "Airbrake_State.hpp"
#include "LaunchVehicle.hpp"
#include "Airbrake.hpp"
#include "SdFat.h"
#include "MockHelper.hpp"

/*********************************************** Functions ***************************************/
bool manualSkipState(void);
void setup(void);
void loop(void);
/*************************************************************************************************/

/************************************************ Globals ****************************************/
LaunchVehicle vehicle;  // Makes decisions about the state of the vehicle based on sensor data
Airbrake airbrake;      // Actuates the air brake and interacts with air brake hardware
Airbrake_State state;   // Keeps track of current state
/*************************************************************************************************/

/**************************************************************************************************
 * One-time setup
 *************************************************************************************************/
void setup() 
{
    delay(4000);
    Serial.println("In setup"); 

    state = START;

    if (MANUAL_MODE)
    {
        Serial.println("MANUAL: Using mocked sensors");
        
        // Set up mock sensor with data file path on micro SD
        MockHelper mockHelper((char*)"loggylog.csv");
        mockHelper.init();

        // Mocked sensors
        MockImu imu(mockHelper);
        MockAltimeter altimeter(mockHelper);

        vehicle.init(&imu, &altimeter);
    }
    else
    {
        Serial.println("AUTOMATIC: Using real sensors");

        // Real sensors
        IMU imu;
        Altimeter altimeter;

        vehicle.init(&imu, &altimeter);
    }    
}
/**************************************************************************************************
 * State machine loop
 *************************************************************************************************/
void loop() 
{
    delay(STATE_DELAY);
    
    switch (state)
    {
        case START:

            Serial.println("State: START");

            Serial.println("Reading from sensors");

            Data data;
            data = vehicle.readFromSensors(data);

            Serial.println("read from sensors complete");

            if (vehicle.launchDetected())       // Check if launch has been detected 
            {
                state = LAUNCH_DETECTED;
            }


            break;
        
        case LAUNCH_DETECTED:

            // Consider waiting until here to power on motor

            Serial.println("State: LAUNCH_DETECTED");
            if (vehicle.motorBurnoutDetected()) // Check if motor burnout has been detected
            {
                state = BURNOUT_DETECTED;
            }

            break;

        case BURNOUT_DETECTED:

            Serial.println("State: BURNOUT_DETECTED");
            if (vehicle.daqThresholdMet())     // Check if data acquisition threshold has been met
            {
                state = DAQ_THRESHOLD_MET_ACTIVE_ADJUST;
            }

            break;
        
        case DAQ_THRESHOLD_MET_ACTIVE_ADJUST:

            Serial.println("State: DAQ_THRESHOLD_MET_ACTIVE_ADJUST");
            if (vehicle.descentDetected()) // Check for descent
            {
                state = DESCENT_DETECTED;
                break;
            }

            if (vehicle.isWithinImmediateDeploymentRange()) // Check for immediate deployment
            {
                airbrake.deployCompletely();        // Deploy air brake completely
                while (!vehicle.descentDetected()); // Wait until descent is detected
                state = DESCENT_DETECTED;           // Switch to descent detected state
                break;
            }

            // Otherwise, proceed with fine adjustment algorithm
            if (vehicle.isWithinPartialDeploymentRange() > 0) // Predicted apogee > target apogee
            {
                int percent_deployment = vehicle.calculatePercentDeployment(); // Calculate action
                airbrake.setAbsoluteDeployment(percent_deployment); // Deploy percent air brake 
            }

            break;

        case DESCENT_DETECTED:

            Serial.println("State: DESCENT_DETECTED");
            airbrake.retractCompletely(); // Retract to 0%
            state = TERMINATION;          // Terminate

            break;

        case TERMINATION:

            Serial.println("State: TERMINATION");
            while (true); // Infinite loop (state machine termination)

            break;

        default:

            state = DESCENT_DETECTED; // Should never be here. Retract to 0% and terminate

            break;
    }
}
/**************************************************************************************************
 * Handles option to skip states in manual mode
 *************************************************************************************************/
bool manualSkipState()
{
    bool ret = false;
    if (MANUAL_MODE)
    {
        Serial.println("Enter 'c' to skip state or 'w' to wait");
        while (Serial.available() == 0) 
        { 
            // Wait for serial
        }
        ret = (Serial.read() == 'c');
    }

    return ret;
}
