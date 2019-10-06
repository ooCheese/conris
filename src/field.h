
#ifndef FIELD_H
    #define FIELD_H

	#define I 0
	#define L 1
	#define J 2
	#define T 3
	#define S 4
	#define Z 5
	
	void setBlockLook(char n);
	void setEmptyLook(char n);
	char getBlockLook();
	char getEmptyLook();
	int getMaxY();
	int getMaxX();
	void setFieldSize(int x, int y);
	void printField(char *field);
	char *createField ();
	void setNext(int *n);
	void printPreView(int count);
	void setControls(char cd,char cl, char cr,char cro,char cq);

	void clearLine(char * field, int line);
	void checkForLineClear(char * field);
#endif
