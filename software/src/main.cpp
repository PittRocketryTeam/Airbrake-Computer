#include <Arduino.h>

#include "Airbrake_State.hpp"

#include "LaunchVehicle.hpp"
#include "Airbrake.hpp"
#include "Logger.hpp"
#include "Timer.hpp"

/*********************************************** Functions ***************************************/
bool manualSkipState(void);
void setup(void);
void loop(void);
/*************************************************************************************************/

/************************************************ Globals ****************************************/
LaunchVehicle vehicle;  // Makes decisions about the state of the vehicle based on sensor data
Airbrake airbrake;      // Actuates the air brake and interacts with air brake hardware
Airbrake_State state;   // Keeps track of current state in FSM
Logger logger;          // Performs data and event logging
Timer log_flush;
/*************************************************************************************************/

/**************************************************************************************************
 * One-time setup
 *************************************************************************************************/
void setup() 
{
    delay(4000);

    vehicle.init(&logger); 

    airbrake.init();

    // Logger inialization
    logger.init();
    log_flush.setInterval(1000);

    state = START;
    logger.logEvent((char*)"State: START");
}
/**************************************************************************************************
 * State machine loop
 *************************************************************************************************/
void loop() 
{
    delay(STATE_DELAY);

    if (log_flush.check())
    {
        logger.flush();
    }
        
    switch (state)
    {
        case START:

            if (VERBOSE) { Serial.println("State: START"); }

            if (vehicle.launchDetected())       // Check if launch has been detected 
            {
                logger.logEvent((char*)"State: LAUNCH_DETECTED");
                state = LAUNCH_DETECTED;
            }

            break;
        
        case LAUNCH_DETECTED:

            if (VERBOSE) { Serial.println("State: LAUNCH_DETECTED"); }

            if (vehicle.motorBurnoutDetected()) // Check if motor burnout has been detected
            {
                logger.logEvent((char*)"State: BURNOUT_DETECTED");
                state = BURNOUT_DETECTED;
            }

            break;

        case BURNOUT_DETECTED:

            if (VERBOSE) { Serial.println("State: BURNOUT_DETECTED"); }

            if (vehicle.daqThresholdMet())     // Check if data acquisition threshold has been met
            {
                logger.logEvent((char*)"State: DAQ_THRESHOLD_MET_ACTIVE_ADJUST");
                state = DAQ_THRESHOLD_MET_ACTIVE_ADJUST;
            }

            break;
        
        case DAQ_THRESHOLD_MET_ACTIVE_ADJUST:

            if (VERBOSE) { Serial.println("State: DAQ_THRESHOLD_MET_ACTIVE_ADJUST"); } 

            if (vehicle.descentDetected()) // Check for descent
            {
                logger.logEvent((char*)"State: DESCENT_DETECTED");
                state = DESCENT_DETECTED;
                break;
            }

            if (vehicle.isWithinImmediateDeploymentRange() > 0) // Check for immediate deployment
            {
                airbrake.deployCompletely();  // Deploy air brake completely
                while (!vehicle.descentDetected())
                {   
                    // Wait until descent is detected
                } 
                state = DESCENT_DETECTED;     // Switch to descent detected state
                logger.logEvent((char*)"State: DESCENT_DETECTED");
                break;
            }

            // Otherwise, proceed with fine adjustment algorithm
            if (vehicle.isWithinPartialDeploymentRange() > 0) // Check if predicted apogee > target apogee
            {
                int percent_deployment = vehicle.calculatePercentDeployment(); // Calculate action
                airbrake.setAbsoluteDeployment(percent_deployment);            // Deploy percent air brake 
                break;
            }

            break;

        case DESCENT_DETECTED:

            if (VERBOSE) { Serial.println("State: DESCENT_DETECTED"); }

            airbrake.retractCompletely(); // Retract to 0%
            state = TERMINATION;          // Terminate
            logger.logEvent((char*)"State: TERMINATION");

            break;

        case TERMINATION:

            if (VERBOSE) { Serial.println("State: TERMINATION"); }
            
            while (true)
            {
                // Infinite loop (state machine termination)
            } 

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
