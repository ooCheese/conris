#include "movment.h"
#include "field.h"
#include "tetro.h"

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