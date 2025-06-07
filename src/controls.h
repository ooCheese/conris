#ifndef CONTROLS_H
    #define CONTROLS_H

    #define BLOCKED 0
    #define FREE 1
    #define GROUNDED -1
    #define GAME_OVER -2
    #define WRONG_INPUT -3

    #define NUM_KEYS 7

    typedef enum {
        DOWN_KEY,
        LEFT_KEY,
        RIGHT_KEY,
        ROTATE_KEY,
        QUIT_KEY,
        HOLD_KEY,
        DOWN_TO_GROUND_KEY
    } t_ControlKeyFunction;

    void setGhostMode(int gm);
    int isGameOver(void);
    int * getNextPtr(void);

    void setKeyMapping(t_ControlKeyFunction typ, char key);
    char getKeyMapping(t_ControlKeyFunction typ);

    void handleInput(int input,int  * field);
    void gameover();
    void spawnPlayer(int *field);

    void down (int *field);

#endif