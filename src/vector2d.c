#include "vector2d.h"
#include <stdio.h>
#include <stdlib.h>

Vector2D * copyRotatedVectorToOther(Vector2D * source,Vector2D * target);

 Vector2D * createVector2D(int x, int y){
    Vector2D * vector;
    
    vector = malloc(sizeof(Vector2D));
    vector->x = x;
    vector->y = y;

    return vector;
}

 void rotateOnVector2DClockwise(Vector2D * vector2D){
    copyRotatedVectorToOther(vector2D,vector2D);
}

 Vector2D * rotateVector2DClockwise(Vector2D * vector2D){
    return copyRotatedVectorToOther(vector2D,createVector2D(0,0));
}

Vector2D * copyRotatedVectorToOther(Vector2D * source,Vector2D * target){
    int x,y;

    x = source->y;
    y = source->x;
    
    target->x = x*-1;
    target->y = y;

    return target;
}

 void addTwoVector2D(Vector2D * vector, Vector2D * add){

    addTwoVector2D_NotFreeAdded(vector,add);
    free(add);
}
 void addTwoVector2D_NotFreeAdded(Vector2D * vector, Vector2D * add){
    vector->x += add->x;
    vector->y += add->y;
}

 void subTwoVector2D(Vector2D * vector, Vector2D * sub){

    vector->x -= sub->x;
    vector->y -= sub->y;
    free(sub);
}

 void multiplyTwoVector2D(Vector2D * vector, Vector2D * vector2){
    vector->x *= vector2->x;
    vector->y *= vector2->y;
}
