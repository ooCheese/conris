#ifndef MOVMENT_H
    #include "field.h"
    #include "tetro.h"

    #define MOVMENT_H
    #define BLOCKED 0
    #define FREE 1
    #define GROUNDED -1
    #define GAME_OVER -2
    #define WRONG_INPUT -3

    int checkMovment(Tetro * player, Vector2D * direction, int * field);
#endif