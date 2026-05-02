#pragma once
constexpr float BASE_SPEED = 10;
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
	float x = 0;
	float y = 0;
	float speed = 0;
	float rot = 0;
	short col = 0;

public:
	BallController();
	~BallController();
	void Update();
	void Render();
	void Exit();
};