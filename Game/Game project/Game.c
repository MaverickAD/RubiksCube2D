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

solveur* newSolve(GAME* game) {
    solveur* tmp = (solveur*)malloc(sizeof(solveur));
    if (tmp != NULL)
    {
        tmp->tab = (int*)malloc(sizeof(int) * game->size * game->size);
        if (tmp->tab != NULL)
        {
            tmp->collock = 0;
            tmp->rowlock = 0;
            tmp->NbMoves = 0;
            for (int i = 0; i < (game->size * game->size); i++)
            {
                tmp->tab[i] = 0;
            }
            tmp->colright = (int*)malloc(sizeof(int) * (game->size - 2) );
            if (tmp->tab != NULL) {
                for (int i = 0; i < game->size - 2; i++) {
                    tmp->colright[i] = game->temoin[(game->size) * (i + 1) - 1];
                }
                tmp->correspondance = (int*)malloc(sizeof(int) * (game->size));
                if (tmp->correspondance != NULL) {
                    for (int i = 0; i < game->size; i++) {
                        tmp->correspondance[i] = 0;
                    }
                }
                tmp->nextMove = (char*)malloc(sizeof(char) * 2);
                if (tmp->nextMove != NULL) {
                    tmp->nextMove[0] = 0;
                    tmp->nextMove[1] = 0;
                    return (tmp);
                }
            }
            
        }
        else
        {
            free(tmp->tab);
        }
    }
    else
    {
        free(tmp);
    }
}

int FindIndice(GAME* game, solveur* sylvain, int Indice) {
    int value = game->temoin[Indice];
    int i = 0;
    while (game->tab[i] != value || sylvain->tab[i] == 1)
    {
        i++;
    }
    return i;
}

void BottomRight(GAME* game, solveur* sylvain, int place) {
    int iteration = 0;

    int ligne = place / game->size;
    //on place le carré dans la dernière colonne 
    while ((place % game->size) != (game->size - 1)) {
        
        deplacementH(game, RIGHT, ligne);
        sylvain->NbMoves++;
        if (sylvain->nextMove[1] == 0) {
            sylvain->nextMove[0] = ligne;
            sylvain->nextMove[1] = 'R';
        }
        //on compte le nombre de décalages
        iteration++;
        place++;
    }

    //on le place ensuite à la dernière ligne 
    while (place != (game->size * game->size) - 1) {
        deplacementV(game, DOWN, game->size - 1);
        sylvain->NbMoves++;
        if (sylvain->nextMove[1] == 0) {
            sylvain->nextMove[0] = game->size - 1;
            sylvain->nextMove[1] = 'D';
        }
        place += game->size;
    }

    //si la ligne était locked, on la remet à sa place
    if (ligne < sylvain->rowlock) {
        for (int i = 0; i < iteration; i++) {
            deplacementH(game, LEFT, ligne);
            sylvain->NbMoves++;
            if (sylvain->nextMove[1] == 0) {
                sylvain->nextMove[0] = ligne;
                sylvain->nextMove[1] = 'L';
            }
        }
    }
}

void placement(GAME* game, solveur* sylvain, int Indice) {
    int colonne = Indice % game->size;
    int iteration = 0;

    //on prépare d'abord la colonne qui va recevoir le carré
    while (Indice / game->size != game->size - 1) {
        deplacementV(game, DOWN, colonne);
        sylvain->NbMoves++;
        if (sylvain->nextMove[1] == 0) {
            sylvain->nextMove[0] = colonne;
            sylvain->nextMove[1] = 'D';
        }
        Indice += game->size;
        iteration++;
    }

    //on place ensuite le carré dans la colonne
    for (int i = 0; i < ((game->size - 1) - colonne); i++) {
        deplacementH(game, LEFT, game->size - 1);
        sylvain->NbMoves++;
        if (sylvain->nextMove[1] == 0) {
            sylvain->nextMove[0] = game->size - 1;
            sylvain->nextMove[1] = 'L';
        }
    }

    //on remonte ensuite la colonne
    for (int i = 0; i < iteration; i++) {
        deplacementV(game, UP, colonne);
        sylvain->NbMoves++;
        if (sylvain->nextMove[1] == 0) {
            sylvain->nextMove[0] = colonne;
            sylvain->nextMove[1] = 'U';
        }

        Indice -= game->size;
    }

    //on notifie que le carré est maintenant bien placé
    sylvain->tab[Indice] = 1;

    //on actualise le nombre de lignes et colonnes locked si nécessaire
    if (sylvain->collock < colonne + 1) {
        sylvain->collock = colonne + 1;
    }
    if (sylvain->rowlock < (Indice / game->size) + 1) {
        sylvain->rowlock = Indice / game->size + 1;
    }


}

void colonneDroite(GAME* game, solveur* sylvain) {
    for (int i = 0; i < game->size; i++) {
        bool need = false;
        for (int j = 0; j < game->size - 2; j++) {
            if (game->tab[(game->size * game->size) - 1] == sylvain->colright[j]) {
                need = true;
            }
            
        }
        if (need) {
            int k = 0;
            while (need &&( k < game->size)) {
                deplacementH(game, LEFT, game->size - 1);
                sylvain->NbMoves++;
                need = false;
                for (int j = 0; j < game->size - 2; j++) {
                    if (game->tab[(game->size * game->size) - 1] == sylvain->colright[j]) {
                        need = true;
                    }
                }
                k++;
                if (k == (game->size))
                {
                    for (int j = 0; j < game->size - 3; j++) {
                        int indice = game->size * (game->size - 1);
                        while (game->tab[indice] != sylvain->colright[j] || sylvain->correspondance[indice % game->size] == 1) {
                            indice++;
                        }
                        sylvain->correspondance[indice % game->size] = 1;
                    }
                    int indCoressepondance = game->size - 1;
                    while (sylvain->correspondance[indCoressepondance] == 1) {
                        deplacementH(game, RIGHT, game->size - 1);
                        sylvain->NbMoves++;
                        indCoressepondance--;
                    }
                }
            }
            
        }
        deplacementV(game, DOWN, game->size - 1);
        sylvain->NbMoves++;
        for (int j = 0; j < game->size; j++)
        {
            sylvain->correspondance[j] = 0;
        }

     }
    
     //les carrés nécessaires sont placés dans la ligne du bas
    for (int i = game->size - 3; i >= 0; i--) {
        while (game->tab[(game->size * game->size) - 1] != sylvain->colright[i]) {
            deplacementH(game, RIGHT, game->size  - 1);
            sylvain->NbMoves++;
        }
        deplacementV(game, DOWN, game->size - 1);
        sylvain->NbMoves++;
    }


}

void endgame(GAME* game, solveur* sylvain) {
    int valueKeyLock = game->temoin[((game->size) * (game->size - 1)) - 1];
    if (game->tab[(game->size * game->size) - 1] == valueKeyLock) {
        deplacementH(game, LEFT, game->size - 1);
        sylvain->NbMoves++;
    }
    deplacementV(game, DOWN, game->size - 1);
    sylvain->NbMoves++;
    if (game->tab[(game->size * game->size) - 1] == valueKeyLock) {
        deplacementH(game, LEFT, game->size - 1);
        sylvain->NbMoves++;
    }

    int valueTopRight = game->tab[game->size - 1];
    int valueBottomRight = game->tab[(game->size) * (game->size) - 1];

    int indice = (game->size) * (game->size - 1);
    while (game->temoin[indice] != valueBottomRight) {
        indice++;
    }

    int delta = 0;
    while (game->temoin[indice] != valueTopRight) {
        delta++;
        if (indice == (game->size) * (game->size - 1)) {
            indice = (game->size * game->size) - 1;
        }
        else {
            indice--;
        }
    }
    for (int i = 0; i < delta; i++) {
        deplacementH(game, RIGHT, game->size - 1);
        sylvain->NbMoves++;
    }
    deplacementV(game, UP, game->size - 1);
    sylvain->NbMoves++;

    while (!win(game)) {
        deplacementH(game, LEFT, game->size - 1);
        sylvain->NbMoves++;
    }

}



void dispSylvain(GAME* game, solveur* sylvain) {
    for (int i = 0; i < (game->size) * (game->size); i++) {
        printf("%d ", sylvain->tab[i]);
        if ((i + 1) % (game->size) == 0) {
            for (int j = 0; j < 10; j++) {
                printf(" ");
            }
            printf("\n");
        }
        
    }
    printf("\nrowlock = %d\n", sylvain->rowlock);
    printf("\ncollock = %d\n", sylvain->collock);

    for (int i = 0; i < game->size - 2; i++) {
        printf("\n %d", sylvain->colright[i]);
    }
}


int Solveur(GAME* game) {
    solveur* sylvain = newSolve(game);


   
    3 * 3;
    if (game->size == 3) {
        BottomRight(game, sylvain, FindIndice(game, sylvain, 0));
        placement(game, sylvain, 0);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 1));
        placement(game, sylvain, 1);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 3));
        placement(game, sylvain, 3);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 4));
        placement(game, sylvain, 4);
        colonneDroite(game, sylvain);
        endgame(game, sylvain);
        printf("\n Next move : %d %c", sylvain->nextMove[0], sylvain->nextMove[1]);
        printf("\n Nombre de coups : %d\n", sylvain->NbMoves);
    }
   
  

    



    //4 * 4;
    if (game->size == 4) {
        BottomRight(game, sylvain, FindIndice(game, sylvain, 0));
        placement(game, sylvain, 0);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 1));
        placement(game, sylvain, 1);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 4));
        placement(game, sylvain, 4);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 5));
        placement(game, sylvain, 5);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 2));
        placement(game, sylvain, 2);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 6));
        placement(game, sylvain, 6);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 8));
        placement(game, sylvain, 8);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 9));
        placement(game, sylvain, 9);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 10));
        placement(game, sylvain, 10);
        colonneDroite(game, sylvain);
        endgame(game, sylvain);

    }
    


       
    //5 * 5;
    if (game->size == 5) {
        BottomRight(game, sylvain, FindIndice(game, sylvain, 0));
        placement(game, sylvain, 0);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 1));
        placement(game, sylvain, 1);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 5));
        placement(game, sylvain, 5);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 6));
        placement(game, sylvain, 6);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 2));
        placement(game, sylvain, 2);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 7));
        placement(game, sylvain, 7);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 10));
        placement(game, sylvain, 10);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 11));
        placement(game, sylvain, 11);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 12));
        placement(game, sylvain, 12);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 3));
        placement(game, sylvain, 3);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 8));
        placement(game, sylvain, 8);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 13));
        placement(game, sylvain, 13);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 15));
        placement(game, sylvain, 15);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 16));
        placement(game, sylvain, 16);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 17));
        placement(game, sylvain, 17);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 18));
        placement(game, sylvain, 18);
        colonneDroite(game, sylvain);
        endgame(game, sylvain);
    }
    

}



