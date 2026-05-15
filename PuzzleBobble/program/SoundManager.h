#pragma once
constexpr int BGM_MAX = 10;	//	音声の最大数
constexpr int SE_MAX = 10;	//	効果音の最大数
//--------------------------------------------------
enum BGM_LIST {
	BGM_TITLE,	
	BGM_STAGE,
	BGM_CLEAR,
	BGM_ENDING,
	BGM_GAMEOVER,
};
//--------------------------------------------------
enum SE_LIST {
	SE_READY,
	SE_GO,
	SE_TAP,
	SE_POP,
	SE_POPCOMBO,
	SE_TAPPOP,
	SE_TOP,
	SE_MISS,
	
};
//--------------------------------------------------
class SoundManager
{
public:
	static SoundManager& GetInstance();
private:
	SoundManager();
	~SoundManager();

	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;
	
	int BGMs[BGM_MAX];	//	音声のハンドルを入れる配列

	int SEs[SE_MAX];	//	効果音のハンドルを入れる配列
public:
	int GetSE(int num) const { return SEs[num]; }
	int GetBGM(int num) const { return BGMs[num]; }
	void StopAllBGM() ;
};