#ifndef __DATA_HPP__
#define __DATA_HPP__


// Data struct definitions for each sensor and for overall data struct.

/**
 * IMU data.
 */
typedef struct ImuData
{
    // Absolute Orientation (Euler Vector, 100Hz) Three axis orientation data based on a 360° sphere
    float euler_abs_orientation_x;
    float euler_abs_orientation_y;
    float euler_abs_orientation_z;
    
    // Acceleration Vector (100Hz) Three axis of acceleration (gravity + linear motion) in m/s^2
    float acceleration_x;
    float acceleration_y;
    float acceleration_z;
} ImuData;

/**
 * Altimeter data. 
*/
typedef struct AltimeterData
{
    float temperature;
    float pressure;
    float altitude;
} AltimeterData;

/**
 * Overall data struct.
*/
typedef struct Data
{
    long int timestamp;
    AltimeterData altimeterData;
    ImuData imuData;
} Data;

#endif // __DATA_HPP__