#ifndef __MOCK_HELPER_CPP__
#define __MOCK_HELPER_CPP__

#include <stdio.h>
#include <SPI.h>
#include "SdFat.h"
#include "sdios.h"
#include "Data.hpp"

#define BUILTIN_SDCARD 254

class MockHelper
{
    public:

        MockHelper(char* data_filename):
            data_index(0),
            filename(data_filename)
        { }

        ~MockHelper() { }

        bool readFromSD()
        {
            // Open SD card
            for (int i = 0; i < 1000; ++i)
            {
                if (SD.begin(BUILTIN_SDCARD))
                    break;
                Serial.println("cannot init sd");
            }

            delay(1000);    // replace with loop
            File32 file = SD.open(filename, FILE_READ);

            // Make sure file exists
            if (!file)
            {
                printf("Could not open file %s", filename);
                return false;
            }

            float temp, brightness;     // throwaway values to satisfy reads

            // Read data into array
            for (int row = 0; row < k_rows; row++)
            {
                file.read(&mocked_data[row].timestamp, sizeof(uint64_t));

                file.read(&mocked_data[row].altimeterData.temperature, sizeof(uint64_t));
                file.read(&mocked_data[row].altimeterData.pressure, sizeof(uint64_t));
                file.read(&mocked_data[row].altimeterData.altitude, sizeof(uint64_t));

                file.read(&mocked_data[row].imuData.euler_abs_orientation_x, sizeof(uint64_t));
                file.read(&mocked_data[row].imuData.euler_abs_orientation_y, sizeof(uint64_t));
                file.read(&mocked_data[row].imuData.euler_abs_orientation_z, sizeof(uint64_t));
                file.read(&mocked_data[row].imuData.acceleration_x, sizeof(uint64_t));
                file.read(&mocked_data[row].imuData.acceleration_y, sizeof(uint64_t));
                file.read(&mocked_data[row].imuData.acceleration_z, sizeof(uint64_t));

                file.read(&temp, sizeof(uint64_t));
                file.read(&brightness, sizeof(uint64_t));
            }
            return true;
        }

        Data getNextDataPoint(Data data)
        {
            data = mocked_data[data_index];
            data_index++;

            return data;
        }

    private:

        static const int k_rows = 208501;
        int data_index;

        char* filename;

        Data mocked_data[k_rows];
        SdFat SD;
};

#endif   // __MOCK_HELPER_CPP__
