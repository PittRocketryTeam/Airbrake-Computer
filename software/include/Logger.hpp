  
#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include "assert.h"
#include "Sensor.hpp"
#include <SPI.h> 
#include "Time.h"
#include "SdFat.h"
#include "TimeLib.h"
#include "board.hpp"
#include "constants.hpp"

class Logger
{
    public:

        Logger();
        ~Logger();

        /**
         * Initialize the logger. Returns false if the initialization fails for 
         * any reason.
        */
        virtual bool init();

        /*
         * Add a sensor to the logger's list of sensors.
         */
        virtual void addSensor(Sensor* sensor);

        /******************************************************************************************
         * Reads from each sensor and writes the timestamped data to the disk. Returns true if data
         * was successfully written, false if not (either because the number of bytes that should 
         * have been written to the disk was not written or because the micro SD couldn't be 
         * opened).
         * 
         * @return true if data was successfully written to the micro SD
         *****************************************************************************************/
        virtual bool log();


        /******************************************************************************************
         * Writes 'event_str' to the logfile with a timestamp.
         * 
         * @return true if data was successfully written to the micro SD
         *****************************************************************************************/
        virtual bool logEvent(char event_str[]);

        void reopen();
        void close();
        void flush();

        virtual bool writeToMemory(Data);

    private:

        /******************************************************************************************
         * Creates a unique log file name based on the current time and date.
         * 
         * Example log filename: Monday_10-07-2019_03:26:41.log
         *****************************************************************************************/
        virtual void generateFilename();

        virtual Data readDataFromSensors();

        static time_t getTeensy3Time();

        SdFat SD;

        /**
         * Sensors to log data from.
         */
        Sensor* sensors[MAX_SENSORS];
        int num_sensors;

        // Timer variables
        time_t current_time;
        bool RTC_set_successfully;

        /**
         * Logfile name.
        */
        char filename[128];

        char buffer[1000];
        File32 handle;
};

#endif
// __LOGGER_HPP__