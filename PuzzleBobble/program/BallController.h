#pragma once
constexpr float BASE_SPEED = 10;

class BallController
{
private:
	float x = 0;
	float y = 0;
	float speed = 0;
	float rot = 0;
	const float radius = 16.0f;
	int state = 1;

private:
	void BallBounce(float leftX,float rightX);
public:
	BallController(int initialColor);
	void Update();
	void Render();
	int GetBallState() const { return state; }
};