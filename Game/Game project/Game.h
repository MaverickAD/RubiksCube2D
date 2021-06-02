#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_SIZE 10
#define PARSE_ERROR -1
#define CICR_SWITCH_ERROR 0 


typedef enum COLORS {
    RED,
    GREEN,
    BROWN,
    WHITE,
    YELLOW,
    BLUE,
    PURPLE,
    ORANGE,
    PINK,
    GREY,
    BLACK
}COLORS;

typedef struct {
    int x;
    int y;
    COLORS color;
} PIECE;

typedef struct {
    int size;
    int *tab;
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

    char* nextMove;

    int NbMoves;
}solveur;


COLORS toColor(int value);
void display(GAME* game);
GAME * NewGame(int size);
int parseInput(GAME* game);
void fill(GAME* game);
int deplacementV(GAME* game, DIR direction, int indice);
int deplacementH(GAME* game, DIR direction, int indice);
bool win(GAME* game);
int parseInputMaker(GAME* game);
void copieTemoin(GAME* game);
void shuffle(GAME* game);
//void petit_carre(GAME* game);
//int findIndice(GAME* game, int indiceInTemoin);
//bool IsInColumn(GAME* game, int lastLocked, int indiceTemoin);
//bool IsInRow(GAME* game, int LastLocked, int indiceTemoin);


solveur* newSolve(GAME* game);
int FindIndice(GAME* game, solveur* sylvain, int Indice);
void BottomRight(GAME* game, solveur* sylvain, int place);
int Solveur(GAME* game);
void placement(GAME* game, solveur* sylvain, int Indice);
void colonneDroite(GAME* game, solveur* sylvain);
void endgame(GAME* game, solveur* sylvain);
void dispSylvain(GAME* game, solveur* sylvain);
