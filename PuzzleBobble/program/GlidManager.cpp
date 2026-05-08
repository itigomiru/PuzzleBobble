#include "GlidManager.h"
#include "Hit.h"
#include "DxLib.h"

void GlidManager::AddGlid(BallController* ball, int row, int col)
{
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
        glid[row][col].isEmpty = false;
        glid[row][col].color = ball->GetBallColor(); 
    }
}
// グリッド1マスの中心座標を計算する関数
void GlidManager::GetCellCenter(int row, int col, float& cx, float& cy)
{
    const float cellW = 50.0f; 
    const float cellH = 50.0f; 
    cx = col * cellW + cellW / 2.0f;
    cy = row * cellH + cellH / 2.0f;
}

// 円同士の当たり判定
bool GlidManager::CheckCircleCollision(float ballX, float ballY, float ballR)
{
    const float cellR = 25.0f; // グリッドセルの半径（描画と合わせて調整）

    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            if (!glid[row][col].isEmpty) {
                float cx, cy;
                GetCellCenter(row, col, cx, cy);
                float dx = ballX - cx;
                float dy = ballY - cy;
				CheckCircleHit(ballX, ballY, ballR, cx, cy, cellR);
            }
        }
    }
    return false;
}