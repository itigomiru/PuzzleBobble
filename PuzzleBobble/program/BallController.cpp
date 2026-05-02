#include "BallController.h"
#include "Random.h"
#include "dxlib.h"

BallController::BallController()
{
	x = 0;
	y = 0;
	speed = 0;
	col = GetRandomI(COL_MAX - 1);
}

BallController::~BallController()
{

}

void BallController::Init()
{
	x = 0;
	y = 0;
	speed = 0;
	col = GetRandomI(COL_MAX - 1);
}