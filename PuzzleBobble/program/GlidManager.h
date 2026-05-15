#pragma once
#include "BallController.h"
#include "SceneManager.h"
#include "Float2.h"
enum states
{
	INVALID = -1,
	EMPTY	= 0,
	RED		= 1,
	GREEN	= 2,
	BLUE	= 3,
	YELLOW	= 4,
	PURPLE	= 5,
	WHITE	= 6,
	BLACK	= 7,
	ORANGE = 8,
};
struct GlidCell
{
	int state = 0;
	Float2 pos = { 0, 0 };
	int blinkTimer = 0;
	int luminusTimer = 0;
	bool wasLuminus = true;
	bool isGameOverGray = false;
};

const int STAGE_MAX = 30;
class GlidManager
{
public:
	float top = VS_Y;
	int dropTimer = 0; 
	bool isWaitingToDrop = false; // 振動後、弾が着弾して下がるのを待つフラグ
	int deadLineRowOffset = 0; // 天井が下がった回数を保持してデッドラインを引き上げる
private:
	const int LUMINUS_INTERVAL = 5;
	static constexpr int ROWS = 12;
	static constexpr int COLS = 8;
	static constexpr int GAMEOVER_GRAY_INTERVAL = 3;
	GlidCell glid[ROWS][COLS];
	bool isGameOverAnimating = false;
	int gameOverGrayTimer = 0;
	int gameOverScanRow = ROWS - 1;
	int gameOverScanCol = COLS - 1;

	int StageData[STAGE_MAX][ROWS][COLS]
		= {
	#include "StageData.inc"
	};
	

private:
	GlidManager();
	GlidManager(const GlidManager&) = delete;
	GlidManager& operator=(const GlidManager&) = delete;

public:
	static GlidManager& GetInstance();

	void Init();
	void Update(bool isBallFlying = false);
	void NotifyBallLanded(); // 弾が着弾したことを通知する用
	void Render();
	void AddGlid(short state, int row, int col);
	void AddScore(int point);
	void SetGlid(int StageNum);

	void GetClosestGlid(Float2 pos, int& outRow, int& outCol);

	bool CheckCircleCollision(float ballX, float ballY, float ballR);

	void CheckMatchAndRemoveGlid(int NewR,int NewC,int state);
	void CheckConnectAndRemoveGlid();

	int DecideNextBallState();
	bool IsClear(); // クリア判定用メソッド
	bool IsGameOver(); // ゲームオーバー判定用メソッド
	bool IsGameOverAnimationFinished() const;
	void GameOver();
};
