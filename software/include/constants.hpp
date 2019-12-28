// #define LOGFILE (char*)"lessdata.csv"

#define MANUAL_MODE false    // Testing flag; set to true when testing, false for automatic mode

/**************************************************************************************************
 * I-1: Target apogee.                                                                  Unit: feet
 *************************************************************************************************/
#define TARGET_APOGEE 3700

/**************************************************************************************************
 * I-2: Range for incremental partial deployments.                                      Unit: feet
 *************************************************************************************************/
#define PARTIAL_DEPLOYMENT_RANGE 5  

/**************************************************************************************************
 * I-3: Range for immediate full deployment.                                            Unit: feet
 *************************************************************************************************/
#define IMMEDIATE_DEPLOYMENT_RANGE 25

/**************************************************************************************************
 * I-4: Rate of data sampling for sensors.                                              Unit: Hertz
 *************************************************************************************************/
#define DATA_SAMPLING_RATE 60

/************************************************************************************************** 
 * I-5: Offset for altimeter reading to calibrate altimeter to match stratologger.      Unit: feet
 *************************************************************************************************/ 
#define ALT_CALIBRATION_OFFSET 2

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
