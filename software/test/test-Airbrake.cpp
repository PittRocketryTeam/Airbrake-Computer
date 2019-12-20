#include <Arduino.h>
#include <unity.h>

// Class under test
#include "Airbrake.cpp"

// Object under test
Airbrake airbrake;

void setUp(void) 
{
    // set stuff up here;
}

void tearDown(void) 
{
    // clean stuff up here
}

void test_setAbsoluteDeployment(void) 
{
    int expected = 50;

    // Deploy airbrake to 50%
    airbrake.setAbsoluteDeployment(expected);

    int actual = airbrake.getDeploymentPercentage();

    TEST_ASSERT_EQUAL(expected, actual);
}

void test_deployCompletely(void) 
{
    int expected = 100;

    airbrake.deployCompletely();

    int actual = airbrake.getDeploymentPercentage();

    TEST_ASSERT_EQUAL(expected, actual);
}

void test_retractCompletely(void) 
{
    int expected = 0;

    airbrake.retractCompletely();

    int actual = airbrake.getDeploymentPercentage();
    
    TEST_ASSERT_EQUAL(expected, actual);
}

void setup() 
{
    delay(2000);

    UNITY_BEGIN();    // IMPORTANT LINE!
}

void loop() 
{

    RUN_TEST(test_setAbsoluteDeployment);

    RUN_TEST(test_deployCompletely);

    RUN_TEST(test_retractCompletely);

    UNITY_END(); // stop unit testing
}