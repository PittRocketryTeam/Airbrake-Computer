#ifndef __MOCKIMU_HPP__
#define __MOCKIMU_HPP__

// #include "IMU.hpp"
#include "AbstractImu.hpp"
#include "MockHelper.Hpp"

/**************************************************************************************************
 * Mocked IMU class. Uses a csv file of data to "read" data, simulating raw data input from IMU.
 *************************************************************************************************/
class MockImu : public AbstractImu
{
    private:

        MockHelper mockHelper;

        float ax, ay, az;
        float ox, oy, oz;

    public:

        MockImu(MockHelper helper);

        virtual ~MockImu();

        virtual bool init() override;

        virtual Data read(Data data) override;
        virtual Data poll(Data data) override;

        virtual void enable() override;
        virtual void disable() override;

        uint64_t getNumDataPoints();    
};

#endif // __MOCKIMU_HPP__