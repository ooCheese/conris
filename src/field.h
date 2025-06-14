
#ifndef FIELD_H
    #define FIELD_H
	
	#define GHOST_ID -2
		
	void setBlockLook(char n);
	void setEmptyLook(char n);
	char getBlockLook();
	char getEmptyLook();

	int getEmptyIdentifier();
	int getBlockIdentifier();

	int getMaxY();
	int getMaxX();
	void setFieldSize(int x, int y);
	void printField(int *field);
	int *createField ();
	void setNext(int *n);
	void printPreView(int count);
	void setControls(char cd,char cl, char cr,char cro,char cq, char ch,char cd2g);
	void deleteField(int * field);
	void setNameOfHolded(char name);
	void setColormode(int mode);

	void clearLine(int * field, int line);
	void checkForLineClear(int * field);
	void setFieldColor(char * colorname);
	
	int colorNameToNumber(char * colorname);

	void addGhostBlock(int x, int y);
	void clearGhostBlocks();
	void changeCell(int x, int y, int id);
	int * jumoToFieldPositon(int x , int y);
	
#endif
