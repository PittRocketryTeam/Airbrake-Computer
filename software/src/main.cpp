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
LaunchVehicle vehicle;
Airbrake airbrake;
Airbrake_State state;
/*************************************************************************************************/

/**************************************************************************************************
 * One-time setup
 *************************************************************************************************/
void setup() 
{
    delay(2000);
    Serial.println("In setup"); 

    state = START;

    if (MANUAL_MODE)
    {
        Serial.println("MANUAL: Using mocked sensors");
        
        // Set up mock sensor with data file path on micro SD
        MockHelper mockHelper((char*)"data.txt");
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
    delay(100);
    
    switch (state)
    {
        case START:

            Serial.println("State: START");
            // if (manualSkipState())
            // {
            //     state = LAUNCH_DETECTED;
            //     break;
            // }

            if (vehicle.launchDetected())       // Check if launch has been detected 
            {
                state = LAUNCH_DETECTED;
                break;
            }

            break;
        
        case LAUNCH_DETECTED:

            Serial.println("State: LAUNCH_DETECTED");
            // if (manualSkipState())
            // {
            //     state = BURNOUT_DETECTED;
            //     break;
            // }

            if (vehicle.motorBurnoutDetected()) // Check if motor burnout has been detected
            {
                state = BURNOUT_DETECTED;
                break;
            }

            break;

        case BURNOUT_DETECTED:

            Serial.println("State: BURNOUT_DETECTED");
            // if (manualSkipState())
            // {
            //     state = DAQ_THRESHOLD_MET_ACTIVE_ADJUST;
            //     break;
            // }

            if (vehicle.daqThresholdMet())     // Check if data acquisition threshold has been met
            {
                state = DAQ_THRESHOLD_MET_ACTIVE_ADJUST;
                break;
            }

            break;
        
        case DAQ_THRESHOLD_MET_ACTIVE_ADJUST:

            Serial.println("State: DAQ_THRESHOLD_MET_ACTIVE_ADJUST");
            // if (manualSkipState())
            // {
            //     state = DESCENT_DETECTED;
            //     break;
            // }

            // Move to descent state if descent has been detected
            if (vehicle.descentDetected())
            {
                state = DESCENT_DETECTED;
                break;
            }

            // Check if vehicle is within range for immediate deployment
            if (vehicle.isWithinImmediateDeployment())
            {
                airbrake.deployCompletely();        // Deploy air brake completely
                while (!vehicle.descentDetected()); // Wait until descent is detected
                state = DESCENT_DETECTED;           // Switch to descent detected state
                break;
            }

            // Otherwise, proceed with fine adjustment algorithm
            if (vehicle.withinPartialDeploymentRange() > 0) // Predicted apogee > target apogee
            {
                int percent_deployment = vehicle.calculateDeploymentAction(); // Calculate action
                airbrake.setAbsoluteDeployment(percent_deployment); // Deploy percent air brake 
            }

            break;

        case DESCENT_DETECTED:

            Serial.println("State: DESCENT_DETECTED");
            // if (manualSkipState())
            // {
            //     state = TERMINATION;
            //     break;
            // }

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
