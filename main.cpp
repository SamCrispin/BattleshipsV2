#include "helper.h"
#include "players/cpu.h"
#include "players/human.h"
#include "players/player.h"
#include "controller.h"

int main() {
    Controller* game = Controller::getInstance();

    game->setup();
}