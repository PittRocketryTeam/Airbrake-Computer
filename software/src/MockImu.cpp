#include "IMU.hpp"
#include <stdio.h>

class MockImu : public IMU 
{
    static const int rows = 208501;
    int data_index = 0;
    char* filename;

    // timestamp, temperature, pressure, altitude
    Data mocked_data[rows];

    float ax, ay, az;
    float ox, oy, oz;
    imu::Vector<3> o;
    imu::Vector<3> a;

    public:MockImu()
    {
        ax = 0.0f;
        ay = 0.0f;
        az = 0.0f;
        ox = 0.0f;
        oy = 0.0f;
        oz = 0.0f;
    }

    public:MockImu(char* data_file_path)
    {
        filename = data_file_path;
        ax = 0.0f;
        ay = 0.0f;
        az = 0.0f;
        ox = 0.0f;
        oy = 0.0f;
        oz = 0.0f;
    }

    ~MockImu()
    {
        //delete last_data;
    }

    bool init()
    {
        // Read from file
        FILE* file = fopen(filename, "r");
        if (file == NULL)
        {
            printf("Could not open file %s", filename);
            return false;
        }

        float temp, brightness; // throwaway values to satisfy fscanf

        // Read data into array
        for (int row = 0; row < rows; row++)
        {
            fscanf(file,"%ld %f %f %f %f %f %f %f %f %f %f %f",  
                   &mocked_data[row].timestamp, 
                   &mocked_data[row].altimeterData.temperature, 
                   &mocked_data[row].altimeterData.pressure, 
                   &mocked_data[row].altimeterData.altitude, 
                   &mocked_data[row].imuData.euler_abs_orientation_x, 
                   &mocked_data[row].imuData.euler_abs_orientation_y, 
                   &mocked_data[row].imuData.euler_abs_orientation_z, 
                   &mocked_data[row].imuData.acceleration_x,
                   &mocked_data[row].imuData.acceleration_y,
                   &mocked_data[row].imuData.acceleration_z,
                   &temp,
                   &brightness
            );
        }
        
        fclose(file);
        return true;
    }

    Data read(Data data)
    {
        // Set data from file
        data = mocked_data[data_index];

        data.imuData.euler_abs_orientation_x = ox;
        data.imuData.euler_abs_orientation_y = oy;
        data.imuData.euler_abs_orientation_z = oz;

        data.imuData.acceleration_x = ax;
        data.imuData.acceleration_y = ay;
        data.imuData.acceleration_z = az;

        return data;
    }

    Data poll(Data data)
    {
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

    void enable()
    {
        // Do nothing
    }

    void disable()
    {
        // Do nothing
    }
};
