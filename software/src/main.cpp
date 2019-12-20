#include <Arduino.h>
#include "Airbrake_State.hpp"
#include "LaunchVehicle.hpp"
#include "Airbrake.hpp"
#include "IMU.hpp"
#include "Altimeter.hpp"
#include "MockImu.cpp"

// Testing flag; set to true when testing, false for automatic mode
#define MANUAL_MODE false

LaunchVehicle vehicle;
Airbrake airbrake;
Airbrake_State state;

void setup() 
{
    Serial.begin(9600);

    state = START;
    
    MockImu imu;
    Altimeter altimeter;
    vehicle.init(imu, altimeter);
}

void loop() 
{
    switch (state)
    {
        case START:

            Serial.println("State: START");
            
            if (MANUAL_MODE)
            {
                Serial.println("Enter 'c' to skip to LAUNCH_DETECTED state or 'w' to wait " 
                               "for launch to be detected");
                while (Serial.available() == 0) { }
                if (Serial.readString() == 'c') state = LAUNCH_DETECTED;
                else break;
            }

            if (vehicle.launchDetected())       // Check if launch has been detected 
            {
                state = LAUNCH_DETECTED;
            }

            break;
        
        case LAUNCH_DETECTED:

            Serial.println("State: LAUNCH_DETECTED");

            if (MANUAL_MODE)
            {
                Serial.println("Enter 'c' to skip to BURNOUT_DETECTED state or 'w' to wait " 
                               "for burnout to be detected");
                while (Serial.available() == 0) { }
                if (Serial.readString() == 'c') state = BURNOUT_DETECTED;
                else break;
            }

            if (vehicle.motorBurnoutDetected()) // Check if motor burnout has been detected
            {
                state = BURNOUT_DETECTED;
            }

            break;

        case BURNOUT_DETECTED:

            Serial.println("State: BURNOUT_DETECTED");

            if (MANUAL_MODE)
            {
                Serial.println("Enter 'c' to skip to DAQ_THRESHOLD_MET_ACTIVE_ADJUST state " 
                               "or 'w' to wait for data acquisition threshold to be met");
                while (Serial.available() == 0) { }
                if (Serial.readString() == 'c') state = DAQ_THRESHOLD_MET_ACTIVE_ADJUST;
                else break;
            }
            
            if (vehicle.daqThresholdMet())     // Check if data acquisition threshold has been met
            {
                state = DAQ_THRESHOLD_MET_ACTIVE_ADJUST;
            }

            break;
        
        case DAQ_THRESHOLD_MET_ACTIVE_ADJUST:

            Serial.println("State: DAQ_THRESHOLD_MET_ACTIVE_ADJUST");

            if (MANUAL_MODE)
            {
                Serial.println("Enter 'c' to skip to DESCENT_DETECTED state or 'w' to wait");
                while (Serial.available() == 0) { }
                if (Serial.readString() == 'c') state = DAQ_THRESHOLD_MET_ACTIVE_ADJUST;
                else break;
            }
            
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

            airbrake.retractCompletely(); // Retract to 0%
            state = TERMINATION;          // Terminate

            break;

        case TERMINATION:

            Serial.println("State: TERMINATION");

            while (true); // Busy wait
            
            break;

        default:

            // Should never be in this state. If so, retract to 0% and terminate to fail safely
            state = DESCENT_DETECTED;

            break;
    }
}
