#include "field.h"
#include "score.h"
#include "tetro.h"
#include "ghostTetro.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

const char * CONSOLE_COLORS [] = {KNRM,KRED,KGRN,KYEL,KBLU,KMAG,KCYN,KWHT};
int * fieldp;
int *nextP;

static int colormode = 1;

char viewNext();
void printCell(int identifier);
void setCellColor(int identifier);
int checkLine(int * line);
void changeColor(const char * color);

void printRightBorder();
void printLeftBorder();

char controlDown = ' ';
char controlLeft = ' ';
char controlRight = ' ';
char controlRotate = ' ';
char controlQuit = ' ';
char controlHold = ' ';
char controlDownToGround = ' ';

char BLOCK_LOOK = '#';
char EMPTY_LOOK = ' ';
char GHOST_LOOK = '*';

const int EMPTY =  -1;
const int NORMAL_BLOCK = 0;

int fieldColorNumber = 0;

char nameOfHolded = ' ';

BlockList * ghostBlock  = NULL;


void setColormode(int mode){
    colormode = mode;
}

void setNameOfHolded(char name){
	nameOfHolded = name;
}

void setNext(int *n){
	nextP = n;
}

static int MAX_FIELD_X;
static int MAX_FIELD_Y;

void setFieldSize(int x, int y){
	MAX_FIELD_X = x;
	MAX_FIELD_Y = y;
	printf("fieldSize: %i %i \n",x,y);
}

 void setBlockLook(char n){
	BLOCK_LOOK = n;
}

 int getEmptyIdentifier(){
    return EMPTY;
}

 int getBlockIdentifier(){
    return NORMAL_BLOCK;
}

 void setEmptyLook(char n){
	EMPTY_LOOK = n;
}

 char getEmptyLook(){
	return EMPTY_LOOK;
}

 char getBlockLook(){
	return BLOCK_LOOK;
}

int getMaxY(){
	return MAX_FIELD_Y;
}

 int getMaxX(){
	return MAX_FIELD_X;
}

 void setFieldColor(char * colorname){
    fieldColorNumber = colorNameToNumber(colorname);
}

void setControls(char cd,char cl, char cr,char cro,char cq, char ch,char cd2g){
	controlDown = cd;
	controlLeft = cl;
	controlRight = cr;
	controlRotate = cro;
	controlQuit = cq;
	controlHold = ch;
    controlDownToGround = cd2g;
}

void deleteField(int * field){
	free(field);
}

int colorNameToNumber(char * colorname){
    if(strstr("NORMAL",colorname)){
        return 0;
    }else if(strstr("RED",colorname)){
        return 1;
    }else if(strstr("GREEN",colorname)){
        return 2;
    }else if(strstr("YELLOW",colorname)){
        return 3;
    }else if(strstr("BLUE",colorname)){
        return 4;
    }else if(strstr("MAGENTER",colorname)){
        return 5;
    }else if(strstr("CYAN",colorname)){
        return 6;
    }else if(strstr("WHITE",colorname)){
         return 7;
    }

    return 0;
}

void changeColor(const char * color){
    if(colormode){
        printf("%s",color);
    }
}

void printExtraInfos(int i){
	
	switch(i){
		case 1: printf("\t POINTS: %i",getPoints());break;
		case 2: printf("\t LINES: %i",getLines());break;
		case 3: printf("\t LEVEL: %i",getLvl());break;
		case 5: printf("\t NEXT: %c",viewNext());break;
		case 6: printf("\t HOLD: %c",nameOfHolded);break;
		case 8: printf("\t |%c| LEFT",controlLeft);break;
		case 9: printf("\t |%c| RIGHT",controlRight);break;
		case 10: printf("\t |%c| DOWN",controlDown);break;
        case 11: printf("\t |%c| DOWN TO GROUND",controlDownToGround);break;
		case 12: printf("\t |%c| ROTATE",controlRotate);break;
		case 13: printf("\t |%c| HOLD",controlHold);break;
		case 15: printf("\t |%c| QUIT",controlQuit);break;
	}
}

void printLeftBorder(){
    changeColor(KNRM);
    printf("|");
    changeColor(CONSOLE_COLORS[fieldColorNumber]);
}

void printRightBorder(){
    changeColor(KNRM);
    printf("|");
}

void printPreView(int count){
	int i,j;
	

    for(i = 0; i <MAX_FIELD_Y;i++){
        printLeftBorder();
        for(j = 0; j <MAX_FIELD_X;j++){
			if(j == MAX_FIELD_X/2 && i ==MAX_FIELD_Y/2){
				printf("%i ",count);
			}else{
				printf("  ");
			}
            
        }	
		printRightBorder();
        printf("\n");
    }
    
    for(j = 0; j <MAX_FIELD_X;j++){
		printf("--");
    }
    printf("\n");
		
}

void printField(int *field){
    int i,j;

    for(i = 0; i <MAX_FIELD_Y;i++){
        printLeftBorder();
        for(j = 0; j <MAX_FIELD_X;j++){

            printCell(*field);
            
            field++;
        }
        printRightBorder();
        
        printExtraInfos(i);
		printf("\n");
    }
    
    for(j = 0; j <MAX_FIELD_X;j++){
		printf("--");
    }
    printf("\n");
}

void printCell(int identifier){
    
    if(identifier > EMPTY){
        setCellColor(identifier);

        printf("%c ",BLOCK_LOOK);

        /*reset Color*/
        changeColor(CONSOLE_COLORS[fieldColorNumber]);
        
    }else if(identifier == GHOST_ID){
        printf("%c ", GHOST_LOOK);
    }else{
        printf("%c ", EMPTY_LOOK);
    }
}

void setCellColor(int identifier){
    changeColor(CONSOLE_COLORS[identifier]);
}

char viewNext(){
	
	switch(*nextP){
		case I: return 'I';
		case L: return 'L';
		case J: return 'J';
		case T: return 'T';
		case S: return 'S';
		case Z: return 'Z';
        case O: return 'O';
		default: return ' ';
	}
}

int *createField (){
    int i,j;
    int * p, * tmp;
    
    p = malloc(sizeof(int )*MAX_FIELD_X*MAX_FIELD_Y);
    
    tmp = p;

    for(i = 0; i <MAX_FIELD_Y;i++){
        for(j = 0; j <MAX_FIELD_X;j++){
            *p = EMPTY;
            p++;
        }
        
    }

    return tmp;
}

void clearLine(int * field, int line){
    int i,j;
    int * prevCell;
    prevCell = field;
    prevCell -= MAX_FIELD_X;

    for(i = line;i>0;i--){
        for(j = 0; j<MAX_FIELD_X;j++){
            field--;
            prevCell--;
            *field = *prevCell;
        }
    }

    /*last line*/
    for(j = 0; j<MAX_FIELD_X;j++){
        field--;
        *field = EMPTY;
    }

}

void checkForLineClear(int * field){
    int i,isFull,count = 0;
    int * startField;

    startField = field;

    for(i = 0;i<MAX_FIELD_Y;i++){
		isFull = checkLine(field);
        field += MAX_FIELD_X;

        if(isFull){
            clearLine(field,i);
            count++;
        }
    }

    lineClears(count);

    field = startField;
}

int checkLine(int * line){
    int i;

    for (i = 0;i<MAX_FIELD_X;i++){
			
        if(*line < NORMAL_BLOCK){
            return 0;
        }
        line++;
    }
    return 1;
}

void clearGhostBlocks(){
    BlockList * tmp;

    while(ghostBlock != NULL){
        tmp = ghostBlock-> next;
        changeCell(ghostBlock->x,ghostBlock->y,EMPTY);
        free(ghostBlock);
        ghostBlock = tmp;
    }
}

void addGhostBlock(int x, int y){

    if(y < MAX_FIELD_Y && y >= 0){
        changeCell(x,y,GHOST_ID);
        ghostBlock = createGhostBlock(x,y,ghostBlock);
    } 
}
    

void changeCell(int x, int y, int id){
    int * pos = jumoToFieldPositon(x,y);
    *pos = id;
}

int * jumoToFieldPositon(int x , int y){
    return fieldp + (y*MAX_FIELD_X)+x;
}