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
	for( int i=0; i<IMAGE_MAX; i++ ){
		images[i] = -1;
	}
	images[0] = LoadGraph("data/allow.png");	
	images[1] = LoadGraph("data/redBall_idle.png");
	images[2] = LoadGraph("data/greenBall_idle.png");
	images[3] = LoadGraph("data/blueBall_idle.png");
	images[4] = LoadGraph("data/yellowBall_idle.png");
	images[5] = LoadGraph("data/purpleBall_idle.png");
	images[6] = LoadGraph("data/whiteBall_idle.png");
	images[7] = LoadGraph("data/blackBall_idle.png");
}

ImageManager::~ImageManager()
{
	//	画像のハンドルを解放
	for( int i=0; i<IMAGE_MAX; i++ ){
		DeleteGraph(images[i]);
		images[i] = -1;
	}
}