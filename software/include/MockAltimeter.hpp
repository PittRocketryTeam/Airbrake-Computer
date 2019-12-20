#ifndef __MOCKALTIMETER_HPP__
#define __MOCKALTIMETER_HPP__

#include "Altimeter.hpp"
#include <stdio.h>
#include <SPI.h>
#include "SdFat.h"
#include "sdios.h"

#define BUILTIN_SDCARD 254

/**************************************************************************************************
 * Mocked altimeter class. Uses a csv file of data to "read" data, simulating raw data input from
 * the altimeter.
 *************************************************************************************************/
class MockAltimeter : public Altimeter
{

    private:

        SdFat SD;

        static const int rows = 208501;
        Data mocked_data[rows];
        int data_index = 0;
        char* filename;

        float temperature, pressure, altitude;

    public:
        
        MockAltimeter();
        MockAltimeter(char* data_file_path);

        virtual ~MockAltimeter();

        bool init();

        Data read(Data data);
        Data poll(Data data);

        void enable();
        void disable();

        void setBaselinePressure();
};

#endif // __MOCKALTIMETER_HPP__