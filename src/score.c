#include "score.h"

#define POINTS_FOR_LINE 10
#define CONRIS_BONUS 50
#define POINTS_PER_FALL 1
#define BASE_LINES_FOR_NEXT_LVL 4
#define LVL_FACTOR 2
#define BASE_SLEEP 500000
#define SPEED_FACTOR 1000

int points = 0;
int lines = 0; 
int lvl = 0;
int linesForNextLvl = BASE_LINES_FOR_NEXT_LVL;
int speed = BASE_SLEEP;

void calculateSpeed();
void nextLvl();

void lineClears(int num){

    if(num == 4){
        points += CONRIS_BONUS;
    }
	
    points += POINTS_FOR_LINE * num;
    lines += num; 
    
    if(lines >= linesForNextLvl){
		nextLvl();
	}
}

void nextLvl(){
	
	linesForNextLvl = (int)(linesForNextLvl * LVL_FACTOR);
	lvl++;
	calculateSpeed();
}

void fall(){
    points+= POINTS_PER_FALL;
}

void calculateSpeed(){
	speed = BASE_SLEEP -(getLvl()*SPEED_FACTOR);
}

int getSpeed(){
	return speed;
}

int getLvl(){
	return lvl;
}

int getLines(){
    return lines;
}

int getPoints(){
    return points;
}
