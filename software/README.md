# Airbrake (VDS) Software
## 1. Overview

This software was designed to run on a Teensy 3.6 in support of the 2019-2020 Pitt SOAR variable drag system (VDS) airbrake for the full scale NASA USLI launch vehicle. The purpose of the airbrake is to control the launch vehicle's apogee to try to get the vehicle as close to its declared target apogee as possible.

It consists of a finite state machine driven by a deployment algorithm consisting of a number of parameters. 'Parameters’ are aspects of the model which can be independently modified to alter the performance of what is called the 'main algorithm', which is the program flow for the main function. 

Integer parameters are static values whereas sub-algorithms are pieces of functionality. The division of the main algorithm into sub-algorithm is to enable ease of testing and to identify independent functionality which can be reused elsewhere on the vehicle. Sub-algorithms which are more difficult to test feature simpler implementations to make testing and verification easier. 

The primary design goals of this software (aside from supporting the mission of the airbrake) are: 

1. __Fail safely.__ Under no circumstances should the airbrake's operation lead to the failure of a launch. This means all operations err on the side of doing nothing (e.g. the system never detects launch where the was no launch event, but it ight fail to detect a launch where there was a launch event).

2. __Make testing easy.__ Due to the aforementioned safety-critical nature of airbrake software, all software has been designed in discrete units that are easily testable. Interfaces were written with testing in mind.

3. __Promote code reuse.__ This is just one of several software projects for Pitt SOAR's 2019-2020 USLI vehicle, and several other software projects use similar functionality. Heavy emphasis was placed on reusing software from other projects and on making new software reusable elsewhere.

Beyond design goals, success is defined as the launch vehicle achieving within 70 feet of its target apogee, regardless of whether or not the airbrake blades ever deploy during flight. Shown below is a formalize definition of how success is defined for airbrake operation.

![success-determination](success-determination.png)

## 2. Sub-Algorithm Descriptions

### 2.1 SA-1: Determination of Launch Detection

TODO: Add description

### 2.2: SA-2 Determination of Motor Burnout

TODO: Add description

### 2.3: SA-3: Airbrake Deployment Incrementation Algorithm

TODO: Add description

### 2.4: SA-4: Apogee Prediction

TODO: Add description

### 2.5: SA-5: Determination of Descent Detection

TODO: Add description

## 3. Project Structure

* `src` - source files
* `include` - header files
* `lib` - external libraries
* `test` - unit tests
* `data` - data files to supply mocked sensors with data

## 4. Collaboration Process

TODO: Add details about branch usage and merging

## 5. Build Configurations

In order to fly and test the same code, there are several flags that are set to modify the behavior of the code. Below, the different build configurations for flight and test are explained. 

### 5.1. Flight Build

The flight build (what flies on the full scale vehicle) should have the following flags set:

| Flag          | Value         | Explanation                                              |
|:-------------:|:-------------:|:--------------------------------------------------------:|
| VERBOSE       | false         | Limit I/O to allocate more resources towards computation |
| MANUAL_MODE   | false         | Disable manual intervention and mock sensors             |

All flight builds must uncomment the line `build_flags = -Wall -Wextra -Werror`.

### 5.2. Test Build

The test build (what's used during testing and __SHOULD NOT BE FLOWN__ can have the `VERBOSE` and `MANUAL_MODE` flags set to whatever is desirable for testing. Note that `MANUAL_MODE = true` enables the mock sensors.

## 6. Basic Style Guidelines

For the sake of consistency, this repo uses the following coding standards: 

* Brackets should be on their own lines, and ALL conditional statements and loops must have brackets, like this: 

```c++
if(initAlt == -1) 
{
    Serial.println("Cannot poll altitude --- ground pressure not yet set!");
}
else
{
    data.altimeterData.altitude = bmp.readAltitude(initAlt);
}
```

* Each function's definition belongs in a header file and should have a block comment with Javadoc-style annotations, like this:

```c++
/******************************************************************************************
 * Initialize vehicle and sensors. Accepts an IMU and Altimeter objects so these sensors
 * can be mocked.
 * 
 * @param AbstractImu imu object (or mock)
 * @param AbstractAltimeter altimeter object (or mock)
 *****************************************************************************************/
void init(AbstractImu* i, AbstractAltimeter* a);
```

* Any constants (aside from -1, 0, and 1) should be named and should feature a block comment with a description of the constant, its intended use, and its imperial units (if relevant), like this:

```c++
/**************************************************************************************************
 * I-2: Range for incremental partial deployments (tolerance around target apogee).     Unit: feet
 * 
 * This is used to control what the system considers apogee. Apogee, to the system, is 
 * TARGET_APOGEE +/- PARTIAL_DEPLOYMENT_RANGE, e.g. if target apogee is 3700 feet, the system 
 * considers anything between 3695 and 3905 to be apogee.
 *************************************************************************************************/
#define PARTIAL_DEPLOYMENT_RANGE 5  
````

* Lines should not exceed 100 characters.

* All code should be compiled with all warnings enabled and reported as errors, using the compiler flags `-Wall -Wextra -Werror` (these are automatically included in the `platform.ini` file, which controls the build process. __These flags must be enabled for all flight builds.__
 
 
## 7. Dev Environment Setup

All development used the PlatformIO extension for Visual Studio Code. Additionally, you need to download the [Teensyduino addon](https://www.pjrc.com/teensy/td_download.html) in order to upload to the Teensy. 

To build the project, run `pio run`. To upload the project to a Teensy board, run `platformio run --target upload`. To view serial output, run `platformio device monitor`.

## 8. Relevant Links

* [Original deployment algorithm documentation](https://docs.google.com/document/d/1qq0nmyqW3g3wkucI6V3XiiaBdJnb-GQawClglQOAYOM/edit#)
* [Sub-algorithm test plan](https://docs.google.com/document/d/130fPIKDiWxRjwC1eHgn8vEJmvnMhvv1aIwvGFC2JZu0/edit)
* [Sub-algorithm test matrix](https://docs.google.com/spreadsheets/d/1-hUiYAFvpETWn4wtxwzF-okXmnx6dhZY2qigwSgHFRo/edit)
