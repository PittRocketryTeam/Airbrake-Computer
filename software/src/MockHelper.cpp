#include "MockHelper.hpp"

MockHelper::MockHelper() :
    data_index(0),
    filename((char*)"data.txt")
{ }

MockHelper::MockHelper(char* data_filename) :
    data_index(0),
    filename(data_filename)
{ }

MockHelper::~MockHelper() { }

void MockHelper::init()
{
    if (VERBOSE) { Serial.println("Trying to init SD"); } 
    int i;
    for (i = 0; i < 1000; ++i)
    {
        delay(100);
        int status = SD.begin(BUILTIN_SDCARD);
        if (status)
        {
            break;
        }
        if (VERBOSE) { Serial.println("cannot init SD"); }      
    }

    // Make sure file exists
    if (SD.exists(filename))
    {
        if (VERBOSE) { Serial.println("data file exists"); } 
    }
    else
    {
        if (VERBOSE) { Serial.println("data file does NOT exist"); }
    }

    if (!(file = SD.open(filename, O_READ)))
    {
        if (VERBOSE) { Serial.println("init: file open failed"); }
    }

    char line[100];
    float temp;
    int pt = 0;
    while (file.fgets(line, sizeof(line)) && (pt < k_rows))
    {
        sscanf(line, "%ld,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
                &mock_data[pt].timestamp,
                &mock_data[pt].altimeterData.temperature,
                &mock_data[pt].altimeterData.pressure,
                &mock_data[pt].altimeterData.altitude,
                &mock_data[pt].imuData.euler_abs_orientation_x,
                &mock_data[pt].imuData.euler_abs_orientation_y,
                &mock_data[pt].imuData.euler_abs_orientation_z,
                &mock_data[pt].imuData.acceleration_x,
                &mock_data[pt].imuData.acceleration_y,
                &mock_data[pt].imuData.acceleration_z,
                &temp,
                &temp);
        pt++;
    }
    if (VERBOSE) { Serial.println("MockHelper init complete"); } 
}


Data MockHelper::getNextDataPoint(Data data)
{
    if(VERBOSE) 
    { 
        Serial.println("Data Index: "); 
        Serial.println(data_index);
    }
    return mock_data[data_index++];
}
