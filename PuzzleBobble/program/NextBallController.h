#pragma once
#include <queue>
class NextBall {
public:
    int state;
    float x, y;
    float targetX, targetY;
    bool isMoving;
    int blinkTimer; // まばたき用タイマーを追加

    void update();
    void Render();


};

