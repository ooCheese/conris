
#ifndef TETRO_H
    #define TETRO_H
	
#include "vector2d.h"

#define MAX_BLOCKS 4

#define I 0
#define L 1
#define J 2
#define T 3
#define S 4
#define Z 5
#define O 6


typedef struct block{
    Vector2D * pos;
} Block;

typedef struct tetro{
    Vector2D * pos;
    char name;
    int id;
    Block * block[4];
}Tetro;

void setSpawnPos(int x);
void setTetroColors(int Ic,int Lc,int Jc,int Tc,int Sc, int Zc,int Oc);

void copyBlocks(Tetro * source, Tetro * target);

int calcMinY(Tetro * tetro);

void deleteTetro(Tetro * t);
Tetro *createTetro(int id,char name,Vector2D * blockPos[4]);
Tetro *createGhostTetro(int id,char name);
Tetro *createI();
Tetro *createL();
Tetro *createJ();
Tetro *createT();
Tetro *createZ();
Tetro *createS();
 Tetro *createO();

#endif



