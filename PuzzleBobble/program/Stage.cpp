#include "Main.h"
#include "SceneManager.h"
#include "Stage.h"
#include "Float2.h"
#include "Hit.h"
#include "LauncherController.h"
#include "GlidManager.h"
#include "BallController.h"
#include "NextManager.h"
#include"ImageManager.h"
#include "EffectManager.h"

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
	stage_state = STAGE_READY;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void StageUpdate()
{
	switch (stage_state)
	{
		case STAGE_READY:
			//ready go!の演出を後で追加
			stage_state = STAGE_PLAYING;
			break;
		case STAGE_PLAYING:
			break;

	}
	bool isBallFlying = (ball != nullptr);

	GlidManager::GetInstance().Update(isBallFlying);
	LauncherController::GetInstance().Update();
	EffectManager::GetInstance().Update();
	NextManager::GetInstance().Update();
	if (PushHitKey(KEY_INPUT_SPACE))
	{
		if (ball == nullptr) {
			int nextColor = NextManager::GetInstance().GetNextBallColor();
			ball = new BallController(nextColor);
			NextManager::GetInstance().onFire(); // 発射をネクストマネージャーに通知
			LauncherController::GetInstance().Onfire(); // 発射アニメーション開始
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
	// ゲームオーバー判定
	else if (GlidManager::GetInstance().IsGameOver()) {
		scene_next = SCENE_TITLE; // ゲームオーバー時はタイトル画面に戻す
	}

}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void StageRender()
{

	DrawRotaGraph(SCREEN_W * 0.5,SCREEN_H * 0.5, 2.0f,0,ImageManager::GetInstance().GetImage(IMAGE_STAGE1), true);
	DrawRectRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5 - 30, GlidManager::GetInstance().deadLineRowOffset * 128, 0, 128, 162, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_SHUTTER_STAGE1), true);
	DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5 + 8, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_WALL_STAGE1), true);
	LauncherController::GetInstance().Render();
	GlidManager::GetInstance().Render();
	EffectManager::GetInstance().Render();
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
