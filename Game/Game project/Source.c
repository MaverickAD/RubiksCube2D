#include "Game.h"
#define GAME_SIZE 3



int main(int argc, char* argv[]) {
    /*
    srand(time(NULL));
    int size = sqrt((_countof(argv[0]) - 1)/2);
    GAME* game = NewGame(size);
    for (int i = 0; i < size * size; i++) {
        game->tab[i] = argv[0][i];
        game->temoin[i] = argv[0][size * size + 1];
    }
    Solveur(game);
    */



    GAME* game = NewGame(GAME_SIZE);



    while (!parseInputMaker(game)) {};
    copieTemoin(game);
    shuffle(game);
    display(game);
    Solveur(game);
    display(game);
    /*
    */



}