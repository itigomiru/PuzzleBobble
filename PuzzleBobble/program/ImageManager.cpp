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
	images[IMAGE_RED_LUMINUS] = LoadGraph("data/redBall_luminus.png");
	images[IMAGE_RED_POP] = LoadGraph("data/redBall_pop.png");
	images[IMAGE_GREEN_IDLE] = LoadGraph("data/greenBall_idle.png");
	images[IMAGE_GREEN_LUMINUS] = LoadGraph("data/greenBall_luminus.png");
	images[IMAGE_GREEN_POP] = LoadGraph("data/greenBall_pop.png");
	images[IMAGE_BLUE_IDLE] = LoadGraph("data/blueBall_idle.png");
	images[IMAGE_BLUE_LUMINUS] = LoadGraph("data/blueBall_luminus.png");
	images[IMAGE_BLUE_POP] = LoadGraph("data/blueBall_pop.png");
	images[IMAGE_YELLOW_IDLE] = LoadGraph("data/yellowBall_idle.png");
	images[IMAGE_YELLOW_LUMINUS] = LoadGraph("data/yellowBall_luminus.png");
	images[IMAGE_YELLOW_POP] = LoadGraph("data/yellowBall_pop.png");
	images[IMAGE_PURPLE_IDLE] = LoadGraph("data/purpleBall_idle.png");
	images[IMAGE_PURPLE_LUMINUS] = LoadGraph("data/purpleBall_luminus.png");
	images[IMAGE_PURPLE_POP] = LoadGraph("data/purpleBall_pop.png");
	images[IMAGE_WHITE_IDLE] = LoadGraph("data/whiteBall_idle.png");
	images[IMAGE_WHITE_LUMINUS] = LoadGraph("data/whiteBall_luminus.png");
	images[IMAGE_WHITE_POP] = LoadGraph("data/whiteBall_pop.png");
	images[IMAGE_BLACK_IDLE] = LoadGraph("data/blackBall_idle.png");
	images[IMAGE_BLACK_LUMINUS] = LoadGraph("data/blackBall_luminus.png");
	images[IMAGE_BLACK_POP] = LoadGraph("data/blackBall_pop.png");
	images[IMAGE_ORANGE_IDLE] = LoadGraph("data/orangeBall_idle.png");
	images[IMAGE_ORANGE_LUMINUS] = LoadGraph("data/orangeBall_luminus.png");
	images[IMAGE_ORANGE_POP] = LoadGraph("data/orangeBall_pop.png");
	images[IMAGE_MONSTER_RED] = LoadGraph("data/monster_red.png");
	images[IMAGE_MONSTER_GREEN] = LoadGraph("data/monster_green.png");
	images[IMAGE_MONSTER_BLUE] = LoadGraph("data/monster_blue.png");
	images[IMAGE_MONSTER_YELLOW] = LoadGraph("data/monster_yellow.png");
	images[IMAGE_MONSTER_PURPLE] = LoadGraph("data/monster_purple.png");
	images[IMAGE_MONSTER_WHITE] = LoadGraph("data/monster_white.png");
	images[IMAGE_MONSTER_BLACK] = LoadGraph("data/monster_black.png");
	images[IMAGE_MONSTER_ORANGE] = LoadGraph("data/monster_orange.png");
	images[IMAGE_LEFT_BABBLEN] = LoadGraph("data/leftBabblen.png");
	images[IMAGE_RIGHT_BABBLEN] = LoadGraph("data/rightBabblen.png");
	images[IMAGE_NEXT] = LoadGraph("data/next.png");
	images[IMAGE_LAUNCHER_BASE] = LoadGraph("data/launcher.png");
	images[IMAGE_LAUNCHER_PIPE] = LoadGraph("data/launcher_pipe.png");
	images[IMAGE_BAR] = LoadGraph("data/bar.png");
	images[IMAGE_ROUNDBOARD] = LoadGraph("data/roundBoard.png");
	images[IMAGE_NUMBER] = LoadGraph("data/number.png");
	images[IMAGE_TITLE_BG] = LoadGraph("data/title_bg.png");
	images[IMAGE_TITLE_BABBLEN] = LoadGraph("data/title_babblen.png");
	images[IMAGE_TITLE_BOBBLEN] = LoadGraph("data/title_bobblen.png");
	images[IMAGE_ROUND_CLEAR] = LoadGraph("data/round_clear.png");
	images[IMAGE_BUBBLE_GRAY] = LoadGraph("data/bubble_gray.png");
}

ImageManager::~ImageManager()
{
	//	画像のハンドルを解放
	for (int i = 0; i < IMAGE_MAX; i++) {
		DeleteGraph(images[i]);
		images[i] = -1;
	}
}

int ImageManager::GetPopImage(int state)
{
	switch (state)
	{
	case RED: return IMAGE_RED_POP;
	case GREEN: return IMAGE_GREEN_POP;
	case BLUE: return IMAGE_BLUE_POP;
	case YELLOW: return IMAGE_YELLOW_POP;
	case PURPLE: return IMAGE_PURPLE_POP;
	case WHITE: return IMAGE_WHITE_POP;
	case BLACK: return IMAGE_BLACK_POP;
	case ORANGE: return IMAGE_ORANGE_POP;
	default: return -1;
	}
}

int ImageManager::GetMonsterImage(int state)
{
	switch (state)
	{
	case RED: return IMAGE_MONSTER_RED;
	case GREEN: return IMAGE_MONSTER_GREEN;
	case BLUE: return IMAGE_MONSTER_BLUE;
	case YELLOW: return IMAGE_MONSTER_YELLOW;
	case PURPLE: return IMAGE_MONSTER_PURPLE;
	case WHITE: return IMAGE_MONSTER_WHITE;
	case BLACK: return IMAGE_MONSTER_BLACK;
	case ORANGE: return IMAGE_MONSTER_ORANGE;
	default: return -1;
	}
}

int ImageManager::GetBubbleImage(int state)
{
	switch (state)
	{
	case RED: return IMAGE_RED_IDLE;
	case GREEN: return IMAGE_GREEN_IDLE;
	case BLUE: return IMAGE_BLUE_IDLE;
	case YELLOW: return IMAGE_YELLOW_IDLE;
	case PURPLE: return IMAGE_PURPLE_IDLE;
	case WHITE: return IMAGE_WHITE_IDLE;
	case BLACK: return IMAGE_BLACK_IDLE;
	case ORANGE: return IMAGE_ORANGE_IDLE;
	default: return -1;
	}
}
int ImageManager::GetLuminusImage(int state)
{
	switch (state)
	{
	case RED: return IMAGE_RED_LUMINUS;
	case GREEN: return IMAGE_GREEN_LUMINUS;
	case BLUE: return IMAGE_BLUE_LUMINUS;
	case YELLOW: return IMAGE_YELLOW_LUMINUS;
	case PURPLE: return IMAGE_PURPLE_LUMINUS;
	case WHITE: return IMAGE_WHITE_LUMINUS;
	case BLACK: return IMAGE_BLACK_LUMINUS;
	case ORANGE: return IMAGE_ORANGE_LUMINUS;
	default: return -1;
	}
}

