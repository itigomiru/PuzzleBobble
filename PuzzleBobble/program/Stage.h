#pragma once

enum stage_states
{
	STAGE_READY,
	STAGE_PLAYING,
	STAGE_CLEAR,
	STAGE_GAMEOVER,
};
int stage_state = STAGE_READY; // ステージの状態を管理する変数
//	ステージで使う関数の宣言
void StageInit();
void StageUpdate();
void StageRender();
void StageExit();
