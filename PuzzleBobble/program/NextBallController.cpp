#include "NextBallController.h"
#include "dxlib.h"
#include "GlidManager.h"
#include "ImageManager.h"

void NextBall::update() {
    // 線形補間（Lerp）などで target に近づける
    x += (targetX - x) * 0.1f;
    y += (targetY - y) * 0.1f;

    // タイマーを進める
    blinkTimer++;
    if (blinkTimer >= 300) {
        blinkTimer = 0;
    }
}
void NextBall::Render()
{
	int color = this->state;
	int dxColor = GetColor(255, 255, 255);
	
	int srcX = 0;
	// 瞬きのアニメーション制御
	if (blinkTimer >= 290) {
		int frame = blinkTimer - 290;
		if (frame < 3) srcX = 16 * 1; // コマ1
		else if (frame < 7) srcX = 16 * 2; // コマ2 (目を閉じる)
		else srcX = 16 * 1; // コマ1に戻る
	}

	switch (color) {
	case RED:
		dxColor = GetColor(255, 0, 0);
		DrawRectRotaGraph(x, y, srcX, 0, 16, 32, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_RED_IDLE), true);
		break;
	case GREEN: 
		dxColor = GetColor(0, 255, 0);
		DrawRectRotaGraph(x, y, srcX, 0, 16, 32, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_GREEN_IDLE), true);
		break;
	case BLUE: 
		dxColor = GetColor(0, 0, 255);
		DrawRectRotaGraph(x, y, srcX, 0, 16, 32, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_BLUE_IDLE), true);
		break;
	case YELLOW: 
		dxColor = GetColor(255, 255, 0);
		DrawRectRotaGraph(x, y, srcX, 0, 16, 32, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_YELLOW_IDLE), true);
		break;
	case PURPLE:
		dxColor = GetColor(255, 0, 255);
		DrawRectRotaGraph(x, y, srcX, 0, 16, 32, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_PURPLE_IDLE), true);
		break;
	case WHITE: 
		dxColor = GetColor(255, 255, 255);
		DrawRectRotaGraph(x, y, srcX, 0, 16, 32, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_WHITE_IDLE), true);
		break;
	case BLACK: 
		dxColor = GetColor(0, 0, 0);
		DrawRectRotaGraph(x, y, srcX, 0, 16, 32, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_BLACK_IDLE), true);
		break;
	}
	//DrawCircle(x, y, 16, dxColor, true);
}
