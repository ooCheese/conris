#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "configReader.h"

#define MAX_LINE_LENGTH 80

typedef struct keywordNode{
	char keyword [MAX_KEY_WORD];
	char value [MAX_KEY_VALUE];
	struct keywordNode * next;
	
}KeyWordNode;

KeyWordNode * confhead = NULL;


void analyzeFile(FILE * file);
void analyzeLine(char * line);

void addKeyWord(char * keyword, char  * value);
char * findByKey(char  * keyword);
int filterInt(char *p,int def);

int readConfig(char * path){
	FILE * file;
	
	if((file = fopen(path,"r")) == NULL){
		return 0;
	}
	
	analyzeFile(file);
	return 1;
}

void analyzeFile(FILE * file){
	char line [MAX_LINE_LENGTH];
	
	while(fgets(line,MAX_LINE_LENGTH,file)){
		analyzeLine(line);
	}
	
	fclose(file);
}

void analyzeLine(char * line){
	char * wordP;
	char keyword[MAX_KEY_WORD];
	char value [MAX_KEY_VALUE];
	
	wordP = keyword;
	
	while(*line != '\0'){
		if(*line == '='){
			*wordP = '\0';
			wordP = value;
		}else if(*line != ' '&&*line>='!'){
			*wordP = *line;
			wordP++;
		}
		line++;
	}
	*wordP = '\0';
	
	addKeyWord(keyword, value);
	
}

void addKeyWord(char * keyword, char * value){
	KeyWordNode * tmp;
	KeyWordNode * new= malloc(sizeof(KeyWordNode));
	
	new->next = NULL;
	
	strcpy(new->keyword,keyword);
	strcpy(new->value,value );
	
	if(confhead == NULL){
		confhead = new;
	}else{
		
		tmp = confhead;
		while(tmp->next != NULL){
			tmp = tmp->next;
		}
	
		tmp->next = new;
	}
	
}

int getBoolProp(char * keyword, char def){
	char * p;
	
	p = findByKey(keyword);
	
	if(strstr("true",p) != NULL){
		return 1;
	}else if(strstr("false",p) != NULL){
		return 0;
	}
	
	
	return def;
}

char * getStringProp(char * keyword,char * def){
	char * value;

	value  = findByKey(keyword);
	if (value == NULL){
		return def;
	}
	return value;
}

char getCharProp(char * keyword,char def){
	char * p, * tmp;
	
	p = findByKey(keyword);
	
	if(*p == '\\'){
		tmp = p;
		tmp++;
		if(isdigit(*tmp)){
			return (char)filterInt(tmp,def);
		}
	}
	
	while(*p != '\0'){
		if(*p != ' '&&*p>='!'){
			return *p;
		}
		p++;
	}
	
	return def;
}

int getIntProp(char * keyword, int def){
	char * p;
	
	p = findByKey(keyword);
	return filterInt(p,def);
	
}

int filterInt(char *p,int def){
	int out = 0;
	int countNum = 0;
	
	while(*p != '\0'){
		if(isdigit(*p)){
			countNum++;
			out*= 10;
			out+= *p - '0';
		}
		p++;
	}
	
	if(countNum == 0){
		return def;
	}
	
	return out;
}


char * findByKey(char * keyword){
	KeyWordNode * tmp;
	char * p;
	
	tmp = confhead;
	while(tmp != NULL ){
		if(strcmp(tmp->keyword,keyword) == 0){
			p = tmp->value;
			return p;
		}
		
		tmp = tmp->next;
	}
	
	return NULL;
	
}

void deleteAllConfigProps(){
	KeyWordNode * tmp, * tmpold;
	
	tmp = confhead;
	while(tmp != NULL){
		tmpold = tmp;
		tmp = tmp->next;
		free(tmpold);
	}
}
