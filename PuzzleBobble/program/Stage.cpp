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

int stage_state;
int stageNum = 4;
int counter = 0;
bool isGameOverStarted = false;
int gameOverDelayTimer = 0;
static constexpr int GAMEOVER_RETRY_DELAY = 60;
//=================================================================================
//	ステージの処理
//=================================================================================

BallController* ball = nullptr;

//---------------------------------------------------------------------------------
//	初期化
//---------------------------------------------------------------------------------
void StageInit()
{
	if (ball != nullptr) {
		delete ball;
		ball = nullptr;
	}
	GlidManager::GetInstance().Init();
	GlidManager::GetInstance().SetGlid(stageNum);
	NextManager::GetInstance().Init();
	EffectManager::GetInstance().ClearAll();
	isGameOverStarted = false;
	gameOverDelayTimer = 0;
	stage_state = STAGE_READY;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void StageUpdate()
{
		bool isBallFlying = (ball != nullptr);
	switch (stage_state)
	{
	case STAGE_READY:
		//ready go!の演出を後で追加
		counter++;
		if (counter > 300)
		{
			counter = 0;
			stage_state = STAGE_PLAYING;
		}
		break;
	case STAGE_PLAYING:

		GlidManager::GetInstance().Update(isBallFlying);
		LauncherController::GetInstance().Update();
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
			//scene_next = SCENE_RESULT;
			stage_state = STAGE_CLEAR;
		}
		// ゲームオーバー判定
		else if (GlidManager::GetInstance().IsGameOver()) {
			//scene_next = SCENE_TITLE; // ゲームオーバー時はタイトル画面に戻す
			stage_state = STAGE_GAMEOVER;
		}

		break;
	case STAGE_CLEAR:
		//クリア演出を後で追加
		LauncherController::GetInstance().Update();
		NextManager::GetInstance().Update();

		counter++;
		if (counter > 300)
		{
			counter = 0;
			stageNum++;
			StageInit();
		}
		break;
	case STAGE_GAMEOVER:
		if (!isGameOverStarted) {
			GlidManager::GetInstance().GameOver();
			isGameOverStarted = true;
			gameOverDelayTimer = 0;
		}
		GlidManager::GetInstance().Update(isBallFlying);
		LauncherController::GetInstance().Update();
		NextManager::GetInstance().Update();
		if (GlidManager::GetInstance().IsGameOverAnimationFinished()) {
			gameOverDelayTimer++;
			if (gameOverDelayTimer >= GAMEOVER_RETRY_DELAY) {
				StageInit();
			}
		}
		break;

	}
	EffectManager::GetInstance().Update();

}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void StageRender()
{

	DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_STAGE1), true);
	DrawRectRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5 - 30, GlidManager::GetInstance().deadLineRowOffset * 128, 0, 128, 162, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_SHUTTER_STAGE1), true);
	DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5 + 8, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_WALL_STAGE1), true);
	LauncherController::GetInstance().Render();
	GlidManager::GetInstance().Render();
	EffectManager::GetInstance().Render();
	NextManager::GetInstance().Render();
	if (ball != nullptr) {
		ball->Render();
	}
		int srcX_r = 16 * ((stageNum + 1) % 10);
		int srcX_l = 16 * ((stageNum + 1) / 10);
	switch (stage_state)
	{
	case STAGE_READY:
		DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.35, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_ROUNDBOARD), true);
		if (srcX_l != 0)DrawRectRotaGraph(SCREEN_W * 0.5 - 16, SCREEN_H * 0.35 + 16, srcX_l, 0, 16, 16, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_NUMBER), true);
		DrawRectRotaGraph(SCREEN_W * 0.5 + 16, SCREEN_H * 0.35 + 16, srcX_r, 0, 16, 16, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_NUMBER), true);
		break;
	case STAGE_CLEAR:
		DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.35, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_ROUND_CLEAR), true);
		break;
	}


}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void StageExit()
{
}
