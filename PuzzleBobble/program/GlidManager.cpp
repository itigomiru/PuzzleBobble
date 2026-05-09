#include "GlidManager.h"
#include "Hit.h"
#include "DxLib.h"
#include "SceneManager.h"
#include <vector>

GlidManager& GlidManager::GetInstance()
{
    static GlidManager instance;
    return instance;
}

GlidManager::GlidManager()
{
    const float cellW = 50.0f;
    const float cellH = 50.0f;

    for (int row = 0; row < ROWS; ++row) {
        // 奇数行のオフセットシフトを考慮する
        float offset_x = (row % 2 == 1) ? (VS_X + 25.0f) : VS_X;
        for (int col = 0; col < COLS; ++col) {
            glid[row][col].state = EMPTY;
            // 座標を一度だけ計算して保持させておく
            glid[row][col].pos.x = col * cellW + cellW / 2.0f + offset_x;
            glid[row][col].pos.y = row * 45.0f + cellH / 2.0f + top;
        }
    }
}



void GlidManager::AddGlid(short state, int row, int col)
{
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS && glid[row][col].state == EMPTY) {
        glid[row][col].state = state;
    }
}

bool GlidManager::CheckCircleCollision(float ballX, float ballY, float ballR)
{
    const float cellR = 25.0f;

    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            if (glid[row][col].state != EMPTY && glid[row][col].state != INVALID) {
                float cx = glid[row][col].pos.x;
                float cy = glid[row][col].pos.y;

                if (CheckCircleHit(ballX, ballY, ballR, cx, cy, cellR) == true) return true;
            }
        }
    }
    return false;
}

void GlidManager::Render()
{
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            if (glid[row][col].state != EMPTY && glid[row][col].state != INVALID) {
                int color = glid[row][col].state;
                int dxColor = GetColor(255, 255, 255);
                switch (color) {
                case RED: dxColor = GetColor(255, 0, 0); break;
                case GREEN: dxColor = GetColor(0, 255, 0); break;
                case BLUE: dxColor = GetColor(0, 0, 255); break;
                case YELLOW: dxColor = GetColor(255, 255, 0); break;
                }

                DrawCircle(glid[row][col].pos.x, glid[row][col].pos.y, 25.0f, dxColor, true);
            }
        }
    }
}

void GlidManager::SetGlid(int StageNum)
{
    for (int row = 0; row < GlidManager::ROWS; ++row) {
        for (int col = 0; col < GlidManager::COLS; ++col) {
            glid[row][col].state = StageData[StageNum][row][col];
        }
    }
}

void GlidManager::GetClosestGlid(Float2 pos, int& outRow, int& outCol)
{
    float minDistance = 999999.0f;
    outRow = 0;
    outCol = 0;

    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            float dist = GetFloat2Distance(pos, glid[row][col].pos);
            if (dist < minDistance) {
                minDistance = dist;
                outRow = row;
                outCol = col;
            }
        }
    }
}

void GlidManager::CheckAndRemoveGlid()
{
	//消すグリッドを保存するリスト
    std::vector<std::pair<int, int>> toRemove;

    //すでに探索済みかどうか。
    bool visited[ROWS][COLS] = { false };

	//even(偶数)の探索方向、odd(奇数)の探索方向を分けてつくっておく
    int evenOffsets[6][2] = { {-1, -1}, {-1, 0}, {0, -1}, {0, 1}, {1, -1}, {1, 0} };
    int oddOffsets[6][2] = { {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, 0}, {1, 1} };

    //すべての要素を探索
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            //グリッドの色を保存しておく
            int state = glid[row][col].state;

			//空、無効、すでに探索済みのセルはとばす
            if (state == EMPTY || state == INVALID || visited[row][col]) {
                continue;
            }

            //つながりを保存するリスト
            std::vector<std::pair<int, int>> connected;
            //同じ色があったら、つぎにここから探索するよの待ち列
            std::vector<std::pair<int, int>> queue;
            
            //まずは最初のセルから始める。
            queue.push_back({ row, col });
            connected.push_back({ row, col });
            visited[row][col] = true;

			//待ち列がなくなるまで探索を続ける
            int head = 0;
            while (head < queue.size()) {
                int cr = queue[head].first;
                int cc = queue[head].second;
                head++;

				//奇数なら奇数の探索方向、偶数なら偶数の探索方向を使う
                auto offsets = (cr % 2 == 0) ? evenOffsets : oddOffsets;

                for (int i = 0; i < 6; ++i) {
					//cr,cc(探索してるセル)にoffset(探索方向)を足して、nr,nc(次に探索するセル)を計算する
                    int nr = cr + offsets[i][0];
                    int nc = cc + offsets[i][1];

                    //グリッド範囲内で、探索していなくて、同じ色のセルを見つけたら、つながったよリストに入れて、次に探索するために待ち列に追加する
                    if (nr >= 0 && nr < ROWS && nc >= 0 && nc < COLS) {
                        if (!visited[nr][nc] && glid[nr][nc].state == state) {
                            visited[nr][nc] = true;
                            queue.push_back({ nr, nc });
                            connected.push_back({ nr, nc });
                        }
                    }
                }
            }
            
            //3つ以上つながってたら、けしますよーにいれる
            if (connected.size() >= 3) {
                for (const auto& pos : connected) {
                    toRemove.push_back(pos);
                }
            }
        }
    }

    //後でまとめて消す
    for (const auto& pos : toRemove) {
        glid[pos.first][pos.second].state = EMPTY;
    }
}