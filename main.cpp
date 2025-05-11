#include <pigpio.h>
#include <iostream>
#include <chrono>
#include <thread>

#include "functions.cpp"

int main() 
{
    // Define input and output pins
    static unsigned int ButtonClose = 0;
    static unsigned int ButtonZero  = 0;
    static unsigned int OutOFF      = 0;
    static unsigned int OutForward  = 0;
    static unsigned int OutBackward = 0;
    
    functions.runTest(gpioInitialise());

    
    
    return 0;
}