#include "BallController.h"
#include "Random.h"
#include "dxlib.h"
#include "LauncherController.h"
#include "GlidManager.h"
#include "Main.h"
#include "SceneManager.h"
#include <Math.h>
void BallController::BallBounce(float leftX, float rightX)
{
    bool reflected = false;

    if (x - radius < leftX) {
        x = leftX + radius; // ï«ÇÃì‡ë§Ç…ñﬂÇ∑
        rot = 180.0f - rot;
        reflected = true;
    }
    if (x + radius > rightX) {
        x = rightX - radius; // ï«ÇÃì‡ë§Ç…ñﬂÇ∑
        rot = 180.0f - rot;
        reflected = true;
    }
    // äpìxÇ0Å`360ìxÇ…ê≥ãKâª
    if (reflected) {
        if (rot < 0) rot += 360.0f;
        if (rot >= 360.0f) rot -= 360.0f;
    }
}
BallController::BallController()
{
	
	x = SCREEN_W * 0.5;
	y = 450;
	speed = BASE_SPEED;
	rot = LauncherController::GetInstance().GetRot();
	state = GlidManager::GetInstance().DecideNextBallState();
}


void BallController::Render()
{
	int color = state;
	int dxColor = GetColor(255, 255, 255);
	switch (color) {
	case RED: dxColor = GetColor(255, 0, 0); break;
	case GREEN: dxColor = GetColor(0, 255, 0); break;
	case BLUE: dxColor = GetColor(0, 0, 255); break;
	case YELLOW: dxColor = GetColor(255, 255, 0); break;
	case PURPLE: dxColor = GetColor(255, 0, 255); break;
	case WHITE: dxColor = GetColor(255, 255, 255); break;
	case BLACK: dxColor = GetColor(0, 0, 0); break;
	}
	DrawCircle(x, y, 25, dxColor, true);
} 
void BallController::Update()
{
	x += cosf(TO_RADIAN(rot)) * speed;
	y += sinf(TO_RADIAN(rot)) * speed;
	BallBounce(VS_X, VS_X + VS_W);
    if (GlidManager::GetInstance().CheckCircleCollision(x, y, radius) == true || GlidManager::GetInstance().top > y - radius)
    {
		int row, col;
		GlidManager::GetInstance().GetClosestGlid({ x, y }, row, col);
	    GlidManager::GetInstance().AddGlid(this->state, row, col);
		GlidManager::GetInstance().CheckMatchAndRemoveGlid(row,col,state);
		GlidManager::GetInstance().CheckConnectAndRemoveGlid();
		this->state = EMPTY;
    }
}
