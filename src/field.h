
#ifndef FIELD_H
    #define FIELD_H
	
		
	void setBlockLook(char n);
	void setEmptyLook(char n);
	char getBlockLook();
	char getEmptyLook();

	char getEmptyIdentifier();
	char getBlockIdentifier();

	int getMaxY();
	int getMaxX();
	void setFieldSize(int x, int y);
	void printField(char *field);
	char *createField ();
	void setNext(int *n);
	void printPreView(int count);
	void setControls(char cd,char cl, char cr,char cro,char cq, char ch);
	void deleteField(char * field);
	void setNameOfHolded(char name);

	void clearLine(char * field, int line);
	void checkForLineClear(char * field);
	void setFieldColor(char * colorname);
	
#endif
