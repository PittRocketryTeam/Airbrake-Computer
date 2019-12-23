#ifndef __MOCKIMU_HPP__
#define __MOCKIMU_HPP__

#include "IMU.hpp"
#include "MockHelper.cpp"

#define BUILTIN_SDCARD 254

/**************************************************************************************************
 * Mocked IMU class. Uses a csv file of data to "read" data, simulating raw data input from IMU.
 *************************************************************************************************/
class MockImu : public IMU
{
    private:

        MockHelper mockHelper;

    public:

        MockImu(char* data_file_path);

        virtual ~MockImu();

        bool init();

        Data read(Data data);
        Data poll(Data data);

        void enable();
        void disable();
};

#endif // __MOCKIMU_HPP__