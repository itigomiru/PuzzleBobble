#include "BallController.h"
#include "Random.h"
#include "dxlib.h"
#include "LauncherController.h"
#include "GlidManager.h"
#include "Main.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include <Math.h>
void BallController::BallBounce(float leftX, float rightX)
{
    bool reflected = false;

    if (x - radius < leftX) {
        x = leftX + radius; // •Ç‚Ì“à‘¤‚É–ß‚·
        rot = 180.0f - rot;
        reflected = true;
    }
    if (x + radius > rightX) {
        x = rightX - radius; // •Ç‚Ì“à‘¤‚É–ß‚·
        rot = 180.0f - rot;
        reflected = true;
    }
    // Šp“x‚ğ0`360“x‚É³‹K‰»
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
	int color = state;
	int dxColor = GetColor(255, 255, 255);
	switch (color) {
	case RED: dxColor = GetColor(255, 0, 0); 
	DrawRectRotaGraph(x , y ,0,0,16,32,2.0f,0, ImageManager::GetInstance().GetImage(IMAGE_RED_IDLE), true);
		break;
	case GREEN: dxColor = GetColor(0, 255, 0);
	DrawRectRotaGraph(x , y ,0,0,16,32,2.0f,0, ImageManager::GetInstance().GetImage(IMAGE_GREEN_IDLE), true);
		break;

	case BLUE: dxColor = GetColor(0, 0, 255); 
	DrawRectRotaGraph(x , y ,0,0,16,32,2.0f,0, ImageManager::GetInstance().GetImage(IMAGE_BLUE_IDLE), true);
		break;
	case YELLOW: dxColor = GetColor(255, 255, 0); 
	DrawRectRotaGraph(x , y ,0,0,16,32,2.0f,0, ImageManager::GetInstance().GetImage(IMAGE_YELLOW_IDLE), true);
		break;
	case PURPLE: dxColor = GetColor(255, 0, 255); 
	DrawRectRotaGraph(x , y ,0,0,16,32,2.0f,0, ImageManager::GetInstance().GetImage(IMAGE_PURPLE_IDLE), true);
		break;
	case WHITE: dxColor = GetColor(255, 255, 255);
	DrawRectRotaGraph(x , y ,0,0,16,32,2.0f,0, ImageManager::GetInstance().GetImage(IMAGE_WHITE_IDLE), true);
		break;
	case BLACK: dxColor = GetColor(0, 0, 0);
	DrawRectRotaGraph(x , y ,0,0,16,32,2.0f,0, ImageManager::GetInstance().GetImage(IMAGE_BLACK_IDLE), true);
		break;
	}
	//DrawCircle(x, y, 16, dxColor, true);
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
		GlidManager::GetInstance().NotifyBallLanded(); // ’…’e‚ğ“Vˆäˆ—‚É’Ê’m
		this->state = EMPTY;
    }
}
