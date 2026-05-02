#pragma once
enum COL
{
	RED,
	GREEN,
	BLUE,
	YELLOW,
	COL_MAX
};
class BallController
{
private:
	int x = 0;
	int y = 0;
	int speed = 0;
	short col = 0;

public:
	BallController();
	~BallController();
	void Init();
	void Update();
	void Render();
	void Exit();
};