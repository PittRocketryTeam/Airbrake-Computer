#include "MockImu.hpp"

MockImu::MockImu() //s: 
    // mockHelper((char*)"data.csv")
{}

MockImu::MockImu(char* data_file_path) //:
    // mockHelper(data_file_path)
{}

MockImu::~MockImu() { }

bool MockImu::init()
{
    // return mockHelper.readFromSD();
    return true;
}

Data MockImu::read(Data data)
{
    // Return local data
    // data.imuData.euler_abs_orientation_x = ox;
    // data.imuData.euler_abs_orientation_y = oy;
    // data.imuData.euler_abs_orientation_z = oz;

    // data.imuData.acceleration_x = ax;
    // data.imuData.acceleration_y = ay;
    // data.imuData.acceleration_z = az;

    return data;
}

Data MockImu::poll(Data data)
{
    // Set local data from file
    // data = mockHelper.getNextDataPoint(data);

    // ox = data.imuData.euler_abs_orientation_x;
    // oy = data.imuData.euler_abs_orientation_y;
    // oz = data.imuData.euler_abs_orientation_z;

    // ax = data.imuData.acceleration_x;
    // ay = data.imuData.acceleration_y;
    // az = data.imuData.acceleration_z;

    return read(data);
}

void MockImu::enable() { }

void MockImu::disable() { }