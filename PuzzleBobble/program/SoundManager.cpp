#include "SoundManager.h"
#include "DxLib.h"
BGMManager& BGMManager::GetInstance()
{
	static BGMManager instance;
	return instance;
}

BGMManager::BGMManager()
{
	//	音声のハンドルを入れる配列を初期化
	for (int i = 0; i < BGM_MAX; i++) {
		BGMs[i] = -1;
	}
	BGMs[0] = LoadMusicMem("data/sound/player.wav");

}

BGMManager::~BGMManager()
{
	//	音声のハンドルを解放
	for (int i = 0; i < BGM_MAX; i++) {
		DeleteSoundMem(BGMs[i]);
		BGMs[i] = -1;
	}
}
//========================================================
SEManager& SEManager::GetInstance()
{
	static SEManager instance;
	return instance;
}

SEManager::SEManager()
{
	//	効果音のハンドルを入れる配列を初期化
	for (int i = 0; i < SE_MAX; i++) {
		SEs[i] = -1;
	}
	SEs[0] = LoadSoundMem("data/sound/jump.wav");
}
SEManager::~SEManager()
{
	//	効果音のハンドルを解放
	for (int i = 0; i < SE_MAX; i++) {
		DeleteSoundMem(SEs[i]);
		SEs[i] = -1;
	}
}