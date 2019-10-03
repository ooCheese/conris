#include "vector2d.h"

#define MAX_BLOCKS 4

typedef struct block{
    Vector2D * pos;
} Block;

typedef struct tetro{
    Vector2D * pos;
    Block * block[4];
}Tetro;

void setSpawnPos(int x);
void deleteTetro(Tetro * t);
Tetro *createTetro(Vector2D * blockPos[4]);
Tetro *createI();
Tetro *createL();
Tetro *createJ();
Tetro *createT();
Tetro *createZ();
Tetro *createS();




