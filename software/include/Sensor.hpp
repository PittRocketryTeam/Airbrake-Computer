#ifndef __SENSOR_HPP__
#define __SENSOR_HPP__

#include "Wire.h"
#include "Data.hpp"

class Sensor
{
    public:

        Sensor() {}
        ~Sensor() {}

        /****************************************************************************************** 
         * Initialize the sensor so it can be used. Return true if the sensor is initialized and 
         * ready to be enabled, disabled, read, or polled, and false otherwise.
         * 
         * @return true if successfully initialized, otherwise false
         *****************************************************************************************/
        virtual bool init() = 0;

        /******************************************************************************************
         * Read current sensor data and returns it as Data struct. Accepts a data struct and 
         * populates the appropriate fields.
         * 
         * @param data the struct to be populated
         * @return Data populated from latest read
         *****************************************************************************************/
        virtual Data read(Data data) = 0;

        /******************************************************************************************
         * Accepts a data struct and populates the appropriate fields from the latest call to 
         * read().
         * 
         * @param data the struct to be populated
         * @return Data populated from latest read
         *****************************************************************************************/
        virtual Data poll(Data data) = 0;

        /******************************************************************************************
         * Enable the sensor to be read.
         *****************************************************************************************/
        virtual void enable() = 0;

        /******************************************************************************************
         * Disable the sensor from being read.
         *****************************************************************************************/
        virtual void disable() = 0;
    
    protected:

        /******************************************************************************************
         * Maintains the state of the sensor. It can only be enabled or disabled.
         * Only if the sensor is enabled ca the read() and poll() functions be called.
         *****************************************************************************************/
        enum sensor_state { ENABLED, DISABLED };
        sensor_state state;
};

#endif
// __SENSOR_HPP__