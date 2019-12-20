#include "MockImu.hpp"

MockImu::MockImu()
{
    IMU();
}

MockImu::MockImu(char* data_file_path)
{
    IMU();
    filename = data_file_path;
}

MockImu::~MockImu() { }

bool MockImu::init()
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

Data MockImu::read(Data data)
{
    // Return local data
    data.imuData.euler_abs_orientation_x = ox;
    data.imuData.euler_abs_orientation_y = oy;
    data.imuData.euler_abs_orientation_z = oz;

    data.imuData.acceleration_x = ax;
    data.imuData.acceleration_y = ay;
    data.imuData.acceleration_z = az;

    return data;
}

Data MockImu::poll(Data data)
{
    // Set local data from file
    data = mocked_data[data_index];
    data_index++;

    ox = data.imuData.euler_abs_orientation_x;
    oy = data.imuData.euler_abs_orientation_y;
    oz = data.imuData.euler_abs_orientation_z;

    ax = data.imuData.acceleration_x;
    ay = data.imuData.acceleration_y;
    az = data.imuData.acceleration_z;

    return read(data);
}

void MockImu::enable() { }

void MockImu::disable() { }