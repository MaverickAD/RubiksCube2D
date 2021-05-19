#include "Game.h"
#define GAME_SIZE 3 


int main() {
    srand(time(NULL));
    GAME* game = NewGame(GAME_SIZE);
    fill(game);
    parseInputMaker(game);
    display(game);

    while (true)
    {
        parseInput(game);
        display(game);
    }
}