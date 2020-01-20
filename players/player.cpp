#include "player.h"
#include "../controller.h"

Controller* game = Controller::getInstance();

int Player::PLAYER_NO = 0;

Player::Player(std::string name) {
    _name = name;
    _order = Player::PLAYER_NO;
    _score = 0;

    board = std::vector<std::vector<Cell> >(BOARD_SIZE, std::vector<Cell>(BOARD_SIZE));

    Player::PLAYER_NO++;
}

bool Player::shoot() {
    int target;
    std::cout << _name << "'s turn" << std::endl;

    if (Player::PLAYER_NO > 2) target = getTarget();
    else if (Player::PLAYER_NO == 2) target = _order ? 0 : 1;
    else target = _order;

    game->players[target]->printBoard(false);
    
    Pos pos;
    do {
        pos = genShotLocation();
    } while (game->players[target]->getCell(pos).hit);
    
    std::cout << _name << " shot at x: " << pos.x << ", y: " << pos.y << std::endl;

    Cell& cell = game->players[target]->getCell(pos);

    if (cell.ship > 0) {
        if (shipSunk(pos, cell.ship)) {
            
        }
    }
    cell.hit = true;
    game->players[target]->printBoard(false);
    return false;
}

bool Player::placeShip() {
    return false;
}

bool Player::moveShip() {
    return false;
}

bool Player::printBoard(bool self) {
    Pos pos;
    std::cout << ((self) ? "Your" : (_name + "'s")) << " board" << std::endl;
    std::cout << "     ";
    for (int i = 0; i < BOARD_SIZE; i++) {
        std::string s1;
        s1 = (char) (i + 65);
        std::cout << s1 << "   ";
    }
    std::cout << std::endl;

    for (int i = 0; i < BOARD_SIZE; i++) {
        std::cout << std::setw(2) << i << " | ";
        for (int j = 0; j < BOARD_SIZE; j++) {
            pos.x = j;
            pos.y = i;
            //if you're looking at your board (self = true) then output ship positions as ship number (0 for no ship)
            //else if looking at enemy board then output just misses and hits (X's and O's)
            if (!self) {
                if (getCell(pos).hit == true) {
                    if (!getCell(pos).ship) std::cout << "X";
                    else std::cout << "O";
                } else {
                    std::cout << "-";
                }
                std::cout << " | ";
            }
            else std::cout << getCell(pos).ship << " | ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    return true;
}

std::string Player::getName() {
    return _name;
}

int Player::getOrder() {
    return _order;
}
        
int Player::getScore() {
    return _score;
}

Cell& Player::getCell(Pos pos) {
    return board[pos.y][pos.x];
}

bool Player::shipSunk(Pos pos, int ship) {
    for (int i = std::max(pos.y - shipLengths[ship-1], 0); i < (pos.y + shipLengths[ship-1]) && i < BOARD_SIZE; i++) {
        if (board[i][pos.x].ship == ship && board[i][pos.x].hit == false) return false;
    }
    for (int j = std::min(pos.x - shipLengths[ship-1], 0); j < (pos.x + shipLengths[ship-1]) && j < BOARD_SIZE; j++) {
        if (board[pos.y][j].ship == ship && board[pos.y][j].hit == false) return false;
    }
    std::cout << shipNames[ship - 1] << " sunk, legnth: " << shipLengths[ship - 1] << std::endl;
    return true;
}

bool Player::setupShips() {
    if (game->state == STANDARD_GAME) {
        for (int i = 0; i < 5; i++) {
            shipLengths.push_back(STANDARD_GAME_SHIP_LENGTHS[i]);
        }
    } else if (game->state == CUSTOM_SHIP_GAME) {
        
    }
    return true;
}