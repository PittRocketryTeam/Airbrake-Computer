#include "Logger.hpp"

Logger::Logger() :
    num_sensors(0)
{

}

Logger::~Logger() {}

bool Logger::init()
{
    // Initialize RTC
    setSyncProvider(getTeensy3Time);
    delay(100);
    RTC_set_successfully = (timeStatus() == timeSet);

    generateFilename();  // Generate unique log filename

    int i;
    for (i = 0; i < 20; ++i)
    {
        int status = SD.begin(BUILTIN_SDCARD);
        if (status)
        {
            break;
        }
        delay(100);
    }

    handle = SD.open(filename, FILE_WRITE);

    return true;
}

void Logger::addSensor(Sensor* sensor)
{
    sensors[num_sensors++] = sensor;
}

bool Logger::log()
{
    Data data = readDataFromSensors();  // Read data from sensors              
    return writeToMemory(data);         // Write data to micro SD
}

bool Logger::logEvent(char event_str[])
{
    if (!handle)
    {
        return false;
    }
    Data data;
    current_time = millis();
    data.timestamp = (long int)current_time; 

    handle.printf("%ld,%s\n",
            data.timestamp,
            event_str); 

    return false;
}

void Logger::generateFilename()
{
    memset(filename, 0, sizeof(filename));

    current_time = now();
    if (RTC_set_successfully)
    {
        sprintf(filename, "%d-%d-%d_%d-%d-%d-AIRBRAKE.csv", 
                month(current_time),
                day(current_time),
                year(current_time),
                hour(current_time),
                minute(current_time),
                second(current_time)
               );        
    }
    else
    {
        sprintf(filename, "loggylog-AIRBRAKE.csv");
    }

}

Data Logger::readDataFromSensors()
{
    Data data;

    if (MANUAL_MODE)
    {
        // For mocked data, only read from one sensor to avoid duplicate reads
        data = sensors[0]->read(data);
    }
    else
    {
        int i;
        for (i = 0; i < num_sensors; ++i)
        {
            data = sensors[i]->read(data);
        }
    }
    
    // Add timestamp
    current_time = millis();
    data.timestamp = (long int)current_time;

    if (VERBOSE) 
    { 
        Serial.printf("Logger::readDataFromSensors - timestamp: %ld, alt: %f\n", 
            data.timestamp,
            data.altimeterData.altitude); 
    }
    return data;                        
}

bool Logger::writeToMemory(Data data)
{
    if (!handle)
    {
        return false;
    }

    handle.printf("%ld, ,%f,%f,%f, ,%f,%f,%f, ,%f,%f,%f, \n",
            data.timestamp,

            data.altimeterData.temperature, 
            data.altimeterData.pressure, 
            data.altimeterData.altitude,
            
            data.imuData.euler_abs_orientation_x, 
            data.imuData.euler_abs_orientation_y, 
            data.imuData.euler_abs_orientation_z,

            data.imuData.acceleration_x,
            data.imuData.acceleration_y,
            data.imuData.acceleration_z);

    return true; 
}

void Logger::flush()
{
    if (!handle)
    {
        return;
    }
    handle.flush();
}

void Logger::reopen()
{
    if (!handle)
    {
        handle = SD.open(filename, FILE_WRITE);
    }
}

void Logger::close()
{
    if (handle.isOpen())
    {
        handle.flush();
        handle.close();
    }
}

time_t Logger::getTeensy3Time()
{
    return Teensy3Clock.get();
}