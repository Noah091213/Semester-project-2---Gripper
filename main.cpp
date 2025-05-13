#include <pigpio.h>
#include <iostream>
#include <chrono>
#include <thread>

#include "Gripper.hpp"
#include "functions.hpp"

int main() 
{
    // Define input and output pins
    static unsigned int ButtonClose = 0;    // Button for detecting if the gripper closed on something
    static unsigned int ButtonZero  = 0;    // Button for zeroing/opening the gripper
    static unsigned int OutOFF      = 0;    // Output to disable the H bridge
    static unsigned int OutForward  = 12;    // Output to turn H bridge/motor forward
    static unsigned int OutBackward = 13;    // Output to turn H bridge/motor in reverse
    
    std::cout << "Initializing GPIO pins" << std::endl;
    runTest(gpioInitialise());

    std::cout << "Initializing In/Out pins" << std::endl;
    setPinInput(ButtonClose);
    setPinInput(ButtonZero);
    setPinOutput(OutOFF);
    setPinOutput(OutForward);
    setPinOutput(OutBackward);

    int currentCase = 1;   // Int used to control state machine for testing
    int userInput = 0;      // Input for calling commands for testing, only call ints
    
    while (true) {
        switch(currentCase) {

            case 1: // Default case

                std::cout << "Case 1\n" << std::endl;
                // Sets all the pins to default
                gpioWrite(OutOFF, PI_ON);
                gpioWrite(OutForward, PI_OFF);
                gpioWrite(OutBackward, PI_OFF);

                std::cout << " Type 1 to close gripper \n Type 2 to open gripper \n Type 3 to get the current status \n " << std::endl;
                std::cin >> userInput;

                if (userInput == 1) {       // Calls command to close the gripper
                    currentCase = 2;

                } else if (userInput == 2) {// Calls command to open gripper
                    currentCase = 3;

                } else {
                    std::cout << "Please enter a valid option.\n\n" << std::endl;
                }

                break;

            case 2: // Close gripper case

                currentCase = 1;
                break;

            case 3: // Open gripper case

                currentCase = 1;
                break;

            case 4: // Get the current state of the grippers success
                
                if (Gripper.wasSuccesful() == 1) {
                    std::cout << "The gripper is holding something" std::endl;
                } else {
                    std::cout << "The gripper is not holding something" std::endl;
                }
                
                currentCase = 1;
                break;
        }
    }
    
    return 0;
}