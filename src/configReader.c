#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "configReader.h"

#define MAX_LINE_LENGTH 50

typedef struct keywordNode{
	char keyword [MAX_KEY_WORD];
	char value [MAX_KEY_VALUE];
	struct keywordNode * next;
	
}KeyWordNode;

KeyWordNode * confhead = NULL;

void addKeyWord(char * keyword, char  * value);
void analyzeLine(char * line);
char * findByKey(char  * keyword);

extern int readConfig(char * path){
	FILE * file;
	char line [MAX_LINE_LENGTH];
	
	if((file = fopen(path,"r")) == NULL){
		return 0;
	}
	while(fgets(line,MAX_LINE_LENGTH,file)){
		analyzeLine(line);
	}
	
	fclose(file);
	return 1;
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
		}else if(isalnum(*line) || *line== '.'){
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

extern char getCharProp(char * keyword,char def){
	char * p;
	
	p = findByKey(keyword);
	
	while(*p != '\0'){
		if(isalpha(*p)){
			return *p;
		}
		p++;
	}
	
	return def;
}

extern int getIntProp(char * keyword, int def){
	char * p;
	int out = 0;
	
	while(*p != '\0'){
		if(isdigit(*p)){
			out*= 10;
			out+= *p - '0';
		}
		p++;
	}
	
	if(out == 0){
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

extern void deleteAllConfigProps(){
	KeyWordNode * tmp, * tmpold;
	
	tmp = confhead;
	while(tmp != NULL){
		tmpold = tmp;
		tmp = tmp->next;
		free(tmpold);
	}
}
