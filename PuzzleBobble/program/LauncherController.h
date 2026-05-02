#pragma once
constexpr float ROT_MAX = 360;
constexpr float ROT_MIN = 180;
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
	
	float GetRot() const { return this->rot; }
};
