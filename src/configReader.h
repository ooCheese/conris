#ifndef CONFIGREADER_H
    #define CONFIGREADER_H
    
	#define MAX_KEY_WORD 20
	#define MAX_KEY_VALUE 20

	int readConfig();
	char getCharProp(char * keyword,char def);
	int getIntProp(char * keyword, int def);
	void deleteAllConfigProps();

#endif
