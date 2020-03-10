#define DELAY 10000

typedef struct node{
	struct node * next;
	void (*run)(int *);
}Node;


void setField(int * f);
void addNode(void (*run)(int *));
