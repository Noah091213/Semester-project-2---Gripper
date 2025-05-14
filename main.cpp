#include <pigpio.h>
#include <iostream>
#include <chrono>
#include <thread>

#include "Gripper.hpp"
#include "functions.hpp"

int main() 
{
    std::cout << "Initializing GPIO library" << std::endl;
    int test = gpioInitialise();
    runTest(test);

    int currentCase = 1;   // Int used to control state machine for testing
    int userInput   = 0;   // Input for calling commands for testing, only call ints

    Gripper mainGripper(13, 12, 26, 0, 1);

    mainGripper.pinInit();

    while (true) {
        switch(currentCase) {

            case 1: // Default case

                std::cout << "Case 1\n" << std::endl;
                
                // Sets all the pins to default
                mainGripper.setOffPinState(1);
                mainGripper.setForwardPinState(0);
                mainGripper.setBackwardPinState(0);

                std::cout << " Type 1 to close gripper \n Type 2 to open gripper \n Type 3 to get the current status \n " << std::endl;
                std::cin >> userInput;

                if (userInput == 1) {       // Calls command to close the gripper
                    mainGripper.closeGripper();
                    currentCase = 2;

                } else if (userInput == 2) {// Calls command to open gripper
                    mainGripper.openGripper();
                    currentCase = 3;

                } else if (userInput == 3) { 
                    currentCase = 4;

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
                
                if (mainGripper.wasSuccesfulGrip() == 1) {
                    std::cout << "The gripper is holding something" << std::endl;
                } else {
                    std::cout << "The gripper is not holding something" << std::endl;
                }
                
                currentCase = 1;
                break;
        }
    }
    
    return 0;
}