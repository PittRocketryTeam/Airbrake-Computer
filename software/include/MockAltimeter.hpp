#ifndef __MOCKALTIMETER_HPP__
#define __MOCKALTIMETER_HPP__

#include "Altimeter.hpp"
#include "MockHelper.cpp"

#define BUILTIN_SDCARD 254

/**************************************************************************************************
 * Mocked altimeter class. Uses a csv file of data to "read" data, simulating raw data input from
 * the altimeter.
 *************************************************************************************************/
class MockAltimeter : public Altimeter
{

    private:

        MockHelper mockHelper;
        float temperature, pressure, altitude;

    public:
        
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