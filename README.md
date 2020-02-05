# Airbrake-Computer
Code for the dedicated airbrake computer on the vehicle

LaunchVehicle methods: 
    (a) Descent detection: This method will primarily look at the altimeter data and its altitude readings. 
        (i) Global variables:
            1.  long highest_alt ---> Keeps track of the highest recorded altitude
            2.  bool hasMax ----> A flag that indicates that highest_alt has been initialized
            3.  int isConsistent ---> A counter that will increment each time a descent has been detected
        (ii) Implementation:
            In each iteration, the method will poll the altitmeter's altitude data. The data will be compared
            to the highest_alt global variable. If the altitude data in that method call is less than the 
            highest_alt global variable, this will assume that the rocket has made a descent. To verify that 
            the launch vehicle has descended, the isConsistent global variable will be incremented by one. 
            The counter will have a certain threshold, a max value. Once the threshold has been reached, 
            the method will finally return true to state that the descent has been detected.  