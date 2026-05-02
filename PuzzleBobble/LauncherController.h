#pragma once
constexpr int ROT_MAX = 60;
constexpr int ROT_MIN = -60;
class LauncherController
{
private:
	int rot = 270;
	int y = 500;
public:
	void Update();
	void Render();
};
