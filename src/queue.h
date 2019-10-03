#define DELAY 10000

typedef struct node{
	struct node * next;
	void (*run)(char *);
}Node;


void setField(char * f);
void addNode(void (*run)(char *));
