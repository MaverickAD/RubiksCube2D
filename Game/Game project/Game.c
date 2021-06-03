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

//fonction de cr�ation de la structure game
GAME* NewGame(int size) {
    // allocation de la structure GAME
    GAME* game = (GAME*)malloc(sizeof(GAME));
    if (game == NULL) return game;
    if (size <= MAX_SIZE) {
        // allocation du tableau de donn�es
        game->tab = (int*)malloc(sizeof(int) * size * size);
    }
    if ((game->tab) != NULL) {
        // initialisation des param�tres 
        game->size = size;
        game->temoin = (int*)malloc(sizeof(int) * size * size);
    }
    else {
        // la GAME n'a pas pu �tre cr��e, game vaut NULL
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

//fonction pour r�aliser les mouvement verticaux 
int deplacementV(GAME* game, DIR direction, int indice) {
    if (direction == UP)
    {
        int indicecourant = game->size + indice;
        int tmp = game->tab[indice];

        //on d�place toutes les pi�ces du puzzle
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

//fonction pour r�aliser les mouvement horizontaux
int deplacementH(GAME* game, DIR direction, int indice) {

    if (direction == LEFT) {
        int temp = game->tab[indice * game->size];

        //on d�place tout les carr�s vers la gauche 
        for (int i = indice * game->size + 1; i < (indice + 1) * game->size; i++) {
            game->tab[i - 1] = game->tab[i];
        }
        //le dernier carr� "loop over"
        game->tab[(indice + 1) * game->size - 1] = temp;
    }

    else
    {
        int temp = game->tab[(indice + 1) * game->size - 1];

        //on d�place les carr�s vers la droite
        for (int i = (indice + 1) * game->size - 1; i > indice * game->size - 1; i--) {
            game->tab[i] = game->tab[i - 1];
        }
        //le dernier "loop over"
        game->tab[indice * game->size] = temp;
    }

    return 1;
}

//fonction pour savoir si on a r�solu le puzzle 
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


//fonction de cr�ation de notre structure solveur
solveur* newSolve(GAME* game) {
    //allocation de la m�moir pour la structure
    solveur* tmp = (solveur*)malloc(sizeof(solveur));
    if (tmp != NULL)
    {
        //allocation de la m�moire pour le tableau contenant les cases d�j� plac�s
        tmp->tab = (int*)malloc(sizeof(int) * game->size * game->size);
        if (tmp->tab != NULL)
        {
            //initialisation des donn�es
            tmp->collock = 0;
            tmp->rowlock = 0;
            tmp->NbMoves = 0;

            for (int i = 0; i < (game->size * game->size); i++)
            {
                tmp->tab[i] = 0;
            }

            //allocation de la m�moire pour le tableau contenant les valeurs de la colonne de droite
            tmp->colright = (int*)malloc(sizeof(int) * (game->size - 2));
            if (tmp->tab != NULL) {
                //obtention des valeurs
                for (int i = 0; i < game->size - 2; i++) {
                    tmp->colright[i] = game->temoin[(game->size) * (i + 1) - 1];
                }

                //allocation de la m�moire pour le tableau de correspondance 
                tmp->correspondance = (int*)malloc(sizeof(int) * (game->size));
                if (tmp->correspondance != NULL) {
                    for (int i = 0; i < game->size; i++) {
                        tmp->correspondance[i] = 0;
                    }
                }

                //allocation de la m�moire pour le string du premier coup 
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

// fonction pour trouver l'indice correspondant � un carr� pr�cis dans le t�moin
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

//fonction pour placer le carr� que l'on souhaite en bas � droite
void BottomRight(GAME* game, solveur* sylvain, int place) {
    int iteration = 0;

    int ligne = place / game->size;

    //on place le carr� dans la derni�re colonne 
    while ((place % game->size) != (game->size - 1)) {

        deplacementH(game, RIGHT, ligne);
        sylvain->NbMoves++;
        if (sylvain->nextMove[1] == 0) {
            sylvain->nextMove[0] = ligne;
            sylvain->nextMove[1] = 'R';
        }
        //on compte le nombre de d�calages
        iteration++;
        place++;
    }

    //on le place ensuite � la derni�re ligne 
    while (place != (game->size * game->size) - 1) {
        deplacementV(game, DOWN, game->size - 1);
        sylvain->NbMoves++;
        if (sylvain->nextMove[1] == 0) {
            sylvain->nextMove[0] = game->size - 1;
            sylvain->nextMove[1] = 'D';
        }
        place += game->size;
    }

    //si la ligne �tait locked, on la remet � sa place
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

//fonction pour placer le carr� au bon endroit une fois qu'il est en bas � droite
void placement(GAME* game, solveur* sylvain, int Indice) {
    int colonne = Indice % game->size;
    int iteration = 0;

    //on pr�pare d'abord la colonne qui va recevoir le carr�
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

    //on place ensuite le carr� dans la colonne
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

    //on notifie que le carr� est maintenant bien plac�
    sylvain->tab[Indice] = 1;

    //on actualise le nombre de lignes et colonnes locked si n�cessaire
    if (sylvain->collock < colonne + 1) {
        sylvain->collock = colonne + 1;
    }
    if (sylvain->rowlock < (Indice / game->size) + 1) {
        sylvain->rowlock = Indice / game->size + 1;
    }


}


//fonction pour r�soudre la colonne tout � droite, � part le keyhold 
void colonneDroite(GAME* game, solveur* sylvain) {
    //on parcours la colonne de droite
    for (int i = 0; i < game->size; i++) {
        //on d�termine si on a "besoin" du carr�
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

                //dans le cas o� on a "besoin" de toutes les cases de la ligne du bas
                if (k == (game->size))
                {
                    //on d�termine une case qui est en doublon
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

        //une fois que la case en bas � gauche n'est pas une case dont on a besoin on descend le tout 
        deplacementV(game, DOWN, game->size - 1);
        sylvain->NbMoves++;
        for (int j = 0; j < game->size; j++)
        {
            sylvain->correspondance[j] = 0;
        }

    }

    //les carr�s n�cessaires sont plac�s dans la ligne du bas
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

    //on extrait la value du keylock des endroits ind�sirable
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

    //on d�termine l'�cart entre la valeur que l'on vient de placer et celle en dessous 
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
        printf("%d%c", sylvain->nextMove[0], sylvain->nextMove[1]);
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
    if (game->size == 6) {
        BottomRight(game, sylvain, FindIndice(game, sylvain, 0));
        placement(game, sylvain, 0);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 1));
        placement(game, sylvain, 1);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 6));
        placement(game, sylvain, 6);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 7));
        placement(game, sylvain, 7);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 2));
        placement(game, sylvain, 2);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 8));
        placement(game, sylvain, 8);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 12));
        placement(game, sylvain, 12);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 13));
        placement(game, sylvain, 13);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 14));
        placement(game, sylvain, 14);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 3));
        placement(game, sylvain, 3);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 9));
        placement(game, sylvain, 9);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 15));
        placement(game, sylvain, 15);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 18));
        placement(game, sylvain, 18);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 19));
        placement(game, sylvain, 19);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 20));
        placement(game, sylvain, 20);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 21));
        placement(game, sylvain, 21);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 4));
        placement(game, sylvain, 4);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 10));
        placement(game, sylvain, 10);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 16));
        placement(game, sylvain, 16);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 22));
        placement(game, sylvain, 22);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 24));
        placement(game, sylvain, 24);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 25));
        placement(game, sylvain, 25);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 26));
        placement(game, sylvain, 26);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 27));
        placement(game, sylvain, 27);
        BottomRight(game, sylvain, FindIndice(game, sylvain, 28));
        placement(game, sylvain, 28);
        colonneDroite(game, sylvain);
    }
    
}



