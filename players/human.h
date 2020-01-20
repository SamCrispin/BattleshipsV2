#ifndef HUMAN_H
#define HUMAN_H

#include "player.h"

class Human : public Player {
    public:
        Human(std::string name);
        Pos genShotLocation();
        int getTarget();
};

#endif