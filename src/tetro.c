#include "tetro.h"
#include "vector2d.h"
#include <stdio.h>
#include <stdlib.h>


int TETRO_COLORS [] = {I,L,J,T,S,Z};

extern void setTetroColors(int Ic,int Lc,int Jc,int Tc,int Sc, int Zc){
    TETRO_COLORS[I] = Ic;
    TETRO_COLORS[L] = Lc;
    TETRO_COLORS[J] = Jc;
    TETRO_COLORS[T] = Tc;
    TETRO_COLORS[S] = Sc;
    TETRO_COLORS[Z] = Zc;
}


int spawnPos = 0;

extern Tetro *createTetro(int id,char name,Vector2D * blockPos[MAX_BLOCKS]){
    int i;
    Tetro * tetro = malloc(sizeof(Tetro));
    
	tetro ->name = name;
    tetro -> id = id;
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
    blocks[1] = createVector2D(-1,0);
    blocks[2] = createVector2D(0,1);
    blocks[3] = createVector2D(1,0);
    return createTetro(TETRO_COLORS[T],'T',blocks);
}

extern Tetro *createL(){
	Vector2D *blocks [MAX_BLOCKS];

    blocks[0] = createVector2D(0,0);
    blocks[1] = createVector2D(0,1);
    blocks[2] = createVector2D(0,2);
    blocks[3] = createVector2D(1,2);
    return createTetro(TETRO_COLORS[L],'L',blocks);
}

extern Tetro *createJ(){
	Vector2D *blocks [MAX_BLOCKS];

    blocks[0] = createVector2D(0,0);
    blocks[1] = createVector2D(0,1);
    blocks[2] = createVector2D(0,2);
    blocks[3] = createVector2D(-1,2);
    return createTetro(TETRO_COLORS[J],'J',blocks);
}

extern Tetro *createZ(){
	Vector2D *blocks [MAX_BLOCKS];

    blocks[0] = createVector2D(0,0);
    blocks[1] = createVector2D(1,0);
    blocks[2] = createVector2D(0,1);
    blocks[3] = createVector2D(-1,1);
    return createTetro(TETRO_COLORS[Z],'Z',blocks);
}

extern Tetro *createS(){
	Vector2D *blocks [MAX_BLOCKS];

    blocks[0] = createVector2D(0,0);
    blocks[1] = createVector2D(-1,0);
    blocks[2] = createVector2D(0,1);
    blocks[3] = createVector2D(1,1);
    return createTetro(TETRO_COLORS[S],'S',blocks);
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
    return createTetro(TETRO_COLORS[I],'I',blocks);
}
