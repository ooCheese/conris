
#ifndef FIELD_H
    #define FIELD_H
	
		
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
	void setControls(char cd,char cl, char cr,char cro,char cq, char ch);
	void deleteField(int * field);
	void setNameOfHolded(char name);

	void clearLine(int * field, int line);
	void checkForLineClear(int * field);
	void setFieldColor(char * colorname);
	
#endif
