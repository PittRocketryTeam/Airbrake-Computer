#include "MockHelper.hpp"

MockHelper::MockHelper() :
    file_index(0),
    filename((char*)"data.txt")
{ }

MockHelper::MockHelper(char* data_filename) :
    file_index(0),
    filename(data_filename)
{ }

void MockHelper::init()
{
    delay(1000);

    Serial.println("Trying to init SD");
    int i;
    for (i = 0; i < 1000; ++i)
    {
        delay(100);
        int status = SD.begin(BUILTIN_SDCARD);
        if (status)
        {
            break;
        }
        Serial.println("cannot init SD");        
    }

    delay(1000);    // replace with loops

    // Make sure file exists
    if (SD.exists(filename))
    {
        Serial.println("data file exists");
    }
    else
    {
        Serial.println("data file does NOT exist");
    }

    if (!(file = SD.open(filename, O_READ)))
    {
        Serial.println("init: file open failed");
    }

    delay(1000);
}

MockHelper::~MockHelper() { }

Data MockHelper::getNextDataPoint(Data data)
{
    Serial.println("\nMockHelper: inside getNextDataPoint()");

    file.open(filename, FILE_READ);

    char line[10];
    file.fgets(line, sizeof(line));
    Serial.println(line);

    // char buf[9];

    // // data.timestamp
    // memset(buf, 0, sizeof(buf));
    // file.fgets(buf, sizeof(buf), (char*)",");  
    // data.timestamp = strtoull(buf, NULL, 0);

    // // data.altimeterData.temperature
    // memset(buf, 0, sizeof(buf));
    // file.fgets(buf, sizeof(buf), (char*)",");  
    // data.altimeterData.temperature = strtoull(buf, NULL, 0);

    // // data.altimeterData.pressure
    // memset(buf, 0, sizeof(buf));
    // file.fgets(buf, sizeof(buf), (char*)",");  
    // data.altimeterData.pressure = strtoull(buf, NULL, 0);

    // // data.altimeterData.altitude
    // memset(buf, 0, sizeof(buf));
    // file.fgets(buf, sizeof(buf), (char*)",");
    // data.altimeterData.altitude = strtoull(buf, NULL, 0);

    // // data.imuData.euler_abs_orientation_x
    // memset(buf, 0, sizeof(buf));
    // file.fgets(buf, sizeof(buf), (char*)",");
    // data.imuData.euler_abs_orientation_x = strtoull(buf, NULL, 0);

    // // data.imuData.euler_abs_orientation_y
    // memset(buf, 0, sizeof(buf));
    // file.fgets(buf, sizeof(buf), (char*)",");
    // data.imuData.euler_abs_orientation_y = strtoull(buf, NULL, 0);

    // // data.imuData.euler_abs_orientation_z
    // memset(buf, 0, sizeof(buf));
    // file.fgets(buf, sizeof(buf), (char*)",");
    // data.imuData.euler_abs_orientation_z = strtoull(buf, NULL, 0);

    // // data.imuData.acceleration_x
    // memset(buf, 0, sizeof(buf));
    // file.fgets(buf, sizeof(buf), (char*)",");
    // data.imuData.acceleration_x = strtoull(buf, NULL, 0);

    // // data.imuData.acceleration_y
    // memset(buf, 0, sizeof(buf));
    // file.fgets(buf, sizeof(buf), (char*)",");
    // data.imuData.acceleration_y = strtoull(buf, NULL, 0);

    // // data.imuData.acceleration_z
    // memset(buf, 0, sizeof(buf));
    // file.fgets(buf, sizeof(buf), (char*)",");
    // data.imuData.acceleration_z = strtoull(buf, NULL, 0);

    // // data.healthData.main_battery_temperature
    // memset(buf, 0, sizeof(buf));
    // file.fgets(buf, sizeof(buf), (char*)",");

    // // data.photocellData.brightness
    // memset(buf, 0, sizeof(buf));
    // file.fgets(buf, sizeof(buf));

    // Serial.println(data.timestamp);
    // Serial.println(data.altimeterData.temperature);
    // Serial.println(data.altimeterData.pressure);
    // Serial.println(data.altimeterData.altitude);
    // Serial.println(data.imuData.euler_abs_orientation_x);
    // Serial.println(data.imuData.euler_abs_orientation_y);
    // Serial.println(data.imuData.euler_abs_orientation_z);
    // Serial.println(data.imuData.acceleration_x);
    // Serial.println(data.imuData.acceleration_y);
    // Serial.println(data.imuData.acceleration_z);

    return data;
}
