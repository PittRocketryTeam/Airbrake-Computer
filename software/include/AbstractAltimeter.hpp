#ifndef __ABSTRACTALTIMETER_HPP__
#define __ABSTRACTALTIMETER_HPP__

#include "Data.hpp"
#include <cstdint>

class AbstractAltimeter
{
    public:

        AbstractAltimeter() {}
        ~AbstractAltimeter() {}

        virtual bool init() = 0;
        virtual Data read(Data data) = 0;
        virtual Data poll(Data data) = 0;
        virtual void enable() = 0;
        virtual void disable() = 0;

        virtual void setBaselinePressure() = 0;

        virtual uint64_t getNumDataPoints() = 0;

    protected:

        uint64_t data_points_read;

};

#endif // __ABSTRACTALTIMETER_HPP__