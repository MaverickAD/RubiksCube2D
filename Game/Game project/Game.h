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


COLORS toColor(int value);
void display(GAME* game);
GAME * NewGame(int size);
int parseInput(GAME* game);
void fill(GAME* game);
int deplacementV(GAME* game, DIR direction, int indice);
int deplacementH(GAME* game, DIR direction, int indice);
bool win(GAME* game);
int parseInputMaker(GAME* game);