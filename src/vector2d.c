#include "vector2d.h"
#include <stdio.h>
#include <stdlib.h>

extern Vector2D * createVector2D(int x, int y){
    Vector2D * vector;
    
    vector = malloc(sizeof(Vector2D));
    vector->x = x;
    vector->y = y;

    return vector;
}

extern void rotateVector2DClockwise(Vector2D * vector2D){
    int x,y;
    x = vector2D->y;
    y = vector2D->x;

    vector2D->x = x*-1;
    vector2D->y = y;

}

extern void addTwoVector2D(Vector2D * vector, Vector2D * add){

    vector->x += add->x;
    vector->y += add->y;
    free(add);
}

extern void subTwoVector2D(Vector2D * vector, Vector2D * sub){

    vector->x -= sub->x;
    vector->y -= sub->y;
    free(sub);
}

extern void multiplyTwoVector2D(Vector2D * vector, Vector2D * vector2){
    vector->x *= vector2->x;
    vector->y *= vector2->y;
}
