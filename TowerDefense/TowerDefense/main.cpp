#include "cmenu.h"
#include "cgame.h"

int main() {
    cmenu menu;
    bool isContinue = false;
    string player = menu.runMenu(isContinue);

    if (player.empty()) return 0;

    cgame game;
    game.playerName = player;

    if (isContinue && game.processLoadFile(player))
        game.playContinue();

    game.run();
    return 0;
}
