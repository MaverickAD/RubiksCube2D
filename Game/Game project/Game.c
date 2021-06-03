#include "Game.h"


void display(GAME* game) {
    for (int i = 0; i < (game->size) * (game->size); i++) {
        printf("%d ", game->tab[i]);
        if ((i + 1) % (game->size) == 0) {
            for (int j = 0; j < 10; j++) {
                printf(" ");
            }
            for (int j = 0; j < game->size; j++) {
                printf("%d ", game->temoin[i - ((game->size) - 1) + j]);
            }
            printf("\n");
        }
    }
    printf("\n");
}

//fonction de création de la structure game
GAME* NewGame(int size) {
    // allocation de la structure GAME
    GAME* game = (GAME*)malloc(sizeof(GAME));
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

//fonction pour réaliser les mouvement verticaux 
int deplacementV(GAME* game, DIR direction, int indice) {
    if (direction == UP)
    {
        int indicecourant = game->size + indice;
        int tmp = game->tab[indice];

        //on déplace toutes les pièces du puzzle
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
        //pour aller vers le haut, on va 3 fois vers le bas 
        for (int i = 0; i < game->size - 1; i++) {
            deplacementV(game, UP, indice);
        }
    }
    return 1;
}

//fonction pour réaliser les mouvement horizontaux
int deplacementH(GAME* game, DIR direction, int indice) {

    if (direction == LEFT) {
        int temp = game->tab[indice * game->size];

        //on déplace tout les carrés vers la gauche 
        for (int i = indice * game->size + 1; i < (indice + 1) * game->size; i++) {
            game->tab[i - 1] = game->tab[i];
        }
        //le dernier carré "loop over"
        game->tab[(indice + 1) * game->size - 1] = temp;
    }

    else
    {
        int temp = game->tab[(indice + 1) * game->size - 1];

        //on déplace les carrés vers la droite
        for (int i = (indice + 1) * game->size - 1; i > indice * game->size - 1; i--) {
            game->tab[i] = game->tab[i - 1];
        }
        //le dernier "loop over"
        game->tab[indice * game->size] = temp;
    }

    return 1;
}

//fonction pour savoir si on a résolu le puzzle 
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
    for (int i = 0; i < game->size * game->size; i++)
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


//fonction de création de notre structure solveur
solveur* newSolve(GAME* game) {
    //allocation de la mémoir pour la structure
    solveur* tmp = (solveur*)malloc(sizeof(solveur));
    if (tmp != NULL)
    {
        //allocation de la mémoire pour le tableau contenant les cases déjà placés
        tmp->tab = (int*)malloc(sizeof(int) * game->size * game->size);
        if (tmp->tab != NULL)
        {
            //initialisation des données
            tmp->collock = 0;
            tmp->rowlock = 0;
            tmp->NbMoves = 0;

            for (int i = 0; i < (game->size * game->size); i++)
            {
                tmp->tab[i] = 0;
            }

            //allocation de la mémoire pour le tableau contenant les valeurs de la colonne de droite
            tmp->colright = (int*)malloc(sizeof(int) * (game->size - 2));
            if (tmp->tab != NULL) {
                //obtention des valeurs
                for (int i = 0; i < game->size - 2; i++) {
                    tmp->colright[i] = game->temoin[(game->size) * (i + 1) - 1];
                }

                //allocation de la mémoire pour le tableau de correspondance 
                tmp->correspondance = (int*)malloc(sizeof(int) * (game->size));
                if (tmp->correspondance != NULL) {
                    for (int i = 0; i < game->size; i++) {
                        tmp->correspondance[i] = 0;
                    }
                }

                //allocation de la mémoire pour le string du premier coup 
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

// fonction pour trouver l'indice correspondant à un carré précis dans le témoin
int FindIndice(GAME* game, solveur* sylvain, int Indice) {
    int value = game->temoin[Indice];
    int i = 0;

    //on parcours le tableau pour trouver la valeur et donc son indice
    while (game->tab[i] != value || sylvain->tab[i] == 1)
    {
        i++;
    }
    return i;
}

//fonction pour placer le carré que l'on souhaite en bas à droite
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

//fonction pour placer le carré au bon endroit une fois qu'il est en bas à droite
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


//fonction pour résoudre la colonne tout à droite, à part le keyhold 
void colonneDroite(GAME* game, solveur* sylvain) {
    //on parcours la colonne de droite
    for (int i = 0; i < game->size; i++) {
        //on détermine si on a "besoin" du carré
        bool need = false;
        for (int j = 0; j < game->size - 2; j++) {
            if (game->tab[(game->size * game->size) - 1] == sylvain->colright[j]) {
                need = true;
            }

        }

        //si c'est le cas, on la place dans la ligne du bas 
        if (need) {
            int k = 0;
            while (need && (k < game->size)) {
                deplacementH(game, LEFT, game->size - 1);
                sylvain->NbMoves++;
                need = false;
                for (int j = 0; j < game->size - 2; j++) {
                    if (game->tab[(game->size * game->size) - 1] == sylvain->colright[j]) {
                        need = true;
                    }
                }
                k++;

                //dans le cas où on a "besoin" de toutes les cases de la ligne du bas
                if (k == (game->size))
                {
                    //on détermine une case qui est en doublon
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

        //une fois que la case en bas à gauche n'est pas une case dont on a besoin on descend le tout 
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
            deplacementH(game, RIGHT, game->size - 1);
            sylvain->NbMoves++;
        }
        deplacementV(game, DOWN, game->size - 1);
        sylvain->NbMoves++;
    }

    if (game->size == 3) {
        sylvain->tab[2] = 1;
    }


}

void endgame(GAME* game, solveur* sylvain) {

    //on extrait la value du keylock des endroits indésirable
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

    //on détermine l'écart entre la valeur que l'on vient de placer et celle en dessous 
    int delta = 0;
    while (game->temoin[indice] != valueTopRight || sylvain->tab[indice] == 1) {
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

    if (game->size == 3) {
        while (!win(game)) {
            deplacementH(game, LEFT, game->size - 1);
            sylvain->NbMoves++;
        }
    }


}


int Solveur(GAME* game) {
    solveur* sylvain = newSolve(game);



    //3 * 3;
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
        //printf("%d%c", sylvain->nextMove[0], sylvain->nextMove[1]);
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
        printf("%d%c", sylvain->nextMove[0], sylvain->nextMove[1]);

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
        //printf("%d%c", sylvain->nextMove[0], sylvain->nextMove[1]);
    }


}



