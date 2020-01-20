#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "helper.h"

class Player;

class Controller {
    private:
        int _CPUNo = 0;
        int _humanNo = 0;

        static Controller* _inst;
    public:
        std::vector<Player*> players;
        std::vector<int> ships;

        State state = MENU;
        
        void setup();
        void addHuman(int humanNo);
        void addCPU(int cpuNo);
        void shoot();

        static Controller* getInstance();

        int getCPUNo() {return _CPUNo;};
        int getHumanNo() {return _humanNo;};
};

#endif