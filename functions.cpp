#include <pigpio.h>
#include <iostream>

// Define a pin as input
void setPinInput(int name*) {
    int gpioTest = 0;
    gpioTest = gpioSetMode(name, PI_INPUT);
    runTest(gpioTest);
}

// Define a pin as output
void setPinOutput(int name*) {
    int gpioTest = gpioSetMode(name, PI_OUTPUT);
    runTest(gpioTest);
}

// Check if pigpio errors occur, must be used because runtime errors have no checks in library
void runTest(int toTest) {
    if (toTest == PI_INIT_FAILED) {
        std::cout << "ERROR" << toTest << std::endl;
    }
}