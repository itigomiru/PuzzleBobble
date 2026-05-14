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
	int srcX = 0;

	if (blinkTimer >= 290) {
		int frame = blinkTimer - 290;

		if (frame < 3) srcX = 16;
		else if (frame < 7) srcX = 32;
		else srcX = 16;
	}

	DrawRectRotaGraph(x, y, srcX, 0, 16, 32, 2.0f, 0, ImageManager::GetInstance().GetImage(ImageManager::GetInstance().GetBubbleImage(state)), true);
}