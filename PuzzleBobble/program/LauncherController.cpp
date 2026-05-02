#include "LauncherController.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "Math.h"
#include "Main.h"

void LauncherController::Update()
{
	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		rot -= 3;
	}
	if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		rot += 3;
	}
	if (rot > ROT_MAX)
	{
		rot = ROT_MAX;
	}
	if (rot < ROT_MIN)
	{
		rot = ROT_MIN;
	}
}
void LauncherController::Render()
{
	DrawLine(SCREEN_W * 0.5, 500, (SCREEN_W * 0.5) + cosf(TO_DEGREE(rot)) , 500 - sinf(TO_DEGREE(rot)) , 0x00FFFF);
	DrawFormatString(100, 100, GetColor(255, 255, 255), "angle: %f", rot);
}