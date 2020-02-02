#include "MockAltimeter.hpp"

MockAltimeter::MockAltimeter(MockHelper helper)
{
    mockHelper = helper;
}

MockAltimeter::~MockAltimeter() { }

bool MockAltimeter::init()
{
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
    data = mockHelper.getNextDataPoint(data);

    temperature = data.altimeterData.temperature;
    pressure = data.altimeterData.pressure;
    altitude = data.altimeterData.altitude + ALT_CALIBRATION_OFFSET;    // Account for offset

    data_points_read++;

    return data;
}

void MockAltimeter::enable() { }

void MockAltimeter::disable() { }

void MockAltimeter::setBaselinePressure() { }

uint64_t MockAltimeter::getNumDataPoints()
{
    return data_points_read;
}