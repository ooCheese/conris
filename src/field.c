#include "field.h"
#include "score.h"
#include <stdio.h>

static char field [MAX_FIELD_Y][MAX_FIELD_X];

int *nextP;
char viewNext();

char controlDown = ' ';
char controlLeft = ' ';
char controlRight = ' ';
char controlRotate = ' ';
char controlQuit = ' ';

extern void setNext(int *n){
	nextP = n;
}

extern void setControls(char cd,char cl, char cr,char cro,char cq){
	controlDown = cd;
	controlLeft = cl;
	controlRight = cr;
	controlRotate = cro;
	controlQuit = cq;
}

void printExtraInfos(int i){
	
	switch(i){
		case 1: printf("\t POINTS: %i",getPoints());break;
		case 2: printf("\t LINES: %i",getLines());break;
		case 3: printf("\t LEVEL: %i",getLvl());break;
		case 5: printf("\t NEXT: %c",viewNext());break;
		case 7: printf("\t |%c| LEFT",controlLeft);break;
		case 8: printf("\t |%c| RIGHT",controlRight);break;
		case 9: printf("\t |%c| DOWN",controlDown);break;
		case 10: printf("\t |%c| ROTATE",controlRotate);break;
		case 12: printf("\t |%c| QUIT",controlQuit);break;
	}
}

extern void printPreView(int count){
	int i,j;

    for(i = 0; i <MAX_FIELD_Y;i++){
        printf("|");
        for(j = 0; j <MAX_FIELD_X;j++){
			if(j == MAX_FIELD_X/2 && i ==MAX_FIELD_Y/2){
				printf("%i ",count);
			}else{
				printf("  ");
			}
            
        }	
		printf("|\n");
    }
    
    for(j = 0; j <MAX_FIELD_X;j++){
		printf("--");
    }
    printf("\n");
		
}

extern void printField(char *field){
    int i,j;

    for(i = 0; i <MAX_FIELD_Y;i++){
        printf("|");
        for(j = 0; j <MAX_FIELD_X;j++){
            printf("%c ", *field);
            field++;
        }
        printf("|");
        
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
    char * p;

    for(i = 0; i <MAX_FIELD_Y;i++){
        for(j = 0; j <MAX_FIELD_X;j++){
            field[i][j] = EMPTY_LOOK;
        }
        
    }

    p = *field;

    i = 0;
    return p;
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
            field++;
            if(*field == EMPTY_LOOK){
                isFull = 0;
            }
        }

        if(isFull){
            clearLine(field,i);
            count++;
        }
    }

    lineClears(count);

    field = startField;
}
