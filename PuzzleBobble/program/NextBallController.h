#pragma once
#include <queue>
class NextBall {
public:
    int color;
    float x, y;
    float targetX, targetY;
    bool isMoving;

    void update();
    void Render();


};

