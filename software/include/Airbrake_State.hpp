/**************************************************************************************************
 * Defines the current state of the air brake.
 *************************************************************************************************/ 
enum Airbrake_State
{
    /**********************************************************************************************
     * Prior to launch detection. 0% deployment.
     *********************************************************************************************/ 
    START,   

    /**********************************************************************************************
     * Launch has been detected; prior to motor burnout. 0% deployment.
     *********************************************************************************************/            
    LAUNCH_DETECTED,

    /**********************************************************************************************
     * Launch and motor burnout detected; DAQ threshold not met. 0% deployment.
     *********************************************************************************************/ 
    BURNOUT_DETECTED,  

    /**********************************************************************************************
     * Launch, motor burnout, and DAQ thresholds met. With 0 to 100% deployment
     *********************************************************************************************/ 
    DAQ_THRESHOLD_MET_ACTIVE_ADJUST, 

    /**********************************************************************************************
     * Air brake retraction to 0% state; following apogee. 0% deployment.
     *********************************************************************************************/ 
    DESCENT_DETECTED,  

    /**********************************************************************************************
     * Air brake has retracted to 0% state and is no longer doing anything. 0% deployment.
     *********************************************************************************************/   
    TERMINATION        
};