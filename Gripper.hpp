#ifndef GRIPPER_HPP
#define GRIPPER_HPP

class Gripper {

    public:
        Gripper(unsigned int forward, unsigned int backward, unsigned int off, unsigned int buttonZ, unsigned int buttonC);

        void pinInit();                         // Method to set up all the pins for the gripper
        void openGripper();                     // Method to open the gripper, simply call and the code does the rest
        void closeGripper();                    // Method to close the gripper, simply call and the code does the rest
        bool isGripperOpen() const;             // Getter to check if the gripper is open
        bool wasSuccesfulGrip() const;          // Getter to see if the gripper is holding something, it can be closed without holding anything
        void setForwardPinState(bool setOn);    // Manuel setter for forward pin, mainly used for debugging
        void setBackwardPinState(bool setOn);   // Manuel setter for backwards pin, mainly used for debugging
        void setOffPinState(bool setOn);        // Manuel setter for disable pin, mainly used for debugging
    
        

    private:
        int currentStep;            // Step counter to keep track of the gripper and how closed it is
        bool isOpen;              // Bool is true if the gripper is closed
        bool isActivelyHolding;     // Bool is true if the gripper is holdingh something

        unsigned int buttonClose;   // Button for detecting if the gripper closed on something
        unsigned int buttonZero;    // Button for zeroing/opening the gripper
        unsigned int outOFF;        // Output to disable the H bridge
        unsigned int outForward;    // Output to turn H bridge/motor forward
        unsigned int outBackward;   // Output to turn H bridge/motor in reverse
        
};

#endif