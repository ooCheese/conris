#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <assert.h>
#include <curses.h>
#include <time.h>
#include <unistd.h>

#include "vector2d.h"
#include "tetro.h"
#include "score.h"
#include "field.h"
#include "queue.h"
#include "readSingelChar.h"
#include "configReader.h"

#define MAX_BLOCKS 4

#define WAIT_IN_INTRO_SEC 1

#define BLOCKED 0
#define FREE 1
#define GROUNDED -1
#define GAME_OVER -2
#define WRONG_INPUT -3


Tetro *spawnTetro(Tetro *tetro,int *field,int wasGrounded);
Tetro *spawn(int * field);
Tetro *manipulateField(Tetro *tetro,int * field,int tetroId, int wasGounded);
void deleteTetroFromField(Tetro *tetro,int * field);

void moveTetro(Tetro * player, Vector2D * direction, int * field);
int checkMovment(Tetro * player, Vector2D * direction, int * field);
int checkCell(Tetro * tetro ,int x, int y);

int checkBlock(Tetro * player,int * field, int x, int y,int yDirection);
int checkRotate(Tetro * player,int * field);
int gameLoop(int * field);

void playerControl(Tetro * player,int * field);
void handleInput(int input,int * field);

void rotatePlayer(Tetro * player,int * field);
void checkResult(int result, int * field);
void grounded(int * field);

void left(int * field);
void right(int * field);
void down(int * field);
void rotate(int * field);
void hold(int *field);
void gameover();

void createGhoast();

void loadConfig();

static void *playerTurn(void * vargp);
static void *systemTurn(void * vargp);
static void *printLoop(void * vargp);

void printIntroduction();
void countDown();

static char DOWN_KEY = 'S',LEFT_KEY= 'A',RIGHT_KEY = 'D',ROTATE_KEY = 'W',QUIT_KEY = '.',HOLD_KEY = 'H';
static int PRINT_SLEEP = 100000;

static Tetro * player;
static int isGameOver = 0;
static int * field;

int next = -1;
int countdownOn = 1;
int isHolded = 0;
int ENABLE_GHOST_BLOCKS = 0;


int COUNT_DOWN = 3;
int COUNT_DOWN_SLEEP = 1;

pthread_t playerThread;
pthread_t fallThread;
pthread_t printThread;

Tetro * holded = NULL;


int main(void){
	
	loadConfig();
    field = createField();
    setField(field);
    setSpawnPos(getMaxX()/2);
    setNext(&next);
    setControls(DOWN_KEY,LEFT_KEY,RIGHT_KEY,ROTATE_KEY,QUIT_KEY,HOLD_KEY);
    return gameLoop(field);
}

void loadConfig(){
	if(readConfig("config.properties")){
		
		DOWN_KEY =  getCharProp("key.down",'S');
		LEFT_KEY =  getCharProp("key.left",'A');
		RIGHT_KEY =  getCharProp("key.right",'D');
		ROTATE_KEY = getCharProp("key.rotate",'R');
		QUIT_KEY =  getCharProp("key.quit",'.');
		HOLD_KEY = getCharProp("key.hold",'H');
		PRINT_SLEEP = 1e6/getIntProp("speed.print",15);
		ENABLE_GHOST_BLOCKS = getBoolProp("gostblocks",0);
		setFieldSize(getIntProp("field.x",10),getIntProp("field.y",20));
		countdownOn = getBoolProp("start.countdown",1);
		COUNT_DOWN = getIntProp("start.countdown.counts",3);
		COUNT_DOWN_SLEEP = getIntProp("start.countdown.seconds",1);
		setEmptyLook(getCharProp("look.empty",' '));
		setBlockLook(getCharProp("look.block",'#'));
		setFieldColor(getStringProp("color.field","NORMAL"));

		setTetroColors(
			colorNameToNumber(getStringProp("color.I","NORMAL")),
			colorNameToNumber(getStringProp("color.L","NORMAL")),
			colorNameToNumber(getStringProp("color.J","NORMAL")),
			colorNameToNumber(getStringProp("color.T","NORMAL")),
			colorNameToNumber(getStringProp("color.S","NORMAL")),
			colorNameToNumber(getStringProp("color.Z","NORMAL"))
		);
		
		deleteAllConfigProps();
	}
	
}

int gameLoop(int * field){
	int rc;

    player = spawn(field);
    
    printIntroduction();
    if(countdownOn){
		countDown();
	}
	
    printf("\n*** START ***\n\n");
    
    rc = pthread_create(&playerThread, NULL, playerTurn, NULL);
    assert(!rc);
    
    rc = pthread_create(&fallThread, NULL, systemTurn, NULL);
    assert(!rc);
	
	rc = pthread_create(&printThread, NULL, printLoop, NULL);
    assert(!rc);

	pthread_join(playerThread, NULL );
    pthread_join(fallThread, NULL );
    pthread_join(printThread, NULL );
    addNode(&deleteField);
    gameover();
    
    return EXIT_SUCCESS;
}

void gameover(){
	printf("\n*** GAME OVER ***\n\n");
	printf("POINTS: \t%5i \n",getPoints());
	printf("LINES: \t%5i \n",getLines());
	printf("LEVEL: \t%5i \n",getLvl());
	
}

void printIntroduction(){
	printf("\n *** CONRIS ***\n\n");
	
	sleep(WAIT_IN_INTRO_SEC);
	
}

void countDown(){
	int i;
	
	for(i = COUNT_DOWN; i > 0 ;i--){
		printPreView(i);
		sleep(COUNT_DOWN_SLEEP);
	}
}

static void *playerTurn(void * vargp){
	
	printField(field);
	 while(!isGameOver){
		playerControl(player,field);
    }
    
    return NULL;
}

static void *systemTurn(void * vargp){
	
	while(!isGameOver){
		usleep(getSpeed());
		addNode(&down);
    }
	
	return NULL;
}

static void *printLoop(void * vargp){
	
	while(!isGameOver){
		printField(field);
		usleep(PRINT_SLEEP);
	}
	
	return NULL;
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

void playerControl(Tetro * player,int * field){
    int input;

    #ifdef __GNUC__
		input = getchLINUX(0); /*only works on linux*/
    #endif
    
    #ifdef _WIN32
		input = getch(); /*only Works on Windows ()input = getch();*/
    #endif
    
    
	handleInput(input,field);

}

void handleInput(int input,int  * field){
	
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
		}
		
		isHolded = 1;
		setNameOfHolded(holded->name);
	}
	
}

void down (int *field){
	moveTetro(player,createVector2D(0,1),field);
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
	int i,x,y,result;
	
	result = checkRotate(player,field);
	if(result == FREE){
		for(i = 0; i<MAX_BLOCKS;i++){
			deleteTetroFromField(player,field);
			
			x = player->block[i]->pos->y;
			y = player->block[i]->pos->x;
			player->block[i]->pos->x = x*-1;
			player->block[i]->pos->y = y;
			
			spawnTetro(player,field,0);  
		}
	}
	checkResult(result,field);
}

int checkRotate(Tetro * player,int * field){
	int i,x,y,result;
	for(i = 0; i<MAX_BLOCKS;i++){
        x = player->block[i]->pos->y;
        y = player->block[i]->pos->x;
        x*=-1;
        x += player->pos->x;
        y += player->pos->y;
        
        result = checkBlock(player,field,x,y,0);
        if (result != FREE){
			return result;
		}
	}
	return FREE;
}

void moveTetro(Tetro * player, Vector2D * direction, int  * field){
    int result;
	
    result = checkMovment(player,direction,field);

    if(result == FREE){
        deleteTetroFromField(player,field);
        addTwoVector2D(player->pos,direction);
        spawnTetro(player,field,0);
    }
    
    checkResult(result,field);

	if(ENABLE_GHOST_BLOCKS){
		createGhoast();
	}
	
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

Tetro *spawn(int * field){
	int num;
	
	if(next == -1){ /*next is empty*/
		num = rand()%6;
	}else{
		num = next;
	}
	
	next = rand()%6;
	
	isHolded = 0;
	
	switch(num){
		case I: return spawnTetro(createI(),field,1);
		case L: return spawnTetro(createL(),field,1);
		case J: return spawnTetro(createJ(),field,1);
		case T: return spawnTetro(createT(),field,1);
		case S: return spawnTetro(createS(),field,1);
		default: return spawnTetro(createZ(),field,1);
	}
	
    
}

void deleteTetroFromField(Tetro *tetro,int * field){
    manipulateField(tetro, field , getEmptyIdentifier(),0);
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


void createGhoast(){
	int i,y,result;
	Vector2D * pos;

	clearGhostBlocks();

	for(i = 0;i<MAX_BLOCKS;i++){
		pos = player->block[i]->pos;
		y = pos-> y +1;

		while(checkCell(player,pos->x,y)== FREE){
			y++;
		}

		y = y-1;

		if(y != pos->y){
			addGhostBlock(pos->x,y);
		}
		
		
	}
}