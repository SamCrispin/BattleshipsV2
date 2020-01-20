#include "cpu.h"

CPU::CPU(std::string name, Difficulty difficulty) : Player(name) {
    _difficulty = difficulty;
}

Pos CPU::easy() {
    Pos pos;

    do {
        pos.x = rand() % 10;
        pos.y = rand() % 10;
    } while (board[pos.y][pos.x].hit);

    return pos;
}

Pos CPU::med() {
    Pos pos;



    return pos;
}

Pos CPU::hard() {
    Pos pos;



    return pos;
}

Pos CPU::genShotLocation() {
    Pos pos;

    switch (_difficulty) {
        case EASY: pos = easy(); break;
        case MED: pos = med(); break;
        case HARD: pos = hard(); break;
    }
    
    return pos;
}

void CPU::setDifficulty(Difficulty difficulty) {
    _difficulty = difficulty;
}

int CPU::getTarget() {
    return 1;
}