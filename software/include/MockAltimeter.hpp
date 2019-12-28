#ifndef __MOCKALTIMETER_HPP__
#define __MOCKALTIMETER_HPP__

#include "AbstractAltimeter.hpp"
#include "MockHelper.hpp"

/**************************************************************************************************
 * Mocked altimeter class. Uses a csv file of data to "read" data, simulating raw data input from
 * the altimeter.
 *************************************************************************************************/
class MockAltimeter : public AbstractAltimeter
{

    private:

        MockHelper mockHelper;
        float temperature, pressure, altitude;

    public:
        
        MockAltimeter(char* data_file_path);

        virtual ~MockAltimeter();

        virtual bool init() override;

        virtual Data read(Data data) override;
        virtual Data poll(Data data) override;

        virtual void enable() override;
        virtual void disable() override;

        virtual void setBaselinePressure() override;
};

#endif // __MOCKALTIMETER_HPP__