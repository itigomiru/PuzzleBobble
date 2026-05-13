#pragma once
constexpr int IMAGE_MAX = 50;	//	画像の最大数
enum IMAGE_LIST {
	IMAGE_STAGE1,	//	ステージの背景
	IMAGE_WALL_STAGE1,
	IMAGE_SHUTTER_STAGE1,
	IMAGE_ALLOW,	//	プレイヤーの画像
	IMAGE_RED_IDLE,
	IMAGE_RED_LUMINUS,
	IMAGE_GREEN_IDLE,
	IMAGE_GREEN_LUMINUS,
	IMAGE_BLUE_IDLE,
	IMAGE_BLUE_LUMINUS,
	IMAGE_YELLOW_IDLE,
	IMAGE_YELLOW_LUMINUS,
	IMAGE_PURPLE_IDLE,
	IMAGE_PURPLE_LUMINUS,
	IMAGE_WHITE_IDLE,
	IMAGE_WHITE_LUMINUS,
	IMAGE_BLACK_IDLE,
	IMAGE_BLACK_LUMINUS,
	IMAGE_LEFT_BABBLEN,
	IMAGE_RIGHT_BABBLEN,
	IMAGE_NEXT,
	IMAGE_LAUNCHER_BASE,
	IMAGE_LAUNCHER_PIPE,
	IMAGE_BAR,

};


class ImageManager
{
	public:
		static ImageManager& GetInstance();
	private:
		ImageManager();
		~ImageManager();
		ImageManager(const ImageManager&) = delete;
		ImageManager& operator=(const ImageManager&) = delete;

		int images[IMAGE_MAX];	//	画像のハンドルを入れる配列
public:
	int GetImage(int num) const { return images[num]; }
};