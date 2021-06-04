#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>


#define MAX_SIZE 8
#define PARSE_ERROR -1
#define CICR_SWITCH_ERROR 0 


typedef struct {
    int size;
    int* tab;
    int* temoin;
}GAME;

typedef enum DIR {
    UP,
    DOWN,
    LEFT,
    RIGHT
} DIR;


typedef struct solveur {
    //tableau pour connaitre les cases bien plac�es
    int* tab;
    //nombre de colonnes locked
    int collock;
    //nombre de lignes locked
    int rowlock;

    //valeur de la colonne de droite (sauf les 2 derni�res)
    int* colright;

    //tableau de corrspondance pour le placement de la derni�re colonne 
    int* correspondance;

    //premier move que l'on r�alise
    char* nextMove;

    //nombre de mouvement 
    int NbMoves;
}solveur;

//fonction de cr�ation de la structure game
GAME* NewGame(int size);

//fonctions r�alisants les coups du jeu
int deplacementV(GAME* game, DIR direction, int indice);
int deplacementH(GAME* game, DIR direction, int indice);

//fonction pour savoir si on a r�solu le puzzle 
bool win(GAME* game);

//fonction de cr�ation de notre structure solveur 
solveur* newSolve(GAME* game);

//fonction pour trouver l'indice correspondant � un carr� pr�cis dans le t�moin
int FindIndice(GAME* game, solveur* sylvain, int Indice);

//fonction pour placer le carr� que l'on souhaite en bas � droite
void BottomRight(GAME* game, solveur* sylvain, int place);

//fonction pour placer le carr� au bon endroit une fois qu'il est en bas � droite
void placement(GAME* game, solveur* sylvain, int Indice);

//fonction pour r�soudre la colonne tout � droite, � part le keyhold 
void colonneDroite(GAME* game, solveur* sylvain);

//fonction pour terminer la ligne du bas 
void endgame(GAME* game, solveur* sylvain);

//wrapper du solveur 
int Solveur(GAME* game);