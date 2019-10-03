
#ifndef FIELD_H
    #define FIELD_H
    
	#define BLOCK_LOOK '#'
	#define EMPTY_LOOK ' '
	#define MAX_FIELD_X 10
	#define MAX_FIELD_Y 20

	#define I 0
	#define L 1
	#define J 2
	#define T 3
	#define S 4
	#define Z 5

	void printField(char *field);
	char *createField ();
	void setNext(int *n);
	void printPreView(int count);
	void setControls(char cd,char cl, char cr,char cro,char cq);

	void clearLine(char * field, int line);
	void checkForLineClear(char * field);
#endif
