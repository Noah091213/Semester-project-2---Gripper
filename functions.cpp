#include <pigpio.h>
#include <iostream>
#include "functions.hpp"


// Check if pigpio errors occur, must be used because runtime errors have no checks in library
void runTest(int toTest) {
    if (toTest == PI_INIT_FAILED) {
        std::cout << "ERROR" << toTest << std::endl;
    } else {
        std::cout << "Pin passed test" << std::endl;
    }
}

// Define a pin as input
void setPinInput(unsigned int name) {
    int gpioTest = 0;
    gpioTest = gpioSetMode(name, PI_INPUT);
    runTest(gpioTest);  // Checking if the pin was set up correctly
}

// Define a pin as output
void setPinOutput(unsigned int name) {
    int gpioTest = 0;
    gpioTest = gpioSetMode(name, PI_OUTPUT);
    runTest(gpioTest);  // Checking if the pin was set up correctly
}


