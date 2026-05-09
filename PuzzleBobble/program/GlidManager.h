#pragma once
#include "BallController.h"
#include "SceneManager.h"
#include "Float2.h"
enum states
{
	INVALID = -1,
	EMPTY = 0,
	RED,
	GREEN,
	BLUE,
	YELLOW
};
struct GlidCell
{
	int state = 0;
	Float2 pos = { 0, 0 };
};


class GlidManager
{
private:
	static constexpr int ROWS = 12;
	static constexpr int COLS = 8;
	GlidCell glid[ROWS][COLS];

	int StageData[3][ROWS][COLS]
		= {
	#include "StageData.inc"
	};

	float top = VS_Y;

	GlidManager();
	GlidManager(const GlidManager&) = delete;
	GlidManager& operator=(const GlidManager&) = delete;

public:
	static GlidManager& GetInstance();

	void Render();
	void AddGlid(short state, int row, int col);
	void SetGlid(int StageNum);

	void GetClosestGlid(Float2 pos, int& outRow, int& outCol);

	bool CheckCircleCollision(float ballX, float ballY, float ballR);
	
	void CheckAndRemoveGlid();
};
