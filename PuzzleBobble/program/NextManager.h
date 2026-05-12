#pragma once
#include "NextBallController.h"

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
		SLOT0_X = 220, SLOT0_Y = 480, // 発射台の左下あたりに最初のスロット
		SLOT1_X = 140, SLOT1_Y = 480, // そのさらに左に2個目のスロット
	};
public:
	void Render();
};