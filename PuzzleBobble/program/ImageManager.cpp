#include "ImageManager.h"
#include "DxLib.h"
ImageManager& ImageManager::GetInstance()
{
	static ImageManager instance;
	return instance;
}

ImageManager::ImageManager()
{
	//	画像のハンドルを入れる配列を初期化
	for (int i = 0; i < IMAGE_MAX; i++) {
		images[i] = -1;
	}
	images[IMAGE_STAGE1] = LoadGraph("data/stage1.png");
	images[IMAGE_WALL_STAGE1] = LoadGraph("data/wall1.png");
	images[IMAGE_SHUTTER_STAGE1] = LoadGraph("data/shutter1.png");
	images[IMAGE_ALLOW] = LoadGraph("data/allow.png");
	images[IMAGE_RED_IDLE] = LoadGraph("data/redBall_idle.png");
	images[IMAGE_GREEN_IDLE] = LoadGraph("data/greenBall_idle.png");
	images[IMAGE_BLUE_IDLE] = LoadGraph("data/blueBall_idle.png");
	images[IMAGE_YELLOW_IDLE] = LoadGraph("data/yellowBall_idle.png");
	images[IMAGE_PURPLE_IDLE] = LoadGraph("data/purpleBall_idle.png");
	images[IMAGE_WHITE_IDLE] = LoadGraph("data/whiteBall_idle.png");
	images[IMAGE_BLACK_IDLE] = LoadGraph("data/blackBall_idle.png");
	images[IMAGE_LEFT_BABBLEN] = LoadGraph("data/leftBabblen.png");
	images[IMAGE_RIGHT_BABBLEN] = LoadGraph("data/rightBabblen.png");
	images[IMAGE_NEXT] = LoadGraph("data/next.png");
	images[IMAGE_LAUNCHER_BASE] = LoadGraph("data/launcher.png");
	images[IMAGE_LAUNCHER_PIPE] = LoadGraph("data/launcher_pipe.png");
	images[IMAGE_BAR] = LoadGraph("data/bar.png");
}

ImageManager::~ImageManager()
{
	//	画像のハンドルを解放
	for (int i = 0; i < IMAGE_MAX; i++) {
		DeleteGraph(images[i]);
		images[i] = -1;
	}
}