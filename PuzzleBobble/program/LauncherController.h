#pragma once
constexpr float ROT_MAX = 60;
constexpr float ROT_MIN = -60;
class LauncherController
{
public:
	static LauncherController& GetInstance()
		{
		static LauncherController instance;
		return instance;
	}

private:
	float rot = 270;

public:
	void Update();
	void Render();
};
