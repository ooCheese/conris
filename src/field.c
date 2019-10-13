#include "field.h"
#include "score.h"
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


char * fieldp;

int *nextP;
char viewNext();

char controlDown = ' ';
char controlLeft = ' ';
char controlRight = ' ';
char controlRotate = ' ';
char controlQuit = ' ';
char controlHold = ' ';

char BLOCK_LOOK = '#';
char EMPTY_LOOK = ' ';

char nameOfHolded = ' ';


extern void setNameOfHolded(char name){
	nameOfHolded = name;
}

extern void setNext(int *n){
	nextP = n;
}

static int MAX_FIELD_X;
static int MAX_FIELD_Y;

extern void setFieldSize(int x, int y){
	MAX_FIELD_X = x;
	MAX_FIELD_Y = y;
	printf("fieldSize: %i %i \n",x,y);
}

extern void setBlockLook(char n){
	BLOCK_LOOK = n;
}

extern void setEmptyLook(char n){
	EMPTY_LOOK = n;
}

extern char getEmptyLook(){
	return EMPTY_LOOK;
}

extern char getBlockLook(){
	return BLOCK_LOOK;
}

extern int getMaxY(){
	return MAX_FIELD_Y;
}

extern int getMaxX(){
	return MAX_FIELD_X;
}


extern void setControls(char cd,char cl, char cr,char cro,char cq, char ch){
	controlDown = cd;
	controlLeft = cl;
	controlRight = cr;
	controlRotate = cro;
	controlQuit = cq;
	controlHold = ch;
}

extern void * deleteField(char * field){
	free(field);
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
		case 11: printf("\t |%c| ROTATE",controlRotate);break;
		case 12: printf("\t |%c| HOLD",controlHold);break;
		case 14: printf("\t |%c| QUIT",controlQuit);break;
	}
}

extern void printPreView(int count){
	int i,j;
	

    for(i = 0; i <MAX_FIELD_Y;i++){
        printf("%s|%s",KNRM,KCYN);
        for(j = 0; j <MAX_FIELD_X;j++){
			if(j == MAX_FIELD_X/2 && i ==MAX_FIELD_Y/2){
				printf("%i ",count);
			}else{
				printf("  ");
			}
            
        }	
		printf("%s|\n",KNRM);
    }
    
    for(j = 0; j <MAX_FIELD_X;j++){
		printf("--");
    }
    printf("\n");
		
}

extern void printField(char *field){
    int i,j;

    for(i = 0; i <MAX_FIELD_Y;i++){
        printf("%s|%s",KNRM,KCYN);
        for(j = 0; j <MAX_FIELD_X;j++){
            printf("%c ", *field);
            field++;
        }
        printf("%s|",KNRM);
        
        printExtraInfos(i);
		
		printf("\n");
    }
    
    for(j = 0; j <MAX_FIELD_X;j++){
		printf("--");
    }
    printf("\n");
}

char viewNext(){
	
	switch(*nextP){
		case I: return 'I';
		case L: return 'L';
		case J: return 'J';
		case T: return 'T';
		case S: return 'S';
		case Z: return 'Z';
		default: return ' ';
	}
}

extern char *createField (){
    int i,j;
    char * p, * tmp;
    
    p = malloc(sizeof(char)*MAX_FIELD_X*MAX_FIELD_Y);
    
    tmp = p;

    for(i = 0; i <MAX_FIELD_Y;i++){
        for(j = 0; j <MAX_FIELD_X;j++){
            *p = EMPTY_LOOK;
            p++;
        }
        
    }

    return tmp;
}

extern void clearLine(char * field, int line){
    int i,j;
    char * prevCell;
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
        *field = EMPTY_LOOK;
    }

}

extern void checkForLineClear(char * field){
    int i,j,isFull,count = 0;
    char * startField;

    startField = field;

    for(i = 0;i<MAX_FIELD_Y;i++){
		isFull = 1;
        for (j = 0;j<MAX_FIELD_X;j++){
			
            if(*field != BLOCK_LOOK){
                isFull = 0;
            }
            field++;
        }

        if(isFull){
            clearLine(field,i);
            count++;
        }
    }

    lineClears(count);

    field = startField;
}
