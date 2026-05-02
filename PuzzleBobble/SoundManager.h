#pragma once
constexpr int BGM_MAX = 10;	//	音声の最大数
//--------------------------------------------------
enum BGM_LIST {
	BGM_PLAYER,	//	プレイヤーの音声
};
//--------------------------------------------------
class BGMManager
{
public:
	static BGMManager& GetInstance();
private:
	BGMManager();
	~BGMManager();

	BGMManager(const BGMManager&) = delete;
	BGMManager& operator=(const BGMManager&) = delete;

	int BGMs[BGM_MAX];	//	音声のハンドルを入れる配列
public:
	int GetBGM(int num) const { return BGMs[num]; }
};
//========================================================
constexpr int SE_MAX = 10;	//	効果音の最大数
//--------------------------------------------------
enum SE_LIST {
	SE_JUMP,	//	ジャンプの効果音
};
//--------------------------------------------------
class SEManager
{
public:
	static SEManager& GetInstance();
private:
	SEManager();
	~SEManager();

	SEManager(const SEManager&) = delete;
	SEManager& operator=(const SEManager&) = delete;

	int SEs[SE_MAX];	//	効果音のハンドルを入れる配列
public:
	int GetSE(int num) const { return SEs[num]; }
};