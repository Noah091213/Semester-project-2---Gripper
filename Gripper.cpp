#include "Gripper.hpp"

#include <pigpio.h>

// Constructor:
Gripper::Gripper() {
    currentStep = 0;
    isClosed = 0;
}

// Methods:

int Gripper::closeGripper() const {

}

int Gripper::openGripper() const {
    
}

bool Gripper::isGripperOpen() const {
    return isClosed;
}

bool Gripper::wasSuccesfulGrip() const {
    return isActivelyHolding;
}

