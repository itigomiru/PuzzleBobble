#pragma once
constexpr float BASE_SPEED = 10;

class BallController
{
private:
	float x = 0;
	float y = 0;
	float speed = 0;
	float rot = 0;
	const float radius = 25.0f;
	short state = 1;

private:
	void BallBounce(float leftX,float rightX);
public:
	BallController();
	void Update();
	void Render();
	int GetBallState() const { return state; }
};