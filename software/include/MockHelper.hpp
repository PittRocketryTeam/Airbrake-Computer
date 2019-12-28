#ifndef __MOCK_HELPER_hpp__
#define __MOCK_HELPER_hpp__

#include <stdio.h>
#include <SPI.h>
#include "SdFat.h"
#include "sdios.h"
#include "Data.hpp"

#define BUILTIN_SDCARD 254

class MockHelper
{
    public:

        MockHelper();
        MockHelper(char* data_filename);

        virtual ~MockHelper();

        virtual bool readFromSD();

        virtual Data getNextDataPoint(Data data);

    private:

        static const int k_rows = 208501;
        int data_index;

        char* filename;

        Data mocked_data[k_rows];
        SdFat SD;
};

#endif   // __MOCK_HELPER_HPP__
