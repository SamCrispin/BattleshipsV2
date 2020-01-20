#include "human.h"

Human::Human(std::string name) : Player(name) {}

Pos Human::genShotLocation() {
    Pos pos;
    bool valid;

    do {
        pos.x = tolower(getInput("Choose X coord: ", X_COORD_RE, "Not a valid X coord").at(0)) - 97;
        pos.y = tolower(getInput("Choose Y coord: ", Y_COORD_RE, "Not a valid Y coord").at(0)) - 48;

        valid = cellOnBoard(pos) && !getCell(pos).hit;
    } while (!valid);
    return pos;
}

int Human::getTarget() {
    return 0;
}