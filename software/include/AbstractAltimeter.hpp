#ifndef __ABSTRACTALTIMETER_HPP__
#define __ABSTRACTALTIMETER_HPP__

#include "Data.hpp"

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

};

#endif // __ABSTRACTALTIMETER_HPP__