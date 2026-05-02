#include "BallController.h"
#include "Random.h"
#include "dxlib.h"
#include "LauncherController.h"
#include <Math.h>

BallController::BallController()
{
	
	x = 0;
	y = 0;
	speed = BASE_SPEED;
	col = GetRandomI(COL_MAX - 1);
	rot = LauncherController::GetInstance().GetRot();
}

BallController::~BallController()
{

}

void BallController::Update()
{
	x += cosf(rot) * speed;
	y += sinf(rot) * speed;
}