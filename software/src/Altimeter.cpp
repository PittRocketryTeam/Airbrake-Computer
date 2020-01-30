#include "Altimeter.hpp"

Adafruit_BMP3XX bmp; // inits for i2c - defaults to 0x77 address and "Wire"
struct bmp3_dev* bmp_dev;
float initAlt = -1;

Altimeter::Altimeter() {}

Altimeter::~Altimeter(){}

bool Altimeter::init()
{
    int i;
    for (i=0; i < 20; i++)
    {
        if (bmp.begin())
        {
            Serial.println("altimeter init succeeded");
            break;
        }
        else
        {
            Serial.println("altimeter init failed");
        }

        delay(100);
    }

    return true;
}

Data Altimeter::read(Data data)
{
    data.altimeterData.temperature = bmp.temperature;
    data.altimeterData.pressure = bmp.pressure;

    if(initAlt == -1) //case where initAlt isn't set -- haven't hit button on ground control yet to indicate we're ready to launch
    {
        Serial.println("Cannot poll altitude --- ground pressure not yet set!");
    }
    else
    {
        data.altimeterData.altitude = bmp.readAltitude(initAlt);//does not performReading again, altitude is just calculated from the pressure and the ground level pressure set earlier
    }

    return data;
}

Data Altimeter::poll(Data data)
{
    if(!bmp.performReading()) //assigns values to pressure and temperature
    {
        Serial.println("Failed to perform reading :(");
    }

    data.altimeterData.temperature = bmp.readTemperature();
    data.altimeterData.pressure = bmp.readPressure();
    if(initAlt == -1) //case where initAlt isn't set -- haven't hit button on ground control yet to indicate we're ready to launch
    {
        Serial.println("Cannot poll altitude --- ground pressure not yet set!");
    }
    else
    {
        data.altimeterData.altitude = bmp.readAltitude(initAlt);
    }
    
    Serial.printf("temp: %f\tpressure: %f\talt: %f\t", data.altimeterData.temperature, data.altimeterData.pressure, data.altimeterData.altitude);
    
    return data;
}

void Altimeter::enable()
{
    bmp_dev->settings.op_mode = BMP3_NORMAL_MODE;
    if(bmp3_set_op_mode(bmp_dev) != 0)
    {
        Serial.println("Altimeter failed to enable");
    }
}

void Altimeter::disable()
{
    bmp_dev->settings.op_mode = BMP3_SLEEP_MODE;
    if(bmp3_set_op_mode(bmp_dev) != 0)
    {
        Serial.println("Altimeter failed to disable");
    }
}

void Altimeter::setBaselinePressure()
{
    initAlt = bmp.readPressure();
}

uint64_t Altimeter::getNumDataPoints()
{
    return data_points_read;
}
