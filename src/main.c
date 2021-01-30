#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
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
#include "controls.h"

#define MAX_BLOCKS 4

#define WAIT_IN_INTRO_SEC 1


int gameLoop(int * field);

void createGhoast();

void loadConfig();
void loadPrintConfig();
void loadGhostBlockConfig();
void loadFieldConfig();
void loadKeyConfig();
void loadCountDownConfig();
void loadColorConfig();
void loadRandConfig();

static void *playerTurn(void * vargp);
static void *systemTurn(void * vargp);
static void *printLoop(void * vargp);

void printIntroduction();
void playerControl(int * field);
void countDown();
void gameover();

static int PRINT_SLEEP = 100000;

static int * field;

int countdownOn = 1;

int COUNT_DOWN = 3;
int COUNT_DOWN_SLEEP = 1;

pthread_t playerThread;
pthread_t fallThread;
pthread_t printThread;


int main(void){
	
	loadConfig();
    field = createField();
    setField(field);
    setSpawnPos(getMaxX()/2);
    setNext(&next);
    setControls(DOWN_KEY,LEFT_KEY,RIGHT_KEY,ROTATE_KEY,QUIT_KEY,HOLD_KEY,DOWN_TO_GROUND_KEY);
    return gameLoop(field);
}

int gameLoop(int * field){
	int rc;

    spawnPlayer(field);
    
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
	waitforQueue();
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
		playerControl(field);
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

void playerControl(int * field){
    int input;

    #ifdef __GNUC__
		input = getchLINUX(0); /*only works on linux*/
    #endif
    
    #ifdef _WIN32
		input = getch(); /*only Works on Windows ()input = getch();*/
    #endif
    
    
	handleInput(input,field);

}

void loadConfig(){
	if(readConfig("config.properties")){
		
		loadFieldConfig();
		loadKeyConfig();
		loadCountDownConfig();
		loadPrintConfig();
		loadColorConfig();
		loadGhostBlockConfig();
		loadRandConfig();

		deleteAllConfigProps();
	}
}

void loadPrintConfig(){
	PRINT_SLEEP = 1e6/getIntProp("speed.print",15);
}

void loadGhostBlockConfig(){
	ghostMode = getBoolProp("ghostblocks",0);
}

void loadFieldConfig(){
	setFieldSize(getIntProp("field.x",10),getIntProp("field.y",20));

	setEmptyLook(getCharProp("look.empty",' '));
	setBlockLook(getCharProp("look.block",'#'));
}

void loadKeyConfig(){
	DOWN_KEY =  getCharProp("key.down",'S');
	LEFT_KEY =  getCharProp("key.left",'A');
	RIGHT_KEY =  getCharProp("key.right",'D');
	ROTATE_KEY = getCharProp("key.rotate",'R');
	QUIT_KEY =  getCharProp("key.quit",'.');
	HOLD_KEY = getCharProp("key.hold",'H');
	DOWN_TO_GROUND_KEY = getCharProp("key.down2ground",' ');
}

void loadCountDownConfig(){
	countdownOn = getBoolProp("start.countdown",1);
	COUNT_DOWN = getIntProp("start.countdown.counts",3);
	COUNT_DOWN_SLEEP = getIntProp("start.countdown.seconds",1);
}

void loadColorConfig(){
	setColormode(getBoolProp("color.mode",1));
	setFieldColor(getStringProp("color.field","NORMAL"));

	setTetroColors(
		colorNameToNumber(getStringProp("color.I","NORMAL")),
		colorNameToNumber(getStringProp("color.L","NORMAL")),
		colorNameToNumber(getStringProp("color.J","NORMAL")),
		colorNameToNumber(getStringProp("color.T","NORMAL")),
		colorNameToNumber(getStringProp("color.S","NORMAL")),
		colorNameToNumber(getStringProp("color.Z","NORMAL")),
		colorNameToNumber(getStringProp("color.O","NORMAL"))
	);
}

void loadRandConfig(){

	if(getBoolProp("rand.seedbytime",1)){
		srand(time(NULL));
	}else{
		srand((unsigned int)getIntProp("rand.seed",1));
	}
}