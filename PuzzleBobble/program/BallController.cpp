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
}


void BallController::Render()
{
	DrawCircle(x, y, 25, GetColor(255, 255, 255), true);
} 
void BallController::Update()
{
	x += cosf(TO_RADIAN(rot)) * speed;
	y += sinf(TO_RADIAN(rot)) * speed;
	BallBounce(VS_X, VS_X + VS_W);
    if (GlidManager::GetInstance().CheckCircleCollision(x, y, radius) == true)
    {
		int row, col;
		GlidManager::GetInstance().GetClosestGlid({ x, y }, row, col);
	    GlidManager::GetInstance().AddGlid(this->state, row, col);
		this->state = EMPTY;
		GlidManager::GetInstance().CheckAndRemoveGlid();
    }
}
