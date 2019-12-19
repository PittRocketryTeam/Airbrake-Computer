#include <Arduino.h>
#include "Airbrake_State.hpp"
#include "LaunchVehicle.hpp"
#include "Airbrake.hpp"


LaunchVehicle vehicle;
Airbrake airbrake;
Airbrake_State state;

void setup() 
{
    state = START;
    
    // TODO: Perform any one-time initialization here


}

void loop() 
{
    switch (state)
    {
        case START:
            
            if (vehicle.launchDetected())       // Check if launch has been detected 
            {
                state = LAUNCH_DETECTED;
            }

            break;
        
        case LAUNCH_DETECTED:

            if (vehicle.motorBurnoutDetected()) // Check if motor burnout has been detected
            {
                state = BURNOUT_DETECTED;
            }

            break;

        case BURNOUT_DETECTED:
            
            if (vehicle.daqThresholdMet())     // Check if data acquisition threshold has been met
            {
                state = DAQ_THRESHOLD_MET_ACTIVE_ADJUST;
            }

            break;
        
        case DAQ_THRESHOLD_MET_ACTIVE_ADJUST:
            
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

            airbrake.retractCompletely(); // Retract to 0%
            state = TERMINATION;          // Terminate

            break;

        case TERMINATION:

            while (true); // Busy wait
            
            break;

        default:

            // Should never be in this state. If so, retract to 0% and terminate to fail safely
            state = DESCENT_DETECTED;

            break;
    }
}
