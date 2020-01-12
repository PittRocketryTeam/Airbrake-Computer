// #define LOGFILE (char*)"lessdata.csv"

#define MANUAL_MODE true    // Testing flag; set to true when testing, false for automatic mode

/**************************************************************************************************
 * I-1: Target apogee.                                                                  Unit: feet
 *************************************************************************************************/
#define TARGET_APOGEE 3700

/**************************************************************************************************
 * I-2: Range for incremental partial deployments (tolerance around target apogee).     Unit: feet
 * 
 * This is used to control what the system considers apogee. Apogee, to the system, is 
 * TARGET_APOGEE +/- PARTIAL_DEPLOYMENT_RANGE, e.g. if target apogee is 3700 feet, the system 
 * considers anything between 3695 and 3905 to be apogee.
 *************************************************************************************************/
#define PARTIAL_DEPLOYMENT_RANGE 5  

/**************************************************************************************************
 * I-3: Range for immediate full deployment.                                            Unit: feet
 * 
 * This is used to control the range where the air brake will immediately deploy. For example, if
 * target apogee is 3700 feet, if the air brake system detects that it's between 3675 and 3725
 * feet, it will trigger immediate 100% deployment of the air brake.
 *************************************************************************************************/
#define IMMEDIATE_DEPLOYMENT_RANGE 25

/**************************************************************************************************
 * I-4: Rate of data sampling for sensors.                                              Unit: Hertz
 *************************************************************************************************/
// #define DATA_SAMPLING_RATE 60

/************************************************************************************************** 
 * I-5: Offset for altimeter reading to calibrate altimeter to match stratologger.      Unit: feet
 * 
 * This is used to account for the fact that NASA's altitude determination is made using the 
 * stratologger, not the air brake altimeter, so the air brake altimeter should be calibrated to
 * stratologger to ensure that it's trying to optimize the apogee reading that actually matters
 * for the competition.
 *************************************************************************************************/ 
#define ALT_CALIBRATION_OFFSET 2

/************************************************************************************************** 
 * I-6: Data acquisition threshold (change in height since motor burnout).              Unit: feet
 * 
 * This is one of the parameters that is used to set the data acquisition threshold. It defines
 * the height since motor burnout detection when enough data has been collected. For example, if
 * this value is 50, that means at least 50 feet mush be gained over the altiude at which motor 
 * burnout was completed.
 *************************************************************************************************/ 
#define DAQ_THRESHOLD_ALTITUDE 50

/************************************************************************************************** 
 * I-6: Data acquisition threshold (# data points collected since motor burnout).       Unit: feet
 * 
 * This is one of the parameters that is used to set the data acquisition threshold. It defines
 * the number of data points collected since motor burnout detection when enough data has been 
 * collected. For example, if this value is 50, that means at least 50 feet mush be gained over 
 * the altiude at which motor burnout was completed.
 *************************************************************************************************/ 
#define DAQ_THRESHOLD_DATA_POINTS

/**************************************************************************************************
 * Lower bound of partial deployment range.                                             Unit: feet
 *************************************************************************************************/
#define PARTIAL_DEPLOYMENT_LOWER_BOUND (TARGET_APOGEE - PARTIAL_DEPLOYMENT_RANGE)

/**************************************************************************************************
 * Upper bound of partial deployment range.                                             Unit: feet
 *************************************************************************************************/
#define PARTIAL_DEPLOYMENT_UPPER_BOUND (TARGET_APOGEE + PARTIAL_DEPLOYMENT_RANGE)

/**************************************************************************************************
 * Lower bound of immediate deployment range.                                           Unit: feet
 *************************************************************************************************/
#define IMMEDIATE_DEPLOYMENT_LOWER_BOUND (TARGET_APOGEE - IMMEDIATE_DEPLOYMENT_RANGE)

/**************************************************************************************************
 * Upper bound of immediate deployment range.                                           Unit: feet
 *************************************************************************************************/
#define IMMEDIATE_DEPLOYMENT_UPPER_BOUND (TARGET_APOGEE + IMMEDIATE_DEPLOYMENT_RANGE)

/************************************************************************************************** 
 * Height of air brake blades when 100% deployed.                                     Unit: inches
 *************************************************************************************************/ 
#define AIRBRAKE_MAX_HEIGHT 0.74

/************************************************************************************************** 
 * Total surface area of air brake when 100% deployed.                         sUnit: square inches
 *************************************************************************************************/ 
#define TOTAL_AIRBRAKE_SURFACE_AREA 28.3 
