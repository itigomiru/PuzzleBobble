#pragma once
#include <queue>
class NextBall {
    int color;
    float x, y;
    float targetX, targetY;
    bool isMoving;

    void update();
};

