#ifndef __LaunchVehicle_HPP__
#define __LaunchVehicle_HPP__

#include "constants.hpp"
// #include "IMU.hpp"
// #include "Altimeter.hpp"
#include "MockImu.hpp"
#include "MockAltimeter.hpp"


class LaunchVehicle
{
    public:

        LaunchVehicle();
        ~LaunchVehicle();

        /******************************************************************************************
         * Initialize vehicle and sensors. Accepts an IMU and Altimeter objects so these sensors
         * can be mocked.
         * 
         * @param IMU imu object (or mock)
         * @param Altimeter altimeter object (or mock)
         *****************************************************************************************/
        void init(IMU i, Altimeter a);
        
        /******************************************************************************************
         * SA-1: Launch Detection Sub-Algorithm
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
         * Determines whether or not motor burnout has completed. Motor burnout is the moment after
         * which the vehicle's motor is no longer firing. 
         * 
         * @return true if motor burnout has been detected, false otherwise.
         *****************************************************************************************/
        bool motorBurnoutDetected();

        /******************************************************************************************
         * SA-4: Data Acquisition Threshold Determination Sub-Algorithm
         * 
         * Determines whether or not enough data has been collected to begin using the data for 
         * apogee prediction. Without enough data, apogee prediction will be inaccurate and should
         * not be used to control the air brake. "Enough data" is a soft measure which is 
         * determined through experimentation. 
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
        bool isWithinImmediateDeployment();

        /******************************************************************************************
         * SA-5: Descent Detection Sub-Algorithm
         * 
         * Determines whether or not the vehicle has achieved apogee and has started to descend. 
         * 
         * @return true if the vehicle is descending, false otherwise.
         *****************************************************************************************/
        bool descentDetected();

        /******************************************************************************************
         * SA-5: Apogee Prediction Sub-Algorithm
         * 
         * Predicts the current apogee based on readings from the altimeter and IMU. 
         * 
         * @return the current predicted apogee
         *****************************************************************************************/
        long predictApogee();

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
        int withinPartialDeploymentRange();

        /******************************************************************************************
         * Calculate Deployment Action
         *
         * Determines how much the air brake should deploy as an absolute percentage. A value of
         * 100 indicates that 100% of the air brake should be deployed, whereas a value of 0%
         * indicates that none of the air brake should be deployed. This value should be within
         * 0 to 100 (inclusive).
         * 
         * @return percent absolutely air brake deployment (0 to 100 inclusive).
         *****************************************************************************************/
        int calculateDeploymentAction();

    private:

        IMU imu;
        Altimeter altimeter;
};

#endif // __LaunchVehicle_HPP__