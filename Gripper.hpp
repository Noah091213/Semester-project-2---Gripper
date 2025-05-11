#ifndef USER_H
#define USER_H

class User {
    public:
        int openGripper() const;
        int closeGripper() const;
        bool isGripperOpen() const;
        int wasSuccesfulGrip() const;
    private:
        int currentPWM;
};


#endif