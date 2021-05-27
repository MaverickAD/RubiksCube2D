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
            for (int j = 0; j < game->size; j++){
                printf("%d ", game->temoin[i - ((game->size) - 1) + j]);
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
    return 1;
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

int findIndice(GAME* game, int indiceInTemoin) {
    int tmp = game->temoin[indiceInTemoin];
    int indice = 0;
    while (game->tab[indice] != tmp) {
        indice++;
    }
    return indice;
}

bool IsInColumn(GAME* game, int lastLocked, int indiceTemoin) {
    int indice = findIndice(game, indiceTemoin);
    return (indice) % (game->size) <= lastLocked;
}

bool IsInRow(GAME* game, int LastLocked, int indiceTemoin) {
    int indice = findIndice(game, indiceTemoin);
    return (indice / game->size) <= LastLocked;
}


void petit_carre(GAME* game) {
    //on cherche à placer le cube en haut à gauche 



    //on le place d'abord à la bonne ligne 
    int indice = findIndice(game, 0);

    if ((indice / 2) >= game->size) {
        while (indice > game->size - 1)
        {
            //on est dans la moitié supérieur 
            deplacementV(game, DOWN, (indice)%(game->size));
           
            indice = findIndice(game, 0);
        }
    }
    else { 
        //on est dans la moitié inférieur
        while (indice > game->size - 1) {
            deplacementV(game, UP, (indice) % (game->size));
            indice = findIndice(game, 0);
        }
    }
   
    //on le place ensuite à la bonne colonne
    if (indice > (game->size / 2) - 1) {
        while (indice != 0) {
            deplacementH(game, RIGHT, 0);
            indice = findIndice(game, 0);
        }
    }
    else {
        while (indice != 0) {
            deplacementH(game, LEFT, 0);
            indice = findIndice(game, 0);
        }
    }
    //le coin en haut à gauche est correct

    //test si deuxieme carre est dans une colonne ou ligne lock
    if (!(game->tab[game->size]==game->temoin[game->size]))
    { 
        //On extrait le carré que l'on veut placer des lignes et colonnes locked
        if (IsInRow(game, 0, game->size)) {
            int indice = findIndice(game, game->size);
            deplacementV(game, DOWN, indice);
        }
        if (IsInColumn(game,0,game->size))
        {
            int indice = findIndice(game, game->size);
            deplacementH(game, RIGHT, (indice / game->size));
        }
    }

    indice = findIndice(game, game->size);
    

    bool enBas = false;
    if (game->size >= 7) {
        if (indice > (game->size * (game->size - 2))) {
            enBas = true;
        }
    }
    else {
        if (indice > (game->size * (game->size - 1))) {
            enBas = true;
        }
    }

    if (enBas) {
        while (indice > game->size * 2 || (indice < game->size)) {
            deplacementV(game, DOWN, indice % game->size);
            indice = findIndice(game, game->size);
        }
    }
    else {
        while (indice > game->size * 2 || indice < game->size) {
            deplacementV(game, UP, indice % game->size);
            indice = findIndice(game, game->size);
        }
    }
    
    bool aGauche = false;
    if (game->size >= 7) {
        if (indice % game->size < 3 ) {
            aGauche = true;
        }
    }
    else {
        if (indice % game->size < 2) {
            aGauche = true;
        }
    }
    if (aGauche) {
        while (indice != game->size) {
            deplacementH(game, LEFT, 1);
            indice = findIndice(game, game->size);
        }
    }
    else {
        while (indice != game->size) {
            deplacementH(game, RIGHT, 1);
            indice = findIndice(game, game->size);
        }
    }
    //le carré en dessous du coin supérieur gauche est bien placé 
    printf("\nles 2 en haut sont bons\n");
    display(game);
    //on cherche maintenant à placer les deux carrés manquant du petit carré
    int tmp = game->temoin[1];
    indice = 0;
    while (game->tab[indice] != tmp || indice == 0 || indice==game->size) {
        indice++;
    }

    
    if (indice % game->size == 0) {
        deplacementH(game, RIGHT, (indice / game->size));
        indice++;
    }
    if (indice == 1) {
        deplacementV(game, DOWN, 1);
        deplacementV(game, DOWN, 1);
        indice = 0;
        while (game->tab[indice] != tmp || indice == 0 || indice == game->size) {
            indice++;
        }
    }
    
    if ((indice / 2) >= game->size) {
        while (indice > (game->size * 3) - 1 || indice < game->size * 2)
        {
            //on est dans la moitié supérieur 
            deplacementV(game, DOWN, (indice) % (game->size));

            int tmp = game->temoin[1];
            indice = 0;
            while (game->tab[indice] != tmp || indice == 0 || indice == game->size) {
                indice++;
            }
        }
    }
    else {
        //on est dans la moitié inférieur
        while (indice > (game->size * 3) - 1 || indice < game->size * 2) {
            deplacementV(game, UP, (indice) % (game->size));
            int tmp = game->temoin[1];
            indice = 0;
            while (game->tab[indice] != tmp || indice == 0 || indice == game->size) {
                indice++;
            }
        }
    }
    
    if (indice > (game->size / 2) - 1) {
        while (indice != (game->size * 2) + 1) {
            deplacementH(game, RIGHT, 2);
            int tmp = game->temoin[1];
            indice = 0;
            while (game->tab[indice] != tmp || indice == 0 || indice == game->size) {
                indice++;
            }
        }
    }
    else {
        while (indice != (game->size * 2) + 1) {
            deplacementH(game, LEFT, 2);
            int tmp = game->temoin[1];
            indice = 0;
            while (game->tab[indice] != tmp || indice == 0 || indice == game->size) {
                indice++;
            }
        }
    }
    if (game->size == 3) {
        deplacementV(game, UP, 1);
        indice -= game->size;
    }

    printf("\nle 2 eme cube est en attente\n");
    display(game);
    /*
    if (game->size == 3) {
        int tmp = game->temoin[4];
        indice = 0;
        while (game->tab[indice] != tmp || indice == 0 || indice == game->size || indice == (game->size+1)) {
            indice++;
        }
        if (indice == 1)
        {
            deplacementH(game, RIGHT, 0);
            deplacementV(game, DOWN, 2);
            deplacementV(game, DOWN, 2);
            deplacementH(game, LEFT, 2);
            deplacementH(game, LEFT, 0);
        }
        if (indice == 2)
        {
            deplacementV(game, DOWN, 2);
            deplacementV(game, DOWN, 2);
            deplacementH(game, LEFT, 2);
        }
        if (indice==5)
        {
            deplacementV(game, DOWN, 2);
            deplacementH(game, LEFT, 2);
        }
        if (indice==6)
        {
            deplacementH(game, RIGHT, 2);

        }
        if (indice==8)
        {
            deplacementH(game, LEFT, 2);
        }
        deplacementV(game, UP, 1);
    }
    */
    /*
    else
    {
        display(game);
        int tmp = game->temoin[game->size + 1];
        indice = 0;
        while (game->tab[indice] != tmp || indice == 0 || indice == game->size || indice == (game->size + 1)) {
            indice++;
        }
        if (indice==1)
        {
            deplacementH(game, RIGHT, 0);
            deplacementV(game, DOWN, 2);
            deplacementV(game, DOWN, 2);
            deplacementV(game, DOWN, 2);
            deplacementH(game, LEFT, 0);
            deplacementH(game, LEFT, 3);
        }
        if (indice==(game->size*2))
        {
            deplacementV(game, DOWN, 0);
            deplacementH(game, RIGHT, 3);
            deplacementV(game, UP, 0);
        }
        if (indice == (game->size+1))
        {
            deplacementH(game, RIGHT, 1);
            deplacementV(game, DOWN, 2);
            deplacementV(game, DOWN, 2);
            deplacementH(game, LEFT, 1);
            deplacementH(game, LEFT, 3);
        }
        indice = 0;
        while (game->tab[indice] != tmp || indice == 0 || indice == game->size || indice == (game->size + 1)) {
            indice++;
        }
        if ((indice % game->size<=1)&&(indice!=game->size*2+1))
        {
            deplacementH(game, RIGHT, (indice / game->size));
            deplacementH(game, RIGHT, (indice / game->size));
        }
        indice = 0;
        while (game->tab[indice] != tmp || indice == 0 || indice == game->size || indice == (game->size + 1)) {
            indice++;
        }
        while ((indice/game->size)!=3)
        {
            deplacementV(game, DOWN, (indice % game->size));
            indice = 0;
            while (game->tab[indice] != tmp || indice == 0 || indice == game->size || indice == (game->size + 1)) {
                indice++;
            }
        }
        while (indice!=((game->size*3)+1))
        {
            deplacementH(game, LEFT, 3);
            indice = 0;
            while (game->tab[indice] != tmp || indice == 0 || indice == game->size || indice == (game->size + 1)) {
                indice++;
            }
        }
        deplacementV(game, UP, 1);
        deplacementV(game, UP, 1);
    }
    */

    

}