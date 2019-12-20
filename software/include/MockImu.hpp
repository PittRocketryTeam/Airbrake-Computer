#ifndef __MOCKIMU_HPP__
#define __MOCKIMU_HPP__

#include "IMU.hpp"
#include <stdio.h>
#include <SPI.h>
#include "SdFat.h"
#include "sdios.h"

#define BUILTIN_SDCARD 254

/**************************************************************************************************
 * Mocked IMU class. Uses a csv file of data to "read" data, simulating raw data input from IMU.
 *************************************************************************************************/
class MockImu : public IMU
{
    private:

        SdFat SD;

        static const int rows = 208501;
        int data_index = 0;
        char* filename;

        Data mocked_data[rows];

    public:

        MockImu();
        MockImu(char* data_file_path);

        virtual ~MockImu();

        bool init();

        Data read(Data data);
        Data poll(Data data);

        void enable();
        void disable();
};

#endif // __MOCKIMU_HPP__