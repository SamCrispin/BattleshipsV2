#ifndef CPU_H
#define CPU_H

#include "player.h"

class CPU : public Player {
    private: 
        Difficulty _difficulty;
        Pos easy();
        Pos med();
        Pos hard();
        
    public:
        CPU(std::string name, Difficulty difficulty);
        void setDifficulty(Difficulty difficulty);
        Pos genShotLocation();
        int getTarget();
};

#endif