#include "Game.h"
#define GAME_SIZE 3



int main(int argc, char* argv[]) {

    srand(time(NULL));
    int size = sqrt(strlen(argv[1]));

    GAME* game = NewGame(size);

    for (int i = 0; i < size * size; i++) {
        game->temoin[i] = argv[1][i];
        game->tab[i] = argv[2][i];
    }
    Solveur(game);

    



}