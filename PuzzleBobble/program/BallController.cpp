#include "BallController.h"
#include "Random.h"
#include "dxlib.h"
#include "LauncherController.h"
#include "GlidManager.h"
#include "Main.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include "SoundManager.h"
#include <Math.h>

void BallController::BallBounce(float leftX, float rightX)
{
    bool reflected = false;

    if (x - radius < leftX) {
        x = leftX + radius; // ï«ÇÃì‡ë§Ç…ñﬂÇ∑
        rot = 180.0f - rot;
        reflected = true;
	PlaySoundMem(SoundManager::GetInstance().GetSE(SE_TAP), DX_PLAYTYPE_BACK);
    }
    if (x + radius > rightX) {
        x = rightX - radius; // ï«ÇÃì‡ë§Ç…ñﬂÇ∑
        rot = 180.0f - rot;
        reflected = true;
	PlaySoundMem(SoundManager::GetInstance().GetSE(SE_TAP), DX_PLAYTYPE_BACK);
    }
    // äpìxÇ0Å`360ìxÇ…ê≥ãKâª
	if (reflected) {
		if (rot < 0) rot += 360.0f;
		if (rot >= 360.0f) rot -= 360.0f;
	}
}
BallController::BallController(int initialColor)
{

	x = LauncherController::GetInstance().SHOOTPOS_X;
	y = LauncherController::GetInstance().SHOOTPOS_Y;
	speed = BASE_SPEED;
	rot = LauncherController::GetInstance().GetRot();
	state = initialColor;
}


void BallController::Render()
{
	DrawRectRotaGraph(x, y, 0, 0, 16, 32, 2.0f, 0, ImageManager::GetInstance().GetImage(ImageManager::GetInstance().GetBubbleImage(state)), true);

} 
void BallController::Update()
{
	x += cosf(TO_RADIAN(rot)) * speed;
	y += sinf(TO_RADIAN(rot)) * speed;
	BallBounce(VS_X, VS_X + VS_W);
    if (GlidManager::GetInstance().CheckCircleCollision(x, y, radius) == true || GlidManager::GetInstance().top > y - radius)
    {
		PlaySoundMem(SoundManager::GetInstance().GetSE(SE_TAP), DX_PLAYTYPE_BACK);
		int row, col;
		GlidManager::GetInstance().GetClosestGlid({ x, y }, row, col);
	    GlidManager::GetInstance().AddGlid(this->state, row, col);
		GlidManager::GetInstance().CheckMatchAndRemoveGlid(row,col,state);
		GlidManager::GetInstance().CheckConnectAndRemoveGlid();
		GlidManager::GetInstance().NotifyBallLanded(); // íÖíeÇìVà‰èàóùÇ…í ím
		this->state = EMPTY;
    }
}
