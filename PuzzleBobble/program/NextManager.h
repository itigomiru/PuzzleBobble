#pragma once
#include "NextBallController.h"

class NextManager
{
private:
	std::deque<NextBall> queue; // NextBallオブジェクトを並べる
	void onFire();
};