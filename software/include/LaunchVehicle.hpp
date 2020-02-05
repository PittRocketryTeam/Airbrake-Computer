#ifndef __LaunchVehicle_HPP__
#define __LaunchVehicle_HPP__

#include "constants.hpp"

#include "AbstractImu.hpp"
#include "AbstractAltimeter.hpp"

#include "IMU.hpp"
#include "Altimeter.hpp"

#include "MockImu.hpp"
#include "MockAltimeter.hpp"

class LaunchVehicle
{
    public:

        LaunchVehicle();
        ~LaunchVehicle();

        /************************************************ Globals ****************************************/
        long highest_alt;       // Keeps track of the highest recorded altitude
        bool hasMax;            // A flag that indicates that highest_alt been initialized
        int isConsistent;       // A counter that will increment each time a descent has been detected
        /*************************************************************************************************/
        
        /******************************************************************************************
         * Initialize vehicle and sensors. Accepts an IMU and Altimeter objects so these sensors
         * can be mocked.
         * 
         * @param AbstractImu imu object (or mock)
         * @param AbstractAltimeter altimeter object (or mock)
         *****************************************************************************************/
        void init(AbstractImu* i, AbstractAltimeter* a);
        
        /******************************************************************************************
         * SA-1: Launch Detection Sub-Algorithm
         * 
         * Author(s): Matt Wildermuth & Daniel Stumpp
         * 
         * Determines whether or not launch has been detected. A launch is defined as an event in 
         * which the vehicle's motor ignites and the vehicle leaves the launch rail at a speed of 
         * at least 52 feet per second.
         * 
         * @return true if launch has been detected, false otherwise.
         *****************************************************************************************/
        bool launchDetected();
        
        /******************************************************************************************
         * SA-2: Motor Burnout Detection Sub-Algorithm
         * 
         * Author(s): TBD
         * 
         * Determines whether or not motor burnout has completed. Motor burnout is the moment after
         * which the vehicle's motor is no longer firing. 
         * 
         * @return true if motor burnout has been detected, false otherwise.
         *****************************************************************************************/
        bool motorBurnoutDetected();

        /******************************************************************************************
         * SA-3: Deployment Incrementation Sub-Algorithm (Calculate Percent Deployment)
         * 
         * Author(s): Patrick Roche
         *
         * Determines how much the air brake should deploy as an absolute percentage. A value of
         * 100 indicates that 100% of the air brake should be deployed, whereas a value of 0%
         * indicates that none of the air brake should be deployed. This value should be within
         * 0 to 100 (inclusive).
         * 
         * @return percent absolutely air brake deployment (0 to 100 inclusive).
         *****************************************************************************************/
        int calculatePercentDeployment();

        /******************************************************************************************
         * SA-4: Apogee Prediction Sub-Algorithm
         * 
         * Author(s): Fernando Tabares
         * 
         * Predicts the current apogee based on readings from the altimeter and IMU. 
         * 
         * @return the current predicted apogee
         *****************************************************************************************/
        long predictApogee();

        /******************************************************************************************
         * SA-5: Descent Detection Sub-Algorithm
         * 
         * Author(s): Sona Padinjarekutt
         * 
         * Determines whether or not the vehicle has achieved apogee and has started to descend. 
         * 
         * @return true if the vehicle is descending, false otherwise.
         *****************************************************************************************/
        bool descentDetected();

        /******************************************************************************************
         * Data Acquisition Threshold Determination (Based on DAQ I-6 and I-7 parameters)
         * 
         * Determines whether or not enough data has been collected to begin using the data for 
         * apogee prediction. Without enough data, apogee prediction will be inaccurate and should
         * not be used to control the air brake. "Enough data" is a soft measure which is 
         * determined through experimentation and controlled using parameters I-6 and I-7.
         * 
         * @return true if the data acquisition threshold has been met, false otherwise.
         *****************************************************************************************/
        bool daqThresholdMet();

        /******************************************************************************************
         * Within Range for Immediate Deployment
         * 
         * This function reads the current altitude and uses this, in conjuction with the 
         * IMMEDIATE_DEPLOYMENT_RANGE parameter, to determine whether the air brake should be 
         * deployed immediately to avoid overshooting target apogee +/- IMMEDIATE_DEPLOYMENT_RANGE.
         * 
         * If the current altitude is less than the lower bound of the range for immediate 
         * deployment, this function returns -1. If the current altitude is within the lower and 
         * upper bound (inclusive) of the range for immediate deployment, this function returns 0. 
         * If the current altitude is above the upper bound of the range for immediate deployment, 
         * this function returns 1.
         * 
         * @return -1 if below range, 0 if within range, 1 if above range.
         *****************************************************************************************/
        int isWithinImmediateDeploymentRange();

        /******************************************************************************************
         * Within Range for Incremental Partial Deployment
         * 
         * This function reads the current predicted apogee and uses this apogee, in conjuction
         * with the PARTIAL_DEPLOYMENT_RANGE parameter, to determine whether or not incremental 
         * changes to the air brake deployment percentage should be made.
         * 
         * If the predicted apogee is less than the lower bound of the range for incremental 
         * partial deployment, this function returns -1. If the predicted apogee is within the 
         * lower and upper bound (inclusive) of the range for partial deployment, this function
         * returns 0. If the predicted apogee is above the upper bound of the range for incremental 
         * partial deployment, this function returns 1.
         * 
         * @return -1 if below range, 0 if within range, 1 if above range.
         *****************************************************************************************/
        int isWithinPartialDeploymentRange();  

        /******************************************************************************************
         * Reads data from both the IMU and altimeter and packages in a single Data object.
         * 
         * @param data the data struct to populate and return
         * @return Data most recent reading from altimeter and IMU
         *****************************************************************************************/
        Data readFromSensors(Data data);

    private:

        /******************************************************************************************
         * Checks if the I-6 height data acquisition threshold has been met.
         * 
         * @return bool true if the height data acquisition threshold has been met, false otherwise
         *****************************************************************************************/
        bool meetsDaqHeightThreshold();

        /******************************************************************************************
         * Checks if the I-7 data quantity data acquisition threshold has been met.
         * 
         * @return bool true if the height data acquisition threshold has been met, false otherwise
         *****************************************************************************************/
        bool meetsDaqDataPointThreshold();

        AbstractImu* imu;
        AbstractAltimeter* altimeter;

        uint64_t altitude_of_burnout;
        uint64_t data_points_read_at_burnout;
};

#endif // __LaunchVehicle_HPP__