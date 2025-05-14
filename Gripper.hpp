#ifndef GRIPPER_HPP
#define GRIPPER_HPP

class Gripper {

    public:
        Gripper(unsigned int forward, unsigned int backward, unsigned int off, unsigned int buttonZ, unsigned int buttonC);

        void pinInit();
        void openGripper();
        void closeGripper();
        bool isGripperOpen() const;
        bool wasSuccesfulGrip() const;
        void setForwardPinState(bool setOn);
        void setBackwardPinState(bool setOn);
        void setOffPinState(bool setOn);
    
        

    private:
        int currentStep;
        bool isClosed;
        bool isActivelyHolding;

        unsigned int buttonClose;     // Button for detecting if the gripper closed on something
        unsigned int buttonZero;      // Button for zeroing/opening the gripper
        unsigned int outOFF;          // Output to disable the H bridge
        unsigned int outForward;      // Output to turn H bridge/motor forward
        unsigned int outBackward;     // Output to turn H bridge/motor in reverse
        
};

#endif