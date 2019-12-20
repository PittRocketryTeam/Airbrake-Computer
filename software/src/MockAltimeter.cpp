#include "MockAltimeter.hpp"

MockAltimeter::MockAltimeter() { }

MockAltimeter::MockAltimeter(char* data_file_path) 
{
    filename = data_file_path;
}

MockAltimeter::~MockAltimeter() { }

bool MockAltimeter::init()
{
    // Open SD card
    for (int i = 0; i < 1000; ++i)
    {
        if (SD.begin(BUILTIN_SDCARD))
            break;
        Serial.println("cannot init sd");
    }

    delay(1000); // replace with loop
    File32 file = SD.open(filename, FILE_READ);

    // Make sure file exists
    if (!file)
    {
        printf("Could not open file %s", filename);
        return false;
    }

    float temp, brightness; // throwaway values to satisfy reads

    // Read data into array
    for (int row = 0; row < rows; row++)
    {
        file.read(&mocked_data[row].timestamp, sizeof(unsigned long));
        
        file.read(&mocked_data[row].altimeterData.temperature, sizeof(float));
        file.read(&mocked_data[row].altimeterData.pressure, sizeof(float));
        file.read(&mocked_data[row].altimeterData.altitude, sizeof(float));

        file.read(&mocked_data[row].imuData.euler_abs_orientation_x, sizeof(float));
        file.read(&mocked_data[row].imuData.euler_abs_orientation_y, sizeof(float));
        file.read(&mocked_data[row].imuData.euler_abs_orientation_z, sizeof(float));
        file.read(&mocked_data[row].imuData.acceleration_x, sizeof(float));
        file.read(&mocked_data[row].imuData.acceleration_y, sizeof(float));
        file.read(&mocked_data[row].imuData.acceleration_z, sizeof(float));

        file.read(&temp, sizeof(float));
        file.read(&brightness, sizeof(float));
    }
    
    file.close();
    return true;
}

Data MockAltimeter::read(Data data)
{
    data.altimeterData.temperature = temperature;
    data.altimeterData.pressure = pressure;
    data.altimeterData.altitude = altitude;

    return data;
}

Data MockAltimeter::poll(Data data)
{
    data = mocked_data[data_index];
    data_index++;

    temperature = data.altimeterData.temperature;
    pressure = data.altimeterData.pressure;
    altitude = data.altimeterData.altitude;

    return data;
}

void MockAltimeter::enable() { }

void MockAltimeter::disable() { }

void MockAltimeter::setBaselinePressure() { }