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
	const float radius = 25.0f;
	short col = 0;

private:
	void BallBounce(float leftX,float rightX);
public:
	BallController();
	~BallController();
	void Update();
	void Render();
	int GetBallColor() const { return col; }
};