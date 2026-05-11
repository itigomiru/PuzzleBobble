#pragma once
#include <queue>
class NextBall {
    int color;
    float x, y;
    float targetX, targetY;
    bool isMoving;

    void update();
};

class NextController
{
	private:
		std::deque<Ball> queue; // Ballオブジェクトを並べる

};