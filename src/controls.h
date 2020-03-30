#ifndef CONTROLS_H
    #define CONTROLS_H

    #define BLOCKED 0
    #define FREE 1
    #define GROUNDED -1
    #define GAME_OVER -2
    #define WRONG_INPUT -3

    char 
        DOWN_KEY,
        LEFT_KEY,
        RIGHT_KEY,
        ROTATE_KEY,
        QUIT_KEY,
        HOLD_KEY,
        DOWN_TO_GROUND_KEY;

    int isHolded;
    int next;
    int isGameOver;

    void handleInput(int input,int  * field);
    void gameover();
    void spawnPlayer(int *field);

    void down (int *field);

#endif