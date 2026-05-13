#pragma once
#include "NextBallController.h"
#include "LauncherController.h"

class NextManager
{
public:
	static NextManager& GetInstance() {
		static NextManager instance;
		return instance;
	}
	void Init(); // 初期化時にボールを詰める用
	int GetNextBallColor(); // 次に発射するボールの色を取得
	void onFire();
	void Update(); // 更新処理
private:
	std::deque<NextBall> queue; // NextBallオブジェクトを並べる

	enum Slots
	{
		// LauncherController の定数をそのまま参照して一緒にする
		SLOT0_X = LauncherController::SHOOTPOS_X, SLOT0_Y = LauncherController::SHOOTPOS_Y,
		// 次のボールは発射台の左下（パズルボブル基準）に置く
		SLOT1_X = LauncherController::SHOOTPOS_X - 70, SLOT1_Y = LauncherController::SHOOTPOS_Y + 34,
	};
public:
	void Render();
};