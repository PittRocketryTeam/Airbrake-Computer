#ifndef __MOCK_HELPER_hpp__
#define __MOCK_HELPER_hpp__

#include <stdio.h>
#include <SPI.h>
#include "SdFat.h"
#include "sdios.h"
#include "Data.hpp"

#define k_rows 20000
#define k_bytes_per_line 96

#define BUILTIN_SDCARD 254

class MockHelper
{
    public:

        MockHelper();
        MockHelper(char* data_filename);

        virtual ~MockHelper();

        virtual void init();

        virtual Data getNextDataPoint(Data data);

    private:

        float temp, brightness;    // throwaway values to satisfy reads

        int file_index;            // Current index in file (in bytes)

        char* filename;            // Name of data file

        SdFat32 SD;                  // SD reader object

        File32 file;
};

#endif   // __MOCK_HELPER_HPP__
