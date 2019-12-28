#include "MockHelper.hpp"


MockHelper::MockHelper() { }

MockHelper::MockHelper(char* data_filename) //:
    // data_index(0),
    // filename(data_filename)
{ }

MockHelper::~MockHelper() { }

bool MockHelper::readFromSD()
{
    // // Open SD card
    // for (int i = 0; i < 1000; ++i)
    // {
    //     if (SD.begin(BUILTIN_SDCARD))
    //         break;
    //     Serial.println("cannot init sd");
    // }

    // delay(1000);    // replace with loop
    // File32 file = SD.open(filename, FILE_READ);

    // // Make sure file exists
    // if (!file)
    // {
    //     printf("Could not open file %s", filename);
    //     return false;
    // }

    // float temp, brightness;     // throwaway values to satisfy reads

    // // Read data into array
    // for (int row = 0; row < k_rows; row++)
    // {
    //     file.read(&mocked_data[row].timestamp, sizeof(uint64_t));

    //     file.read(&mocked_data[row].altimeterData.temperature, sizeof(uint64_t));
    //     file.read(&mocked_data[row].altimeterData.pressure, sizeof(uint64_t));
    //     file.read(&mocked_data[row].altimeterData.altitude, sizeof(uint64_t));

    //     file.read(&mocked_data[row].imuData.euler_abs_orientation_x, sizeof(uint64_t));
    //     file.read(&mocked_data[row].imuData.euler_abs_orientation_y, sizeof(uint64_t));
    //     file.read(&mocked_data[row].imuData.euler_abs_orientation_z, sizeof(uint64_t));
    //     file.read(&mocked_data[row].imuData.acceleration_x, sizeof(uint64_t));
    //     file.read(&mocked_data[row].imuData.acceleration_y, sizeof(uint64_t));
    //     file.read(&mocked_data[row].imuData.acceleration_z, sizeof(uint64_t));

    //     file.read(&temp, sizeof(uint64_t));
    //     file.read(&brightness, sizeof(uint64_t));
    // }
    return true;
}

Data MockHelper::getNextDataPoint(Data data)
{
    // data = mocked_data[data_index];
    // data_index++;

    return data;
}


