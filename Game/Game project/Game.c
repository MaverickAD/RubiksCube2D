#include "Game.h"

COLORS toColor(int value) {

    switch (value)
    {
    case 1:  return RED;
    case 2:  return GREEN;
    case 3:  return BROWN;
    case 4:  return WHITE;
    case 5:  return YELLOW;
    case 6:  return BLUE;
    case 7:  return PURPLE;
    case 8:  return ORANGE;
    case 9:  return PINK;
    case 10: return GREY;
    case 11: return BLACK;
    default: return;
    }
}

void display(GAME* game) {
    for (int i = 0; i < (game->size) * (game->size); i++) {
        printf("%d ", game->tab[i]);
        if ((i + 1) % (game->size) == 0) {
            for (int j = 0; j < 10; j++) {
                printf(" ");
            }
            for (int j = 0; j < 3; j++){
                printf("%d ", game->temoin[i - 2 + j]);
            }
            printf("\n");
        }
    }
    printf("\n");
}

GAME * NewGame(int size) {
    // allocation de la structure GAME
    GAME *game = (GAME*)malloc(sizeof(GAME));
    if (game == NULL) return game;
    if (size <= MAX_SIZE) {
        // allocation du tableau de données
        game->tab = (int*)malloc(sizeof(int) * size * size);
    }
    if ((game->tab) != NULL) {
        // initialisation des paramètres 
        game->size = size;
        game->temoin = (int*)malloc(sizeof(int) * size * size);
    }
    else {
        // la GAME n'a pas pu être créée, game vaut NULL
        free(game); 
        game = NULL;
    }
    return game;
}

int parseInput(GAME* game) {

    char string[3];
    scanf_s("%s", string, 3);
    string[2] = 0;

    if (strlen(string) != 2) return -1;

    char collign = string[0];
    char dir = string[1];

    if (collign < '1'
        || collign >(game->size + '0')) {
        puts("SizeError");
        return -1;
    }

    if (dir != 'H'
        && dir != 'B'
        && dir != 'D'
        && dir != 'G') {
        printf_s("Can't find direction ~> %c\n", dir);
        return -1;
    }

    collign = (collign % '0') - 1;
    switch (dir)
    {
    case 'H': return deplacementV(game, UP, collign);
    case 'B': return deplacementV(game, DOWN, collign);
    case 'D': return deplacementH(game, RIGHT, collign);
    case 'G': return deplacementH(game, LEFT, collign);
    default: puts("error");  return -1;
    }

}

void fill(GAME* game) {
    for (int i = 0; i < game->size * game->size; i++) {
        game->tab[i] = rand() % 11;
    }
}

int deplacementV(GAME* game, DIR direction, int indice) {
    if (direction == UP)
    {
        int indicecourant = game->size + indice;
        int tmp = game->tab[indice];
        for (int i = 0; i < game->size - 1; i++)
        {
            game->tab[indice + (i * game->size)] = game->tab[indicecourant];
            indicecourant += game->size;
        }
        indicecourant -= game->size;
        game->tab[indicecourant] = tmp;
    }
    else
    {
        for (int i = 0; i < game->size-1; i++) {
            deplacementV(game, UP, indice);
        }
    }
}

int deplacementH(GAME* game, DIR direction, int indice) {

    if (direction == LEFT) {
        int temp = game->tab[indice * game->size];
        for (int i = indice * game->size + 1; i < (indice + 1) * game->size; i++) {
            game->tab[i - 1] = game->tab[i];
        }
        game->tab[(indice + 1) * game->size - 1] = temp;
    }

    else
    {
        int temp = game->tab[(indice + 1) * game->size - 1];
        for (int i = (indice + 1) * game->size - 1; i > indice * game->size - 1; i--) {
            game->tab[i] = game->tab[i - 1];
        }
        game->tab[indice * game->size] = temp;
    }

    return 1;
}

bool win(GAME* game) {
    for (int i = 0; i < game->size * game->size; i++) if (game->tab[i] != game->temoin[i]) return false;
    return true;
}

int parseInputMaker(GAME* game) {

    puts("| Create your own pattern |");

    char string[101] = { 0 };
    scanf_s("%s", string, 100);
    string[100] = '\0';
    int len = strlen(string);

    if (len != game->size * game->size) { printf("Canno't match len input %d with len game board %d\n", len, game->size * game->size); return 0; }

    for (int i = 0; i < len; i++) {

        char letter = string[i];
        if (letter < '1' || letter > '9') { printf("Unknow number %c\n", letter); return 0; }

        letter -= '0';

        game->temoin[i] = letter;
    }

    return 1;
}


void copieTemoin(GAME* game) {
    for (int  i = 0; i < game->size * game->size; i++)
    {
        game->tab[i] = game->temoin[i];
    }
}

void shuffle(GAME* game) {
    srand(time(NULL));
    for (int i = 0; i < 1000; i++)
    {
        int alea = rand() % 4;
        int indicealea = rand() % (game->size);
        switch (alea)
        {
        case 0:
            deplacementH(game, LEFT, indicealea);
            break;
        case 1:
            deplacementH(game, RIGHT, indicealea);
            break;
        case 2:
            deplacementV(game, UP, indicealea);
            break;
        case 3:
            deplacementV(game, DOWN, indicealea);
            break;
        }

    }
}

void petit_carre(GAME* game) {
    int tmp = game->temoin[0];
    int indice = 0;
    while (game->tab[indice] != tmp) {
        indice++;
    }

    if ((indice / 2) > game->size-1) {
        printf("on est en bas\n");
        while (indice > game->size)
        {
            deplacementV(game, DOWN, indice/game->size);
           
            if (indice > (game->size * game->size) - game->size) {
                indice = indice - (game->size * (game->size - 1));
            }
            else {
                indice += game->size;
            }
        }
    }
    else { 
        printf("on est en haut\n");
        while (indice > game->size) {
            deplacementV(game, UP, indice/game->size);
            indice -= game->size;
        }
    }
    //le coin en haut à gauche est correct 
    
}