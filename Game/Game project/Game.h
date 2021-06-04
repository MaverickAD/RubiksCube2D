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
    //tableau pour connaitre les cases bien placées
    int* tab;
    //nombre de colonnes locked
    int collock;
    //nombre de lignes locked
    int rowlock;

    //valeur de la colonne de droite (sauf les 2 dernières)
    int* colright;

    //tableau de corrspondance pour le placement de la dernière colonne 
    int* correspondance;

    //premier move que l'on réalise
    char* nextMove;

    //nombre de mouvement 
    int NbMoves;
}solveur;

//fonction de création de la structure game
GAME* NewGame(int size);

//fonctions réalisants les coups du jeu
int deplacementV(GAME* game, DIR direction, int indice);
int deplacementH(GAME* game, DIR direction, int indice);

//fonction pour savoir si on a résolu le puzzle 
bool win(GAME* game);

//fonctions de test 
void display(GAME* game);
int parseInput(GAME* game);
void fill(GAME* game);
int parseInputMaker(GAME* game);
void copieTemoin(GAME* game);
void shuffle(GAME* game);

//fonction de création de notre structure solveur 
solveur* newSolve(GAME* game);

//fonction pour trouver l'indice correspondant à un carré précis dans le témoin
int FindIndice(GAME* game, solveur* sylvain, int Indice);

//fonction pour placer le carré que l'on souhaite en bas à droite
void BottomRight(GAME* game, solveur* sylvain, int place);

//fonction pour placer le carré au bon endroit une fois qu'il est en bas à droite
void placement(GAME* game, solveur* sylvain, int Indice);

//fonction pour résoudre la colonne tout à droite, à part le keyhold 
void colonneDroite(GAME* game, solveur* sylvain);

//fonction pour terminer la ligne du bas 
void endgame(GAME* game, solveur* sylvain);

//wrapper du solveur 
int Solveur(GAME* game);