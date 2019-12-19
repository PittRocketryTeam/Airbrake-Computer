#ifndef __IMU_HPP__
#define __IMU_HPP__

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "Data.hpp"
#include "board.hpp"

#define IMU_DIMENIONS 3

class IMU
{
    private:
        Adafruit_BNO055 sensor;
        sensors_event_t event;
        bool verbose;
        //Data *last_data;
        Data last_data;

        float ax, ay, az;
        float ox, oy, oz;
        imu::Vector<3> o;
        imu::Vector<3> a;

    public:

        IMU();
        IMU(bool);
        ~IMU();

        bool init();
        Data poll(Data);
        Data read(Data);

        void enable();
        void disable();
};

#endif
// __IMU_HPP__