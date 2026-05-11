#include <deque>
#include "NextManager.h"



    void NextManager::onFire() {
        queue.pop_front(); // 発射された弾を管理から外す

        // 既存の弾の目標座標をずらす
        queue.targetX = SLOT0_X;
        queue.targetY = SLOT0_Y;
        // ... queueも同様

        // 新しい弾を Slot2 に生成
        Ball newBall = { getRandomColor(), SLOT2_X + 50, SLOT2_Y }; // 画面外から出すとかっこいい
        newBall.targetX = SLOT2_X;
        queue.push_back(newBall);
    }
};