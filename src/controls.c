#include "controls.h"

#include <stdlib.h>
#include <ctype.h>

#include "tetro.h"
#include "score.h"
#include "field.h"
#include "queue.h"

void deleteTetroFromField(Tetro *tetro,int * field);

int moveTetro(Tetro * player, Vector2D * direction, int * field);

Tetro *spawnTetro(Tetro *tetro,int *field,int wasGrounded);
Tetro *spawn(int * field);
Tetro *manipulateField(Tetro *tetro,int * field,int tetroId, int wasGounded);

void checkResult(int result, int * field);
int checkBlock(Tetro * player,int * field, int x, int y,int yDirection);
int checkMovment(Tetro * player, Vector2D * direction, int * field);

void rotatePlayer(Tetro * player,int * field);
void rotatePlayerOnFreeCells(Tetro * player,int * field);
int checkRotate(Tetro * player,int * field);
int checkCell(Tetro * player ,int x, int y);

int calculateRandomTetroId();

void grounded(int * field);

void left(int * field);
void right(int * field);
void downToGround(int * field);
void rotate(int * field);
void hold(int *field);

int down_with_result(int * field);

extern char 
        DOWN_KEY,
        LEFT_KEY,
        RIGHT_KEY,
        ROTATE_KEY,
        QUIT_KEY,
        HOLD_KEY,
        DOWN_TO_GROUND_KEY;

Tetro * player;
Tetro * holded = NULL;

extern int isHolded;
extern int next = -1;
extern int isGameOver = 0;

extern void handleInput(int input,int  * field){
	
	input = toupper(input);
    
    if(input == LEFT_KEY){
		addNode(&left);
	}else if(input == RIGHT_KEY){
		addNode(&right);
	}else if(input == DOWN_KEY){
		addNode(&down);
		fall();
	}else if(input == ROTATE_KEY){
		addNode(&rotate);
	}else if(input == QUIT_KEY){
		isGameOver = 1;
	}else if(input == HOLD_KEY){
		addNode(&hold);
	}else if(input == DOWN_TO_GROUND_KEY){
		addNode(&downToGround);
	}
	
}

void hold(int  *field){
	Tetro * tmp;
	
	
	if(!isHolded){
		
		manipulateField(player,field,getEmptyIdentifier(),0);
		if(holded == NULL){
			holded = player;
			player = spawn(field);
		}else{
			tmp = player;
			player = holded;
			holded = tmp;

			player->pos->y = 0;
			player->pos->x = getMaxX()/2;
			spawnTetro(player,field,1);
		}
		
		isHolded = 1;
		setNameOfHolded(holded->name);
	}
	
}

extern void down (int *field){
	down_with_result(field);
}

int down_with_result(int * field){
	return moveTetro(player,createVector2D(0,1),field);
}

void downToGround(int * field){
	int result = FREE;
	while(result != GROUNDED){
		result = down_with_result(field);
		fall();
	}
}

void rotate(int *field){
	rotatePlayer(player,field);
}

void right(int * field){
	moveTetro(player,createVector2D(1,0),field);
}

void left(int * field){
	moveTetro(player,createVector2D(-1,0),field);
}

void rotatePlayer(Tetro * player,int * field){
	int result = checkRotate(player,field);

	if(result == FREE){
		rotatePlayerOnFreeCells(player,field); 
	}

	checkResult(result,field);
}

void rotatePlayerOnFreeCells(Tetro * player,int * field){
	int i;

	deleteTetroFromField(player,field);
	for(i = 0; i<MAX_BLOCKS;i++){
		rotateOnVector2DClockwise(player->block[i]->pos);
	}
	spawnTetro(player,field,0);  
}

int checkRotate(Tetro * player,int * field){
	int i,result;
	Vector2D * tmp;

	for(i = 0; i<MAX_BLOCKS;i++){
		tmp = rotateVector2DClockwise(player->block[i]->pos);
		addTwoVector2D_NotFreeAdded(tmp,player->pos);
        
        result = checkBlock(player,field,tmp->x,tmp->y,0);
		free(tmp);
        if (result != FREE){
			return result;
		}
	}
	return FREE;
}

int moveTetro(Tetro * player, Vector2D * direction, int  * field){
    int result;
	
    result = checkMovment(player,direction,field);

    if(result == FREE){
        deleteTetroFromField(player,field);
        addTwoVector2D(player->pos,direction);
        spawnTetro(player,field,0);
    }
    
    checkResult(result,field);

	return result;
	
}

Tetro *spawn(int * field){
	int num;
	
	if(next == -1){ /*next is empty*/
		num = calculateRandomTetroId();
	}else{
		num = next;
	}
	
	next = calculateRandomTetroId();
	
	isHolded = 0;
	
	switch(num){
		case I: return spawnTetro(createI(),field,1);
		case L: return spawnTetro(createL(),field,1);
		case J: return spawnTetro(createJ(),field,1);
		case T: return spawnTetro(createT(),field,1);
		case S: return spawnTetro(createS(),field,1);
		case O: return spawnTetro(createO(),field,1);
		default: return spawnTetro(createZ(),field,1);
	}
	
    
}

int calculateRandomTetroId(){
	return rand()%7;
}

void deleteTetroFromField(Tetro *tetro,int * field){
    manipulateField(tetro, field , getEmptyIdentifier(),0);
}

void spawnPlayer(int *field){
	player = spawn(field);
}

Tetro *spawnTetro(Tetro *tetro,int * field,int wasGrounded){
    return manipulateField(tetro,field,tetro->id,wasGrounded);
}

Tetro *manipulateField(Tetro *tetro,int * field,int tetroId, int wasGrounded){
    int i,x,y;
    Block *block;
	int * fieldStart = field;

    for(i = 0;i<MAX_BLOCKS;i++){
        block = tetro->block[i];
        x = block->pos->x;
        y = block->pos->y;
        x += tetro->pos->x;
        y += tetro->pos->y;

		
        field+= y*getMaxX()+x;
        if(wasGrounded && *field >= getBlockIdentifier()){
			isGameOver = 1;
			return tetro;
		}
        
        *field = tetroId;
        field = fieldStart;
    }
    return tetro;
}

void checkResult(int result, int * field){ 
	if(result == GROUNDED){
		grounded(field);
    }else if(result == GAME_OVER){
		isGameOver = 1;
	}
}

void grounded(int * field){
	deleteTetro(player);
    checkForLineClear(field);
    player = spawn(field);
}

int checkMovment(Tetro * player, Vector2D * direction, int * field){
    int i, x,y, result; 
	
    for(i = 0; i<MAX_BLOCKS;i++){
        x = player->pos->x;
        y = player->pos->y;
        x += player->block[i]->pos->x;
        y += player->block[i]->pos->y;
        
        x +=direction->x;
        y +=direction->y;
        
        result = checkBlock(player,field,x,y,direction->y);
        if (result != FREE){
			return result;
		}
        
    }
    return FREE;
}

int checkBlock(Tetro * player,int * field, int x, int y,int yDirection){
	
	int * startCell;
    startCell = field;
	
	if(x<0 || x>=getMaxX()){
		return BLOCKED;
	}else if (y<0){
		return BLOCKED;
	}else if(y>=getMaxY()){
		return GROUNDED;
	}
	
	field+=y*getMaxX()+x;
	if(*field != getEmptyIdentifier() && checkCell(player,x,y)){
		field = startCell;
		
		if(yDirection != 0){
			return GROUNDED;
		}
		return BLOCKED;
	}
	
	return FREE;
}

int checkCell(Tetro * player ,int x, int y){
    int i,bx,by;
    
    x -= player->pos->x;
    y -= player->pos->y;

    for(i = 0; i<MAX_BLOCKS;i++){
        bx = player->block[i]->pos->x;
        by = player->block[i]->pos->y;
        if(x == bx && y == by){
            return 0;
        }
    }
    return 1;
}