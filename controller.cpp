#include "helper.h"
#include "controller.h"
#include "players/human.h"
#include "players/cpu.h"
#include "players/player.h"

Controller* Controller::_inst = NULL;

void Controller::setup() {
    std::string input;
    std::regex inputRE("[1-3]{1}h?");
    std::string outputMsg = "Welcome to BattleShips!!!\n\n" 
        "What kind of game do you want to play? (Type in 1-3) \n"
        "  1. Standard game\n"
        "  2. Custom ship game\n"
        "  3. Custom cell game\n\n"
        "To see more about an option, type 'h' after the option number (e.g. '2h')";
    
    do {
        input = getInput(outputMsg, inputRE, "Please choose one of the given options (1-3 with or without 'h')");
        if (input.size() == 1) {
            //compile time casting of int to an enum to get the nth term in an enum
            state = static_cast<State>(input[0]-48);
        } else {
            switch (input[0]) {
                case '1': 
                    std::cout << "This is a regular game of BattleShips. Each player has 5 ships, one 2 length ship, two 3 length ships, a 4 length and a 5 length. You place your ships horizontally/veritcally and try to sink your opponents (however many there may be) ships.\n";
                    break;
                case '2':
                    std::cout << "This is a game of BattleShips where you control what ships each player has. The max size ship is still 5 but you can have as many of each ship as you want, each player still has the same ships\n";
                    break;
                case '3':
                    std::cout << "This is a even more customisable game. You control the total amount of cells that will be taken up by ships, and then each player decides how to distribute their cells between their ships. A standard game has 17 cells, an example custom game could be where you have 20 cells and one player chooses to have four 5 length ships, one chooses one 2 length ship, three 3 length ships, a 4 legnth and a 5 length. Each player has the same amount of cells taken up by ships, just distributed differently depending on how each player chooses.\n";
                    break;
            }
        }
    } while (state == MENU);

    std::regex playerNoRE("[0-9]{1}");
    std::string err = "Please choose a number between 0 and 9 inclusive";
    int shipNo = 0;
    std::regex cellsRE("[0-9]{2}");
    int cells = 0;

    do {
        _humanNo = getInput("How many human players do you want? (Min: 0, max: 9)", playerNoRE, err)[0] - 48;
        _CPUNo = getInput("How many CPU players do you want? (Min: 0, max: 9)", playerNoRE, err)[0] - 48;
        if (_humanNo + _CPUNo == 0) std::cout << "Total amount of players must be greater than 0\n";
    } while (_humanNo + _CPUNo == 0);

    for (int i = 0; i < _humanNo; i++) addHuman(i);
    for (int i = 0; i < _CPUNo; i++) addCPU(i);

    if (state == CUSTOM_SHIP_GAME) {
        do {
            ships.clear();
            std::cout << "The total cells taken up by ships must total 100 or less\n";
            for (int i = 2; i <= 5; i++) {
                outputMsg = "How many " + std::to_string(i) + " length ships do you want each player to have? (Min: 0, max: 9)";
                shipNo = getInput(outputMsg, playerNoRE, err)[0] - 48;
                for (int j = 0; j < shipNo; j++) ships.push_back(i);
            }
        } while (std::accumulate(ships.begin(), ships.end(), 0) > 100);

        for (int i = 0; i < players.size(); i++) {
            players[i]->shipLengths = ships;
        }

    } else if (state == CUSTOM_CELL_GAME) {
        do {
            cells = std::stoi(getInput("How many cells do you want to each player to have? (Min: 2, max: 99", cellsRE, "Please enter a number between 2 and 99 inclusive"));
        } while (cells < 2 || cells > 99);

        for (int i = 0; i < players.size(); i++) {

        }
    }

    for (int i = 0; i < players[0]->shipLengths.size(); i++) {
        std::cout << std::to_string(players[0]->shipLengths[i]) << std::endl;
    }

    for (int i = 0; i < players.size(); i++) {
        players[i]->setupShips();
    }
}

void Controller::addHuman(int humanNo) {
    std::regex nameRE("[a-zA-Z0-9 ]+");
    std::string name = getInput("Player " + std::to_string(humanNo + 1) + " choose your name" , nameRE, "Please choose a name that only includes letters, numbers and spaces");
    players.push_back(new Human(name));
}

void Controller::addCPU(int cpuNo) {
    std::regex diffRE("[1-3]{1}");
    std::string outputStr = "Choose CPU " + std::to_string(cpuNo + 1) + "'s difficulty setting\n"
        "  1. Easy\n"
        "  2. Medium\n"
        "  3. Hard";
    Difficulty difficulty = static_cast<Difficulty>(getInput(outputStr, diffRE, "Please choose between 1 and 3 inclusive")[0] - 48);
    players.push_back(new CPU("CPU" + std::to_string(cpuNo + 1), difficulty));
}

void Controller::shoot() {
    for (int i = 0; i < players.size(); i++) {
        players[i]->shoot();
    }
}

Controller* Controller::getInstance() {
    if (Controller::_inst == NULL) Controller::_inst = new Controller;
    return Controller::_inst;
}