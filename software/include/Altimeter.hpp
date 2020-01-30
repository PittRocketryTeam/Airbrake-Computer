#ifndef __ALTIMETER_HPP__
#define __ALTIMETER_HPP__

#include "board.hpp"
#include "Data.hpp"
#include "Adafruit_BMP3XX.h"
#include "bmp3.h"
#include "AbstractAltimeter.hpp"

class Altimeter : public AbstractAltimeter
{
    public:

        Altimeter();

        virtual ~Altimeter();
        
        virtual bool init() override;

        virtual Data read(Data data) override;
        virtual Data poll(Data data) override;

        virtual void enable() override;
        virtual void disable() override;
        
        virtual void setBaselinePressure() override;

        virtual uint64_t getNumDataPoints() override;
};

#endif
// __ALTIMETER_HPP__