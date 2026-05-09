#pragma once
#include "BallController.h"
#include "SceneManager.h"
enum states
{
	EMPTY,
	RED,
	GREEN,
	BLUE,
	YELLOW
};
struct GlidCell
{
	int state = 0;
};


class GlidManager
{
private:
	static constexpr int ROWS = 12;
	static constexpr int COLS = 8;
	GlidCell glid[ROWS][COLS];

	GlidCell StageData[3][ROWS][COLS]
		= {
	#include "StageData.inc"
	};

	float offset_y = VS_Y;

	GlidManager();
	~GlidManager();
	GlidManager(const GlidManager&) = delete;
	GlidManager& operator=(const GlidManager&) = delete;


	void GetCellCenter(int row, int col, float& cx, float& cy);
public:
	static GlidManager& GetInstance();

	void Render();
	void AddGlid(BallController* ball, int row, int col);
	void SetGlid(int StageNum);

	bool CheckCircleCollision(float ballX, float ballY, float ballR);
};