#include "helper.h"

std::string getInput(std::string outputMessage, std::regex regex, std::string err) {
    std::string input;
    bool valid;
    do {
        std::cout << outputMessage << std::endl;
        std::cin >> input;
        valid = std::regex_match(input, regex);
        if (!valid) std::cout << err << std::endl;
    } while (!valid);
    return input;
}

bool cellOnBoard(Pos pos) {
    return (pos.x >= 0 && pos.y >= 0 && pos.x < BOARD_SIZE && pos.y < BOARD_SIZE);
}