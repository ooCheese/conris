#ifndef CONFIGREADER_H
    #define CONFIGREADER_H
    
	#define MAX_KEY_WORD 40
	#define MAX_KEY_VALUE 40

	int readConfig();
	char getCharProp(char * keyword,char def);
	int getIntProp(char * keyword, int def);
	void deleteAllConfigProps();
	int getBoolProp(char * keyword, char def);
	char * getStringProp(char * keyword,char * def);

#endif
