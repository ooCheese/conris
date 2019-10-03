
#ifndef VECTOR2D_H
    #define VECTOR2D_H
    struct vector2D{
        int x;
        int y;
    }typedef Vector2D;
        
    Vector2D * createVector2D(int x, int y);
    void rotateVector2DClockwise(Vector2D * vector2D);
    void multiplyTwoVector2D(Vector2D * vector, Vector2D * vector2);
    void subTwoVector2D(Vector2D * vector, Vector2D * sub);
    void addTwoVector2D(Vector2D * vector, Vector2D * add);

#endif

