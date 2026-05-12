#include <deque>
#include "NextManager.h"
#include "GlidManager.h"
#include "NextBallController.h"

void NextManager::onFire() {
   queue.pop_front(); // 発射された弾を管理から外す

   // 既存の弾の目標座標をずらす
   queue.targetX = SLOT0_X;
   queue.targetY = SLOT0_Y;
   // ... queueも同様

   // 新しい弾を Slot1 に生成
   NextBall newBall = { GlidManager::GetInstance().DecideNextBallState(), SLOT1_X + 50, SLOT1_Y, SLOT1_X, SLOT1_Y, true}; // メソッド呼び出しに変更
   newBall.targetX = SLOT1_X;
   queue.push_back(newBall);
}