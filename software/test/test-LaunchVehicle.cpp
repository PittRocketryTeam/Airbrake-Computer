#include <Arduino.h>
#include <unity.h>

// Class under test
#include "LaunchVehicle.cpp"

// Object under test
LaunchVehicle launch_vehicle;

void setUp(void) 
{
    // set stuff up here;
}

void tearDown(void) 
{
    // clean stuff up here
}

void setup() 
{
    delay(2000);

    UNITY_BEGIN();    // IMPORTANT LINE!
}

void loop() 
{

    RUN_TEST(test_descentDetection); 

    UNITY_END(); // stop unit testing
}