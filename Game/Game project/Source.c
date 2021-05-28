 #include "Game.h"
#define GAME_SIZE 4



int main() {
    srand(time(NULL));
    GAME* game = NewGame(GAME_SIZE);

    
        while (!parseInputMaker(game)) {};
        copieTemoin(game);
        shuffle(game);
        printf("Grille de base wesh :\n");
        display(game);
        petit_carre(game);
        printf("\nC'est resolu, youpi\n");
        display(game);

    
  

}