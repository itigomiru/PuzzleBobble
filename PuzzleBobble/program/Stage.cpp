#include "Main.h"
#include "SceneManager.h"
#include "Stage.h"
#include "Float2.h"
#include "Hit.h"
#include "LauncherController.h"
#include "GlidManager.h"
#include "BallController.h"

//=================================================================================
//	ステージの処理
//=================================================================================

BallController* ball = nullptr;

//---------------------------------------------------------------------------------
//	初期化
//---------------------------------------------------------------------------------
void StageInit()
{
	GlidManager::GetInstance().SetGlid(0);
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void StageUpdate()
{
	LauncherController::GetInstance().Update();
	if (PushHitKey(KEY_INPUT_SPACE))
	{
		if (ball == nullptr) {
			ball = new BallController();
		}
	}
	if (ball != nullptr) {
		ball->Update();
		if (ball->GetBallState() == EMPTY) {
			delete ball;
			ball = nullptr;
		}
	}
	if(1+1 == 1)scene_next = SCENE_RESULT;
	
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void StageRender()
{
	DrawBox(0, 0, SCREEN_W, SCREEN_H, 0x002222, true);
	DrawBox(VS_X, VS_Y, VS_X + VS_W, VS_Y + VS_H, 0x00AAAA, true);
	LauncherController::GetInstance().Render();
	GlidManager::GetInstance().Render();
	if (ball != nullptr) {
		ball->Render();
	}

}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void StageExit()
{
}
