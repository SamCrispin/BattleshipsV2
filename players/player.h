#ifndef PLAYER_H
#define PLAYER_H

#include "../helper.h"

class Controller;

class Player {
    protected:
        std::string _name;
        int _order;
        int _score;
        std::vector<std::vector<Cell> > board;
        int target;

        virtual Pos genShotLocation() {Pos pos; return pos;};
        virtual int getTarget() {return 0;};
        
        virtual bool genShips() {return false;};

        std::vector<std::string> shipNames;

    public:
        static int PLAYER_NO;

        std::vector<int> shipLengths;

        Player(std::string name);

        bool placeShip();
        bool shoot();
        bool moveShip();
        
        bool printBoard(bool self);
        std::string getName();
        int getOrder();
        int getScore();
        Cell& getCell(Pos pos);
        bool shipSunk(Pos pos, int ship);

        bool setupShips();
};

#endif