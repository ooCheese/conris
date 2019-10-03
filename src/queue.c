#include "queue.h"
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


char * field;
Node * head = NULL;
int isAlive = 0;
pthread_t thread;

static void * startQueue(void * vargp);

extern void setField(char * f){
	field = f;
}

extern void addNode(void (*run)(char *)){
	Node * new = malloc(sizeof(Node));
	
	new->next = NULL;
	new->run = run;
	
	if(head == NULL){
		head = new;
		pthread_create(&thread, NULL, &startQueue, NULL);
		
	}else{
		head->next = new;
	}
}

static void * startQueue(void * vargp){
	Node *tmp;
	
	while(head != NULL){
		head->run(field);
		tmp = head->next;
		free(head);
		head = tmp;
		usleep(DELAY);
	}
	
	return NULL;
}
