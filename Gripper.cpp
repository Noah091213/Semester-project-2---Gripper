#include "Gripper.hpp"
#include "functions.hpp"

#include <chrono>
#include <thread>
#include <iostream>
#include <pigpio.h>

// Constructor:

Gripper::Gripper(unsigned int forward, unsigned int backward, unsigned int off, unsigned int buttonZ, unsigned int buttonC) {
    currentStep = 0;
    isClosed = 0;

    buttonClose = buttonC;    // Button for detecting if the gripper closed on something
    buttonZero  = buttonZ;    // Button for zeroing/opening the gripper
    outOFF      = off;        // Output to disable the H bridge
    outForward  = forward;    // Output to turn H bridge/motor forward
    outBackward = backward;   // Output to turn H bridge/motor in reverse
}

// Methods:

void Gripper::pinInit() {

    std::cout << "Initializing In/Out pins" << std::endl;
    setPinInput(buttonClose);
    setPinInput(buttonZero);
    setPinOutput(outOFF);
    setPinOutput(outForward);
    setPinOutput(outBackward);
}

void Gripper::openGripper() {
    gpioWrite(outOFF, PI_OFF);
    gpioWrite(outForward, PI_OFF);
    gpioWrite(outBackward, PI_ON);

    std::cout << "Steps are "<< currentStep << std::endl;
    currentStep += 300;

    while (/*buttonZero == 0 &&*/ currentStep >= 0) {
        std::cout << "Opening "<< currentStep << std::endl;
        currentStep--;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    currentStep = 0;
    std::cout << "Zero achieved!"<< currentStep << std::endl;
}

void Gripper::closeGripper() {
    
    gpioWrite(outOFF, PI_OFF);
    gpioWrite(outForward, PI_ON);
    gpioWrite(outBackward, PI_OFF);

    while (buttonClose == 0 && currentStep <= 200) {
        std::cout << "Closing "<< currentStep << std::endl;
        currentStep++;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    gpioWrite(outForward, PI_OFF);
    gpioWrite(outOFF, PI_ON);

    if (currentStep >= 1700) {
        isActivelyHolding = true;
    } else {
        isActivelyHolding = false;
    }
}

bool Gripper::isGripperOpen() const {
    return isClosed;
}

bool Gripper::wasSuccesfulGrip() const {
    return isActivelyHolding;
}

void Gripper::setForwardPinState(bool setOn ) {
    gpioWrite(outForward, setOn); 
}

void Gripper::setBackwardPinState(bool setOn ) {
    gpioWrite(outBackward, setOn); 
}

void Gripper::setOffPinState(bool setOn ) {
    gpioWrite(outOFF, setOn); 
}

