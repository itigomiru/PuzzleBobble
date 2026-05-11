#include "NextBallController.h"


void NextBall::update() {
    // 線形補間（Lerp）などで target に近づける
    x += (targetX - x) * 0.1f;
    y += (targetY - y) * 0.1f;
}




