#include "MockAltimeter.hpp"

MockAltimeter::MockAltimeter(char* data_file_path) :
    mockHelper(data_file_path)
{
    
}

MockAltimeter::~MockAltimeter() { }

bool MockAltimeter::init()
{
    mockHelper.readFromSD();
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
    data = mockHelper.getNextDataPoint(data);

    temperature = data.altimeterData.temperature;
    pressure = data.altimeterData.pressure;
    altitude = data.altimeterData.altitude;

    return data;
}

void MockAltimeter::enable() { }

void MockAltimeter::disable() { }

void MockAltimeter::setBaselinePressure() { }