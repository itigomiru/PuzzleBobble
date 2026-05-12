#pragma once
#include "NextBallController.h"

class NextManager
{
private:
	std::deque<NextBall> queue; // NextBallオブジェクトを並べる
	void onFire();
	
	enum Slots
	{
		SLOT0_X = 700, SLOT0_Y = 50,
		SLOT1_X = 750, SLOT1_Y = 50,
	};
};