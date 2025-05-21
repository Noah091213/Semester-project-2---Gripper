#include "Gripper.hpp"
#include "functions.hpp"

#include <chrono>
#include <thread>
#include <iostream>
#include <pigpio.h>

// Constructor:

Gripper::Gripper(unsigned int forward, unsigned int backward, unsigned int off, unsigned int buttonZ, unsigned int buttonC) {
    currentStep = 0;          // Variable used to meassure how closed the gripper is. 0 is all the way open and pressing the zero button
    isClosed = 0;             // Var to check if the gripper is currently closed

    buttonClose = buttonC;    // Button for detecting if the gripper closed on something
    buttonZero  = buttonZ;    // Button for zeroing/opening the gripper
    outOFF      = off;        // Output to disable the H bridge
    outForward  = forward;    // Output to turn H bridge/motor forward
    outBackward = backward;   // Output to turn H bridge/motor in reverse
}


// Methods:


void Gripper::pinInit() {   // Method to init all pins together, this is done through a method to encapsulate all aspects of the gripper in the class

    std::cout << "Initializing In/Out pins" << std::endl;   // Debug print
    setPinInput(buttonClose);   
    setPinInput(buttonZero);
    setPinOutput(outOFF);
    setPinOutput(outForward);
    setPinOutput(outBackward);
}



void Gripper::openGripper() {

    std::cout << "Opening gripper" << std::endl;    // Debug print

    gpioWrite(outOFF, PI_ON);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    gpioWrite(outOFF, PI_OFF);      // Set disable pin to low, allowing control through H-bridge
    gpioWrite(outForward, PI_OFF);  // Sets forward pin to low, opening needs to go backwards
    gpioWrite(outBackward, PI_ON);  // Sets backward pin to high, to open the gripper

    std::cout << "Steps are "<< currentStep << std::endl;   
    currentStep += 300; // To make sure the gripper is zeroed we add a lot of steps, to keep it running until it hits the button

    std::cout << "Button zero is currently " << gpioRead(buttonClose) << std::endl; // Debug print

    while (gpioRead(buttonZero) == 0 && currentStep >= 0) {         // Keep driving the motor until the button is pressed or it has been running for longer than it should need and steps have reached 0
        std::cout << "Opening "<< currentStep << std::endl;         // Debug print
        currentStep--;                                              // For every loop we subtract one from steps to keep count
        std::this_thread::sleep_for(std::chrono::milliseconds(5)); // Sleep for 5 miliseconds, this allows the program to acount steps roughly every 10 miliseconds, may change if motor drives too fast
    }

    currentStep = 0;    // Because the button should now have been pressed, reset currentStep to zero
    std::cout << "Zero achieved! Current step is: "<< currentStep << std::endl;

    isClosed = false;   // Set the gripper to be open if checked

    //gpioWrite(outOFF, PI_ON);       // Disable the H-bridge
    gpioWrite(outBackward, PI_OFF); // Disable the backwards movement
}



void Gripper::closeGripper() {  // Method to close the gripper
    
    std::cout << "Closing gripper" << std::endl;    // Debug print

    gpioWrite(outOFF, PI_ON);   
    std::this_thread::sleep_for(std::chrono::milliseconds(200));


    gpioWrite(outOFF, PI_OFF);      // Set disable pin to low, allowing control through H-bridge
    gpioWrite(outForward, PI_ON);   // Sets forward pin to high, to close the gripper
    gpioWrite(outBackward, PI_OFF); // Sets backward pin to low, closing needs to go forwards 

    std::cout << "Button close is currently " << gpioRead(buttonClose) << std::endl;    // Debug print

    while (gpioRead(buttonClose) == 0 && currentStep <= 160) {      // Keep running until the button hits something, or steps reach a point where the gripper is fully closed. The steps here need to be calibrated with PWM signal
        std::cout << "Closing "<< currentStep << std::endl;         // Debug print
        currentStep++;                                              // Add a step for every loop to keep track of location
        std::this_thread::sleep_for(std::chrono::milliseconds(5)); // Sleep for 5 miliseconds, this allows the program to acount steps roughly every 10 miliseconds, may change if motor drives too fast
    }

    if (gpioRead(buttonClose) == 1) {
        std::cout << "Closed with button pressed" << std::endl;
    } else {
        std::cout << "Closed without button pressed" << std::endl;
        gpioWrite(outOFF, PI_ON);
        gpioWrite(outBackward, PI_OFF);
    }

    isClosed = true;    // Set the gripper to be closed if checked

    gpioWrite(outForward, PI_OFF);  // Disable the forward move
    if (currentStep <= 140) {       // If the gripper managed to take more than 140 steps (subject to change) the gripper managed to close past where an object would realistically be, thus set isActivelyHolding to true
        isActivelyHolding = true;
    } else {                        // Else the gripper closed past and didnt grab anything
        isActivelyHolding = false;
    }
}



bool Gripper::isGripperOpen() const {   // Getter for current status of the gripper
    return isClosed;
}

bool Gripper::wasSuccesfulGrip() const {// Getter for whether or not the gripper is holding something
    return isActivelyHolding;
}

void Gripper::setForwardPinState(bool setOn ) {   // Setter for debugging to manually set pins high or low
    gpioWrite(outForward, setOn); 
}

void Gripper::setBackwardPinState(bool setOn ) {  // Setter for debugging to manually set pins high or low
    gpioWrite(outBackward, setOn); 
}

void Gripper::setOffPinState(bool setOn ) {       // Setter for debugging to manually set pins high or low
    gpioWrite(outOFF, setOn); 
}

