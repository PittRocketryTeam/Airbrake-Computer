#ifndef __ABSTRACTIMU_HPP__
#define __ABSTRACTIMU_HPP__

#include "Data.hpp"

class AbstractImu
{
    public:

        AbstractImu() {}
        ~AbstractImu() {}

        virtual bool init() = 0;
        virtual Data read(Data data) = 0;
        virtual Data poll(Data data) = 0;
        virtual void enable() = 0;
        virtual void disable() = 0;

};

#endif // __ABSTRACTIMU_HPP__