#pragma once
#include "BallController.h"
#include "SceneManager.h" // VS_Xなどのマクロを使うために追加

constexpr float ROT_MAX = 350;
constexpr float ROT_MIN = 190;
class LauncherController
{
public:
	static LauncherController& GetInstance()
	{
		static LauncherController instance;
		return instance;
	}

private:
	enum ANIMCOUNTER
	{
		LEFT_BABBLEN = 0,
		RIGHT_BABBLEN = 1,
		LAUNCHER_BASE = 2,
		LAUNCHER_PIPE = 3,
		ANIMCOUNTER_MAX,
	};
	float rot = 270;
	const int ANIM_INTERVAL[ANIMCOUNTER_MAX] = {
		5,
		2,
		2,
		5,
	};
	int animCounter[ANIMCOUNTER_MAX] = { 0 };
	bool isFiring = false;
	bool isPiped = false;
public:
	static constexpr int SHOOTPOS_X = VS_X + (VS_W / 2);
	static constexpr int SHOOTPOS_Y = VS_Y + VS_H - 40;

	void Update();
	void Render();

	float GetRot() const { return this->rot; }
	void Onfire();
};