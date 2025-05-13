#ifndef GRIPPER_HPP
#define GRIPPER_HPP

class Gripper {

    public:
        Gripper();

        int openGripper() const;
        int closeGripper() const;
        bool isGripperOpen() const;
        bool wasSuccesfulGrip() const;
    
    private:
        int currentStep;
        bool isClosed;
        bool isActivelyHolding;
};

#endif