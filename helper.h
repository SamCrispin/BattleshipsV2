#ifndef HELPER_H
#define HELPER_H

#include <vector>
#include <iostream>
#include <string>
#include <iomanip>
#include <random>
#include <memory>
#include <regex>
#include <numeric>

const int BOARD_SIZE = 10;

struct Cell {
    bool hit = false;
    int ship = 0;
    int density = 0;
};

struct Pos {
    int x;
    int y;
};

enum Difficulty {EASY, MED, HARD};

enum State {MENU, STANDARD_GAME, CUSTOM_SHIP_GAME, CUSTOM_CELL_GAME};

const std::string STANDARD_GAME_SHIPS[5] = {
    "Patrol Boat",
    "Submarine",
    "Destroyer",
    "BattleShip",
    "Aircraft Carrier"
};

const int STANDARD_GAME_SHIP_LENGTHS[5] = {2, 3, 3, 4, 5};

const std::regex X_COORD_RE("[A-Ja-j]{1}");
const std::regex Y_COORD_RE("[0-9]{1}");

std::string getInput(std::string outputMessage, std::regex regex, std::string err);
bool cellOnBoard(Pos pos);

#endif