#include "tetro.h"
#include "vector2d.h"
#include <stdio.h>
#include <stdlib.h>


int spawnPos = 0;

extern Tetro *createTetro(Vector2D * blockPos[MAX_BLOCKS]){
    int i;
    Tetro * tetro = malloc(sizeof(Tetro));

    tetro ->pos = createVector2D(spawnPos,0);
    for(i = 0;i<MAX_BLOCKS;i++){
        tetro->block[i] = malloc(sizeof(Block));
        tetro->block[i]->pos = blockPos[i];

    }
    
    return tetro;
}

extern void setSpawnPos(int x){
    spawnPos = x;
}

extern Tetro *createT(){
	Vector2D *blocks [MAX_BLOCKS];

    blocks[0] = createVector2D(0,0);
    blocks[1] = createVector2D(0,-1);
    blocks[2] = createVector2D(0,1);
    blocks[3] = createVector2D(1,0);
    return createTetro(blocks);
}

extern Tetro *createL(){
	Vector2D *blocks [MAX_BLOCKS];

    blocks[0] = createVector2D(0,0);
    blocks[1] = createVector2D(0,1);
    blocks[2] = createVector2D(0,2);
    blocks[3] = createVector2D(1,2);
    return createTetro(blocks);
}

extern Tetro *createJ(){
	Vector2D *blocks [MAX_BLOCKS];

    blocks[0] = createVector2D(0,0);
    blocks[1] = createVector2D(0,1);
    blocks[2] = createVector2D(0,2);
    blocks[3] = createVector2D(-1,2);
    return createTetro(blocks);
}

extern Tetro *createZ(){
	Vector2D *blocks [MAX_BLOCKS];

    blocks[0] = createVector2D(0,0);
    blocks[1] = createVector2D(1,0);
    blocks[2] = createVector2D(0,1);
    blocks[3] = createVector2D(-1,1);
    return createTetro(blocks);
}

extern Tetro *createS(){
	Vector2D *blocks [MAX_BLOCKS];

    blocks[0] = createVector2D(0,0);
    blocks[1] = createVector2D(-1,0);
    blocks[2] = createVector2D(0,1);
    blocks[3] = createVector2D(1,1);
    return createTetro(blocks);
}

extern void deleteTetro(Tetro * t){
	int i;
	
	free(t->pos);
	for(i = 0;i<MAX_BLOCKS;i++){
		free(t->block[i]->pos);
		free(t->block[i]);
	}
	free(t);
}
	

extern Tetro *createI(){
    Vector2D *blocks [MAX_BLOCKS];

    blocks[0] = createVector2D(0,0);
    blocks[1] = createVector2D(0,1);
    blocks[2] = createVector2D(0,2);
    blocks[3] = createVector2D(0,3);
    return createTetro(blocks);
}
