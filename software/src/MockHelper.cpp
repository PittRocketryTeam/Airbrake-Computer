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

    Data data;
    char line[100];
    while (file.fgets(line, sizeof(line)))
    {
        // Serial.println(line);

        // char* chars_array = strtok(line, ",");
        // while(chars_array)
        // {
        //     // MessageBox(NULL, subchar_array, NULL, NULL);
        //     Serial.println(chars_array);

        //     chars_array = strtok(NULL, ",");
        // }

        Serial.println(line);

        char temp[sizeof(uint64_t)];
        char float_temp[sizeof(float)];

        memset(temp, 0, sizeof(temp));
        strncpy(temp, line, 15);
        temp[15] = '\0'; // IMPORTANT!
        data.timestamp = strtoull(temp, NULL, 0);
        Serial.println(data.timestamp);

        memset(float_temp, 0, sizeof(float_temp));
        strncpy(float_temp, line, 15);
        float_temp[15] = '\0'; // IMPORTANT!
        Serial.println(float_temp);
        data.timestamp = atof(float_temp);
        Serial.println(data.timestamp);

        // data.altimeterData.pressure = strtoull(line, NULL, 0);
        // Serial.println(data.altimeterData.pressure);

        // data.altimeterData.altitude = strtoull(line, NULL, 0);
        // Serial.println(data.altimeterData.altitude);

        delay(1000);


    }
}

MockHelper::~MockHelper() { }

Data MockHelper::getNextDataPoint(Data data)
{
    // Serial.println("\nMockHelper: inside getNextDataPoint()");

    // file.open(filename, FILE_READ);
    // file.seekSet(84);
    // Serial.println(file.curPosition());

    // char line[84];
    // file.fgets(line, sizeof(line));
    // Serial.println(line);
    // Serial.println(file.curPosition());
    // Serial.println(file.fileSize());

    // data.timestamp
    // memset(line, 0, sizeof(line));
    // file.fgets(line, sizeof(line));  
    // data.timestamp = strtoull(line, NULL, 0);
    // Serial.println(data.timestamp);

    // data.altimeterData.temperature
    // memset(line, 0, sizeof(line));
    // file.fgets(line, sizeof(line));  
    // data.altimeterData.temperature = strtoull(line, NULL, 0);
    // Serial.println(data.altimeterData.temperature);

    // // data.altimeterData.pressure
    // memset(line, 0, sizeof(line));
    // file.fgets(line, sizeof(line), (char*)",");  
    // data.altimeterData.pressure = strtoull(line, NULL, 0);

    // // data.altimeterData.altitude
    // memset(line, 0, sizeof(line));
    // file.fgets(line, sizeof(line), (char*)",");
    // data.altimeterData.altitude = strtoull(line, NULL, 0);

    // // data.imuData.euler_abs_orientation_x
    // memset(line, 0, sizeof(line));
    // file.fgets(line, sizeof(line), (char*)",");
    // data.imuData.euler_abs_orientation_x = strtoull(line, NULL, 0);

    // // data.imuData.euler_abs_orientation_y
    // memset(line, 0, sizeof(line));
    // file.fgets(line, sizeof(line), (char*)",");
    // data.imuData.euler_abs_orientation_y = strtoull(line, NULL, 0);

    // // data.imuData.euler_abs_orientation_z
    // memset(line, 0, sizeof(line));
    // file.fgets(line, sizeof(line), (char*)",");
    // data.imuData.euler_abs_orientation_z = strtoull(line, NULL, 0);

    // // data.imuData.acceleration_x
    // memset(line, 0, sizeof(line));
    // file.fgets(line, sizeof(line), (char*)",");
    // data.imuData.acceleration_x = strtoull(line, NULL, 0);

    // // data.imuData.acceleration_y
    // memset(line, 0, sizeof(line));
    // file.fgets(line, sizeof(line), (char*)",");
    // data.imuData.acceleration_y = strtoull(line, NULL, 0);

    // // data.imuData.acceleration_z
    // memset(line, 0, sizeof(line));
    // file.fgets(line, sizeof(line), (char*)",");
    // data.imuData.acceleration_z = strtoull(line, NULL, 0);

    // // data.healthData.main_battery_temperature
    // memset(line, 0, sizeof(line));
    // file.fgets(line, sizeof(line), (char*)",");

    // // data.photocellData.brightness
    // memset(line, 0, sizeof(line));
    // file.fgets(line, sizeof(line));

    
    
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
