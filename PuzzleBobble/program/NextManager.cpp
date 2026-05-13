#include <deque>
#include "NextManager.h"
#include "GlidManager.h"
#include "NextBallController.h"
#include "ImageManager.h"
#include "DxLib.h"
#include "Random.h"

void NextManager::Init() {
    queue.clear();
    // 初期状態で2つボールを入れておく、まばたきタイマー(blinkTimer)も一緒に付与する
    NextBall ball0 = { GlidManager::GetInstance().DecideNextBallState(), (float)SLOT0_X, (float)SLOT0_Y, (float)SLOT0_X, (float)SLOT0_Y, false, GetRandomI(0, 300) };
    NextBall ball1 = { GlidManager::GetInstance().DecideNextBallState(), (float)SLOT1_X, (float)SLOT1_Y, (float)SLOT1_X, (float)SLOT1_Y, false, GetRandomI(0, 300) };
    queue.push_back(ball0);
    queue.push_back(ball1);
}

int NextManager::GetNextBallColor() {
    if (!queue.empty()) {
        return queue.front().state;
    }
	// 一応、キューが空の場合のエラー対策
    return GlidManager::GetInstance().DecideNextBallState();
}

void NextManager::onFire() {
   queue.pop_front(); // 発射された弾を管理から外す

   // 既存の弾の目標座標をずらす
   if (!queue.empty()) {
      queue.front().targetX = SLOT0_X;
      queue.front().targetY = SLOT0_Y;
   }

   // 新しい弾を Slot1 に生成 (blinkTimerもランダムな値で初期化)
   NextBall newBall = { GlidManager::GetInstance().DecideNextBallState(), SLOT1_X - 50, SLOT1_Y, SLOT1_X, SLOT1_Y, true, GetRandomI(0, 300)};
   queue.push_back(newBall);
}

void NextManager::Update() {
   for (auto& ball : queue) {
      ball.update();
   }
}

void NextManager::Render() {
    DrawRectRotaGraph(SLOT1_X - 30, SLOT1_Y -15, 0, 0, 64, 32, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_NEXT), true);

   for (auto& ball : queue) {
      ball.Render();
   }
    DrawRectRotaGraph(SLOT1_X-30, SLOT1_Y -15, 64, 0, 64, 32, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_NEXT), true);
}
