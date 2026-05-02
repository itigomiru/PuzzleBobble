#include "LauncherController.h"
#include "SceneManager.h"
#include "DxLib.h"

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
	DrawLine(, y, 50 + (int)(cosf(rot * DX_PI_F / 180) * 100), y + (int)(sinf(rot * DX_PI_F / 180) * 100), GetColor(255, 255, 255));
}