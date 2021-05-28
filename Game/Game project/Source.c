#include "Game.h"
#define GAME_SIZE 4



int main() {
    srand(time(NULL));
    GAME* game = NewGame(GAME_SIZE);

    while (!parseInputMaker(game)) {};
    copieTemoin(game);
    shuffle(game);
    display(game);
    Solveur(game);
    display(game);


}