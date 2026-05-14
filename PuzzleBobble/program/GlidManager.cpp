#include "GlidManager.h"
#include "Hit.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "Random.h"
#include <vector>
#include <algorithm>
#include "ImageManager.h"
#include "EffectManager.h"
GlidManager& GlidManager::GetInstance()
{
	static GlidManager instance;
	return instance;
}

GlidManager::GlidManager()
{
	const float cellW = 32.0f; // 16*2
	const float cellH = 32.0f;
	const float rowDistance = 28.0f; // sqrt(32^2 - 16^2) = 27.7 くらいの適切な行間

	for (int row = 0; row < ROWS; ++row) {
		// 奇数行のオフセットシフトを考慮する
		float offset_x = (row % 2 == 1) ? (VS_X + 16.0f) : VS_X;
		for (int col = 0; col < COLS; ++col) {
			glid[row][col].state = EMPTY;
			// 座標を一度だけ計算して保持させておく
			glid[row][col].pos.x = col * cellW + cellW / 2.0f + offset_x;
			glid[row][col].pos.y = row * rowDistance + cellH / 2.0f + top;
			glid[row][col].blinkTimer = GetRandomI(0, 300);
			glid[row][col].isGameOverGray = false;
		}
	}
	isGameOverAnimating = false;
	gameOverGrayTimer = 0;
	gameOverScanRow = ROWS - 1;
	gameOverScanCol = COLS - 1;
}
void GlidManager::Init()
{
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLS; ++col) {
			glid[row][col].state = EMPTY;
			glid[row][col].blinkTimer = GetRandomI(0, 300); // ばらばらに瞬きさせるために初期値をランダムに設定
			glid[row][col].luminusTimer = 0;
			glid[row][col].wasLuminus = true;
			glid[row][col].isGameOverGray = false;
		}
	}
	top = VS_Y;
	dropTimer = 0;
	isWaitingToDrop = false;
	deadLineRowOffset = 0;
	isGameOverAnimating = false;
	gameOverGrayTimer = 0;
	gameOverScanRow = ROWS - 1;
	gameOverScanCol = COLS - 1;
	for (int row = 0; row < ROWS; ++row) {
		float offset_x = (row % 2 == 1) ? (VS_X + 16.0f) : VS_X;
		for (int col = 0; col < COLS; ++col) {
			glid[row][col].pos.y = row * 28.0f + 16.0f + top;
		}
	}
}

void GlidManager::AddGlid(short state, int row, int col)
{
	if (row >= 0 && row < ROWS && col >= 0 && col < COLS && glid[row][col].state == EMPTY) {
		glid[row][col].state = state;
		glid[row][col].luminusTimer = 0;
		glid[row][col].wasLuminus = false;
		glid[row][col].isGameOverGray = false;
	}
}

bool GlidManager::CheckCircleCollision(float ballX, float ballY, float ballR)
{
	const float cellR = 16.0f;

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

void GlidManager::Update(bool isBallFlying)
{
	// 弾が飛んでいない(存在しない)時のみタイマーを進める
	if (!isBallFlying) {
		dropTimer++;

		// 440フレーム時点に達したら振動開始フラグをONにする
		if (dropTimer >= 440) {
			isWaitingToDrop = true;
		}

		// 振動が始まってから一定時間（600フレーム＝約10秒の地点）経ったら、撃たなくても強制的に天井を下げる
		if (dropTimer >= 600) {
			NotifyBallLanded(); // 既存の「待機状態を解除して天井を1段下げる処理」を呼び出す
		}
	}

	if (isGameOverAnimating) {
		gameOverGrayTimer++;
		if (gameOverGrayTimer >= GAMEOVER_GRAY_INTERVAL) {
			gameOverGrayTimer = 0;
			while (gameOverScanRow >= 0) {
				auto& cell = glid[gameOverScanRow][gameOverScanCol];
				if (cell.state != EMPTY && cell.state != INVALID) {
					cell.isGameOverGray = true;
					gameOverScanCol--;
					if (gameOverScanCol < 0) {
						gameOverScanCol = COLS - 1;
						gameOverScanRow--;
					}
					break;
				}
				gameOverScanCol--;
				if (gameOverScanCol < 0) {
					gameOverScanCol = COLS - 1;
					gameOverScanRow--;
				}
			}
			if (gameOverScanRow < 0) {
				isGameOverAnimating = false;
			}
		}
	}

	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLS; ++col) {
			if (glid[row][col].state != EMPTY && glid[row][col].state != INVALID) {
				glid[row][col].blinkTimer++;
				// 瞬きの周期を設定 (約300フレーム = 約5秒に1回瞬き)
				if (glid[row][col].blinkTimer >= 300) {
					glid[row][col].blinkTimer = 0;
				}
				if (glid[row][col].wasLuminus == false)
				{
					glid[row][col].luminusTimer++;
					if (5 * LUMINUS_INTERVAL <= glid[row][col].luminusTimer)
					{
						glid[row][col].wasLuminus = true;
					}
				}
			}
		}
	}

}

void GlidManager::Render()
{
	float quakeX = 0.0f;
	float quakeY = 0.0f;

	if (isWaitingToDrop) {
		quakeX = GetRandomI(-1, 1) * 2.0f;
		quakeY = GetRandomI(-1, 1) * 2.0f;
	}

	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLS; ++col) {

			auto& cell = glid[row][col];

			if (cell.state == EMPTY || cell.state == INVALID) {
				continue;
			}

			float x = cell.pos.x + quakeX;
			float y = cell.pos.y + quakeY;

			// 点滅アニメ
			int srcX = 0;

			if (cell.blinkTimer >= 290) {

				int frame = cell.blinkTimer - 290;

				if (frame < 3) {
					srcX = 16;
				}
				else if (frame < 7) {
					srcX = 32;
				}
			}

			// 本体描画
			if (cell.isGameOverGray) {
				int graySrcX = (cell.state - 1) * 16;
				DrawRectRotaGraph(x, y, graySrcX, 0, 16, 16, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_BUBBLE_GRAY), true);
			}
			else {
				DrawRectRotaGraph(x,y,srcX,0,16,32,2.0f,0,ImageManager::GetInstance().GetImage(ImageManager::GetInstance().GetBubbleImage(cell.state)),true);

			// 発光
				if (!cell.wasLuminus) {
					DrawRectRotaGraph(x,y,(cell.luminusTimer / LUMINUS_INTERVAL) * 16,0,16,32,2.0f,0,ImageManager::GetInstance().GetImage(ImageManager::GetInstance().GetLuminusImage(cell.state)),true);
				}
			}
		}
	}
}
void GlidManager::NotifyBallLanded()
{
	// 通知を受けたら（＝弾が着弾したら）、待機状態を解除して即座に天井を下げる
	if (isWaitingToDrop) {
		isWaitingToDrop = false;
		dropTimer = 0; // タイマーリセット
		top += 28.0f; // 天井を一段分下げる
		deadLineRowOffset++; // 天井が一行分下がったので、デッドラインの行も一つ上に上げる

		// 全てのセルの位置を再計算してずらす
		const float rowDistance = 28.0f;
		for (int row = 0; row < ROWS; ++row) {
			float offset_x = (row % 2 == 1) ? (VS_X + 16.0f) : VS_X;
			for (int col = 0; col < COLS; ++col) {
				glid[row][col].pos.y = row * rowDistance + 16.0f + top;
			}
		}
	}
}

void GlidManager::SetGlid(int StageNum)
{
	deadLineRowOffset = 0;
	for (int row = 0; row < GlidManager::ROWS; ++row) {
		for (int col = 0; col < GlidManager::COLS; ++col) {
			glid[row][col].state = StageData[StageNum][row][col];
			glid[row][col].isGameOverGray = false;
		}
	}
	isGameOverAnimating = false;
	gameOverGrayTimer = 0;
	gameOverScanRow = ROWS - 1;
	gameOverScanCol = COLS - 1;
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

void GlidManager::CheckMatchAndRemoveGlid(int NewR, int NewC, int state)
{
	if (state == EMPTY || state == INVALID) return;

	// すでに探索済みかどうか
	bool visited[ROWS][COLS] = { false };

	// even(偶数)の探索方向、odd(奇数)の探索方向を分けてつくっておく
	int evenOffsets[6][2] = { {-1, -1}, {-1, 0}, {0, -1}, {0, 1}, {1, -1}, {1, 0} };
	int oddOffsets[6][2] = { {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, 0}, {1, 1} };

	// つながりを保存するリスト
	std::vector<std::pair<int, int>> connected;
	// 探索するための待ち列
	std::vector<std::pair<int, int>> queue;

	// 新しく追加された位置から探索を開始
	queue.push_back({ NewR, NewC });
	connected.push_back({ NewR, NewC });
	visited[NewR][NewC] = true;

	// 待ち列がなくなるまで探索を続ける
	int head = 0;
	while (head < queue.size()) {
		int cr = queue[head].first;
		int cc = queue[head].second;
		head++;

		// 奇数なら奇数の探索方向、偶数なら偶数の探索方向を使う
		auto offsets = (cr % 2 == 0) ? evenOffsets : oddOffsets;

		for (int i = 0; i < 6; ++i) {
			// cr,cc(探索してるセル)にoffset(探索方向)を足して、nr,nc(次に探索するセル)を計算する
			int nr = cr + offsets[i][0];
			int nc = cc + offsets[i][1];

			// グリッド範囲内で、探索していなくて、同じ色のセルを見つけたら、つながったよリストに入れて待ち列に追加する
			if (nr >= 0 && nr < ROWS && nc >= 0 && nc < COLS) {
				if (!visited[nr][nc] && glid[nr][nc].state == state) {
					visited[nr][nc] = true;
					queue.push_back({ nr, nc });
					connected.push_back({ nr, nc });
				}
			}
		}
	}

	// 3つ以上つながっていたら消す
	if (connected.size() >= 3) {
		for (const auto& pos : connected) {
			glid[pos.first][pos.second].state = EMPTY;
			EffectManager::GetInstance().AddPopEffect(glid[pos.first][pos.second].pos.x, glid[pos.first][pos.second].pos.y, state);
			EffectManager::GetInstance().AddDropMonsterEffect(glid[pos.first][pos.second].pos.x, glid[pos.first][pos.second].pos.y, state);
		}
	}
}

void GlidManager::CheckConnectAndRemoveGlid()
{
	// 天井からつながっているかどうか
	bool visited[ROWS][COLS] = { false };

	// even(偶数)の探索方向、odd(奇数)の探索方向を分けてつくっておく
	int evenOffsets[6][2] = { {-1, -1}, {-1, 0}, {0, -1}, {0, 1}, {1, -1}, {1, 0} };
	int oddOffsets[6][2] = { {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, 0}, {1, 1} };

	// 探索するための待ち列
	std::vector<std::pair<int, int>> queue;

	// 1. 一番上の列（天井）にあるグリッドをすべてキューに入れ、探索開始地点にする
	for (int c = 0; c < COLS; ++c) {
		if (glid[0][c].state != EMPTY && glid[0][c].state != INVALID) {
			queue.push_back({ 0, c });
			visited[0][c] = true; // 天井とつながっている
		}
	}

	// 2. 待ち列がなくなるまで探索を続ける（天井からつながっているグリッドを全て洗い出す）
	int head = 0;
	while (head < queue.size()) {
		int cr = queue[head].first;
		int cc = queue[head].second;
		head++;

		// 奇数なら奇数の探索方向、偶数なら偶数の探索方向を使う
		auto offsets = (cr % 2 == 0) ? evenOffsets : oddOffsets;

		for (int i = 0; i < 6; ++i) {
			// cr,cc(探索してるセル)にoffset(探索方向)を足して、nr,nc(次に探索するセル)を計算する
			int nr = cr + offsets[i][0];
			int nc = cc + offsets[i][1];

			// グリッド範囲内で、まだ探索していなくて、空じゃないセルを見つけたら次に探索するために追加する
			if (nr >= 0 && nr < ROWS && nc >= 0 && nc < COLS) {
				if (!visited[nr][nc] && glid[nr][nc].state != EMPTY && glid[nr][nc].state != INVALID) {
					visited[nr][nc] = true;
					queue.push_back({ nr, nc });
				}
			}
		}
	}

	// 3. 全てのつながりを調べた後、天井からつながっていなかったグリッドをすべて消す
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLS; ++col) {
			if (glid[row][col].state != EMPTY && glid[row][col].state != INVALID && !visited[row][col]) {
				EffectManager::GetInstance().AddDropBubbleEffect(glid[row][col].pos.x, glid[row][col].pos.y, glid[row][col].state);
				glid[row][col].state = EMPTY; // 天井から切り離されているので消去
			}
		}
	}
}

int GlidManager::DecideNextBallState()
{
	//存在している色を格納していくリスト
	std::vector<int> availableColors;
	// グリッド内に存在する色を調べる
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLS; ++col) {
			int state = glid[row][col].state;
			if (state != EMPTY && state != INVALID) {
				// すでにリストにある色は追加しない
				// std::find vector,arrayなどで使用可能。あった場合はその位置へのイテレータ(独自のポインタのようなもの)を返し、ない場合は終端の次のイテレータ(もう終わりましたよイテレータ)を返す。
				if (std::find(availableColors.begin(), availableColors.end(), state) == availableColors.end()) {
					availableColors.push_back(state);
				}
			}
		}
	}
	//emptyになることはないと思うが、一応赤を出しておく。
	if (availableColors.empty()) {
		return RED;
	}
	else {
		// 利用可能な色からランダムに選ぶ
		int randomIndex = GetRandomI(0, availableColors.size() - 1);
		return availableColors[randomIndex];
	}
}

bool GlidManager::IsClear()
{
	// グリッドの中に有効なボール(色付きボール)が1つでも残っていればクリアしていない
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLS; ++col) {
			if (glid[row][col].state != EMPTY && glid[row][col].state != INVALID) {
				return false;
			}
		}
	}
	return true; // 全てEMPTYまたはINVALIDになればクリア
}

bool GlidManager::IsGameOver()
{
	// 配列の一番下（ROWS - 1）から、天井が下がった回数分だけデッドラインを引き上げる
	int deadLineRow = ROWS - 1 - deadLineRowOffset;

	// デッドラインが0以下になったら（限界まで下がったら）問答無用でゲームオーバー
	if (deadLineRow < 0) {
		return true;
	}

	for (int col = 0; col < COLS; ++col) {
		if (glid[deadLineRow][col].state != EMPTY && glid[deadLineRow][col].state != INVALID) {
			return true;
		}
	}
	return false;
}

bool GlidManager::IsGameOverAnimationFinished() const
{
	return !isGameOverAnimating && gameOverScanRow < 0;
}

void GlidManager::GameOver()
{
	if (!isGameOverAnimating) {
		isGameOverAnimating = true;
		gameOverGrayTimer = 0;
		gameOverScanRow = ROWS - 1;
		gameOverScanCol = COLS - 1;
	}
}