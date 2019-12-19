#ifndef __AIRBRAKE_HPP__
#define __AIRBRAKE_HPP__

#include "constants.hpp"

class Airbrake
{
    public:

        Airbrake();
        ~Airbrake();

        /******************************************************************************************
         * Sets the absolute deployment percentage of the air brake.
         * 
         * @param percent   the percentage (0 to 100 inclusive) of the air brake to deploy.
         *****************************************************************************************/
        void setAbsoluteDeployment(int percent);
        
        /******************************************************************************************
         * Deploys the air brake completely (100% deployment).
         *****************************************************************************************/
        void deployCompletely();

        /******************************************************************************************
         * Retracts the air brake completely (0% deployment).
         *****************************************************************************************/
        void retractCompletely();

        /******************************************************************************************
         * Returns the current air brake deployment percentage. Must always be between 0 and 100 
         * inclusive.
         * 
         * @return current air brake deployment percentage.
         *****************************************************************************************/
        int getDeploymentPercentage();

    private:

        /******************************************************************************************
         * Internal record of current air brake deployment percentage, between 0 and 100 inclusive.
         *****************************************************************************************/
        int deployment_percentage;

};

#endif // __AIRBRAKE_HPP__