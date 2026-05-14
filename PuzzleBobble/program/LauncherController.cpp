#include "LauncherController.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "Main.h"
#include "ImageManager.h"

void LauncherController::Update()
{
    if (CheckHitKey(KEY_INPUT_LEFT))
    {
        rot -= 3;
        animCounter[LAUNCHER_BASE] = (animCounter[LAUNCHER_BASE] + 1) % (12 * ANIM_INTERVAL[LAUNCHER_BASE]);
		animCounter[RIGHT_BABBLEN]--;
		if (animCounter[RIGHT_BABBLEN] < ANIM_INTERVAL[RIGHT_BABBLEN]) animCounter[RIGHT_BABBLEN] = (9 * ANIM_INTERVAL[RIGHT_BABBLEN]) - 1;
    }
    else if (CheckHitKey(KEY_INPUT_RIGHT))
    {
        rot += 3;
		animCounter[LAUNCHER_BASE]--;
		if (animCounter[LAUNCHER_BASE] < 0) animCounter[LAUNCHER_BASE] = (12 * ANIM_INTERVAL[LAUNCHER_BASE]) - 1;
        animCounter[RIGHT_BABBLEN] = (animCounter[RIGHT_BABBLEN] + 1) % (8 * ANIM_INTERVAL[RIGHT_BABBLEN]);
		if (animCounter[RIGHT_BABBLEN] < ANIM_INTERVAL[RIGHT_BABBLEN]) animCounter[RIGHT_BABBLEN] += ANIM_INTERVAL[RIGHT_BABBLEN];
    }
    else {
    animCounter[LAUNCHER_BASE] = 0;
	animCounter[RIGHT_BABBLEN] = 0;
    }
    if (rot > ROT_MAX)
    {
        rot = ROT_MAX;
    }
    if (rot < ROT_MIN)
    {
        rot = ROT_MIN;
    }
    if(isFiring)
    {
        animCounter[LEFT_BABBLEN]++;
        if (animCounter[LEFT_BABBLEN] >= 9 * ANIM_INTERVAL[LEFT_BABBLEN]) {
            animCounter[LEFT_BABBLEN]= 0;
            isFiring = false;
        }
        if(isPiped == false)animCounter[LAUNCHER_PIPE]++;
        if (animCounter[LAUNCHER_PIPE] >= 3 * ANIM_INTERVAL[LAUNCHER_PIPE]  - 4) {
            animCounter[LAUNCHER_PIPE]= 0;
            isPiped = true;
        }
	}
    else {
        animCounter[LEFT_BABBLEN] = 0;
        animCounter[LAUNCHER_PIPE] = 0;
	}
}

void LauncherController::Render()
{
	DrawRotaGraph(SCREEN_W * 0.5, 362, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_BAR), true);
	DrawRectRotaGraph(SCREEN_W * 0.5,392, animCounter[LAUNCHER_BASE]/ANIM_INTERVAL[LAUNCHER_BASE] *64, 0, 64, 64, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_LAUNCHER_BASE), true);
    DrawRotaGraph(SHOOTPOS_X , SHOOTPOS_Y, 2.0f, TO_RADIAN(rot), ImageManager::GetInstance().GetImage(IMAGE_ALLOW), true);
    DrawRectRotaGraph(SCREEN_W * 0.5 - 32, 400, animCounter[LEFT_BABBLEN] / ANIM_INTERVAL[LEFT_BABBLEN] * 32, 0, 32, 32, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_LEFT_BABBLEN), true);
	DrawRectRotaGraph(SCREEN_W * 0.5, 398, animCounter[LAUNCHER_PIPE] / ANIM_INTERVAL[LAUNCHER_PIPE] * 32, 0, 16, 32, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_LAUNCHER_PIPE), true);
	DrawRectRotaGraph(SCREEN_W * 0.5 + 60, 400, animCounter[RIGHT_BABBLEN] / ANIM_INTERVAL[RIGHT_BABBLEN] * 32, 0, 32, 32, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_RIGHT_BABBLEN), true);
}

void LauncherController::Onfire()
{
    animCounter[LEFT_BABBLEN] = 3 * ANIM_INTERVAL[LEFT_BABBLEN];
	isFiring = true;
    isPiped = false;
}