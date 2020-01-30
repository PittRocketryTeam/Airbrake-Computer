#ifndef __IMU_HPP__
#define __IMU_HPP__

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "constants.hpp"
#include "board.hpp"
#include "AbstractImu.hpp"

#define IMU_DIMENIONS 3

class IMU : public AbstractImu
{
    private:
        Adafruit_BNO055 sensor;
        sensors_event_t event;
        bool verbose;
        Data last_data;
        
        float ax, ay, az;
        float ox, oy, oz;
        imu::Vector<3> o;
        imu::Vector<3> a;

    public:

        IMU();
        IMU(bool);
        virtual ~IMU();

        virtual bool init() override;
        virtual Data poll(Data) override;
        virtual Data read(Data) override;

        virtual void enable() override;
        virtual void disable() override;

        virtual uint64_t getNumDataPoints() override;
};

#endif
// __IMU_HPP__