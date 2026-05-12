#include "Main.h"
#include "SceneManager.h"
#include "Stage.h"
#include "Float2.h"
#include "Hit.h"
#include "LauncherController.h"
#include "GlidManager.h"
#include "BallController.h"
#include "NextManager.h"

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
	NextManager::GetInstance().Init();
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void StageUpdate()
{
	LauncherController::GetInstance().Update();
	NextManager::GetInstance().Update();
	if (PushHitKey(KEY_INPUT_SPACE))
	{
		if (ball == nullptr) {
			int nextColor = NextManager::GetInstance().GetNextBallColor();
			ball = new BallController(nextColor);
			NextManager::GetInstance().onFire(); // 発射をネクストマネージャーに通知
		}
	}
	if (ball != nullptr) {
		ball->Update();
		if (ball->GetBallState() == EMPTY) {
			delete ball;
			ball = nullptr;
		}
	}

	// クリア判定
	if (GlidManager::GetInstance().IsClear()) {
		scene_next = SCENE_RESULT;
	}

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
	NextManager::GetInstance().Render();
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
