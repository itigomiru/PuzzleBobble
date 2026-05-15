#include "SoundManager.h"
#include "DxLib.h"



//========================================================
SoundManager& SoundManager::GetInstance()
{
	static SoundManager instance;
	return instance;
}

SoundManager::SoundManager()
{
	//	効果音のハンドルを入れる配列を初期化
	for (int i = 0; i < SE_MAX; i++) {
		SEs[i] = -1;
	}
	//	音声のハンドルを入れる配列を初期化
	for (int i = 0; i < BGM_MAX; i++) {
		BGMs[i] = -1;
	}

	BGMs[BGM_TITLE] = LoadMusicMem("data/sound/title_bgm.mp3");
	BGMs[BGM_STAGE] = LoadMusicMem("data/sound/stage_bgm.mp3");
	BGMs[BGM_CLEAR] = LoadMusicMem("data/sound/clear_bgm.mp3");
	BGMs[BGM_ENDING] = LoadMusicMem("data/sound/ending_bgm.mp3");
	BGMs[BGM_GAMEOVER] = LoadMusicMem("data/sound/gameover_bgm.mp3");
	//-----------------------------------------------
	SetVolumeMusicMem(128, BGMs[BGM_TITLE]);
	SetVolumeMusicMem(128, BGMs[BGM_STAGE]);
	SetVolumeMusicMem(128, BGMs[BGM_CLEAR]);
	SetVolumeMusicMem(128, BGMs[BGM_ENDING]);
	SetVolumeMusicMem(128, BGMs[BGM_GAMEOVER]);
	//-----------------------------------------------
	SEs[SE_READY] = LoadSoundMem("data/sound/ready.wav");
	SEs[SE_GO] = LoadSoundMem("data/sound/go.wav");
	SEs[SE_TAP] = LoadSoundMem("data/sound/tap.wav");
	SEs[SE_POP] = LoadSoundMem("data/sound/pop.wav");
	SEs[SE_POPCOMBO] = LoadSoundMem("data/sound/popCombo.wav");
	SEs[SE_TAPPOP] = LoadSoundMem("data/sound/tapPop.wav");
	SEs[SE_TOP] = LoadSoundMem("data/sound/top.wav");
	SEs[SE_MISS] = LoadSoundMem("data/sound/miss.wav");

	//-----------------------------------------------
	ChangeVolumeSoundMem(128, SEs[SE_TAP]);
	ChangeVolumeSoundMem(128, SEs[SE_READY]);
	ChangeVolumeSoundMem(128, SEs[SE_GO]);
	ChangeVolumeSoundMem(80, SEs[SE_POP]);
	ChangeVolumeSoundMem(80, SEs[SE_POPCOMBO]);
	ChangeVolumeSoundMem(100, SEs[SE_TAPPOP]);
	ChangeVolumeSoundMem(100, SEs[SE_TOP]);
	ChangeVolumeSoundMem(150, SEs[SE_MISS]);
}

SoundManager::~SoundManager()
{
	//	効果音のハンドルを解放
	for (int i = 0; i < SE_MAX; i++) {
		DeleteSoundMem(SEs[i]);
		SEs[i] = -1;
	}
	//	音声のハンドルを解放
	for (int i = 0; i < BGM_MAX; i++) {
		DeleteSoundMem(BGMs[i]);
		BGMs[i] = -1;
	}
}

void SoundManager::StopAllBGM(){
	for (int i = 0; i < BGM_MAX; i++) {
		if (BGMs[i] != -1) {
			StopMusicMem(BGMs[i]);
		}
	}
}
