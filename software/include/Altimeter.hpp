#ifndef __ALTIMETER_HPP__
#define __ALTIMETER_HPP__

#include "board.hpp"
#include "Data.hpp"
#include "Adafruit_BMP3XX.h"
#include "bmp3.h"

class Altimeter
{
    public:

        Altimeter();
        ~Altimeter();
        
        virtual bool init();
        Data read(Data data);
        Data poll(Data data);
        void enable();
        void disable();
        void setBaselinePressure();
};

#endif
// __ALTIMETER_HPP__