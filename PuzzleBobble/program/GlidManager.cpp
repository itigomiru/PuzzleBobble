#include "GlidManager.h"
#include "Hit.h"
#include "DxLib.h"
#include "SceneManager.h"
GlidManager& GlidManager::GetInstance()
{
    static GlidManager instance;
    return instance;
}

GlidManager::GlidManager()
{
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            glid[row][col].state = EMPTY;
        }
    }
}
GlidManager::~GlidManager()
{
}

void GlidManager::AddGlid(BallController* ball, int row, int col)
{
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
        glid[row][col].state = ball->GetBallColor(); 
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
            if (glid[row][col].state != EMPTY) {
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

void GlidManager::Render()
{
    const float cellW = 50.0f; 
    const float cellH = 50.0f; 
	float offset_x = VS_X;
    for (int row = 0; row < ROWS; ++row) {
        if(row % 2 == 1)  offset_x = VS_X + 25.0f;   //奇数は描画ずらす
		else offset_x = VS_X;
        for (int col = 0; col < COLS; ++col) {
            if (glid[row][col].state != EMPTY) {
                int color = glid[row][col].state;
                int dxColor = GetColor(255, 255, 255); 
                switch (color) {
                    case RED: dxColor = GetColor(255, 0, 0); break;
                    case GREEN: dxColor = GetColor(0, 255, 0); break;
                    case BLUE: dxColor = GetColor(0, 0, 255); break;
                    case YELLOW: dxColor = GetColor(255, 255, 0); break;
                }
                float cx, cy;
                GetCellCenter(row, col, cx, cy);
                DrawCircle(cx + offset_x, cy + offset_y, 25.0f, dxColor, true);
            }
        }
    }
}

void GlidManager::SetGlid(int StageNum)
{
    for(int row = 0; row < GlidManager::ROWS; ++row) {
        for(int col = 0; col < GlidManager::COLS; ++col) {
			glid[row][col].state = StageData[StageNum][row][col].state;
        }
	}
    
}