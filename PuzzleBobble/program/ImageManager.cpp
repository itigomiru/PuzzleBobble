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
	images[IMAGE_STAGE1] =			LoadGraph("data/image/stage1.png");
	images[IMAGE_STAGE2] =			LoadGraph("data/image/stage2.png");
	images[IMAGE_STAGE3] =			LoadGraph("data/image/stage3.png");
	images[IMAGE_STAGE4] =			LoadGraph("data/image/stage4.png");
	images[IMAGE_STAGE5] =			LoadGraph("data/image/stage5.png");
	images[IMAGE_STAGE6] =			LoadGraph("data/image/stage6.png");
	images[IMAGE_STAGE7] =			LoadGraph("data/image/stage7.png");
	images[IMAGE_STAGE8] =			LoadGraph("data/image/stage8.png");
	images[IMAGE_STAGE9] =			LoadGraph("data/image/stage9.png");
	images[IMAGE_WALL_STAGE1] =		LoadGraph("data/image/wall1.png");
	images[IMAGE_WALL_STAGE2] =		LoadGraph("data/image/wall2.png");
	images[IMAGE_WALL_STAGE3] =		LoadGraph("data/image/wall3.png");
	images[IMAGE_WALL_STAGE4] =		LoadGraph("data/image/wall4.png");
	images[IMAGE_WALL_STAGE5] =		LoadGraph("data/image/wall5.png");
	images[IMAGE_WALL_STAGE6] =		LoadGraph("data/image/wall6.png");
	images[IMAGE_WALL_STAGE7] =		LoadGraph("data/image/wall7.png");
	images[IMAGE_WALL_STAGE8] =		LoadGraph("data/image/wall8.png");
	images[IMAGE_WALL_STAGE9] =		LoadGraph("data/image/wall9.png");
	images[IMAGE_SHUTTER_STAGE1] =	LoadGraph("data/image/shutter1.png");
	images[IMAGE_SHUTTER_STAGE2] =	LoadGraph("data/image/shutter2.png");
	images[IMAGE_SHUTTER_STAGE3] =	LoadGraph("data/image/shutter3.png");
	images[IMAGE_SHUTTER_STAGE4] =	LoadGraph("data/image/shutter4.png");
	images[IMAGE_SHUTTER_STAGE5] =	LoadGraph("data/image/shutter5.png");
	images[IMAGE_SHUTTER_STAGE6] =	LoadGraph("data/image/shutter6.png");
	images[IMAGE_SHUTTER_STAGE7] =	LoadGraph("data/image/shutter7.png");
	images[IMAGE_SHUTTER_STAGE8] =	LoadGraph("data/image/shutter8.png");
	images[IMAGE_SHUTTER_STAGE9] =	LoadGraph("data/image/shutter9.png");
	images[IMAGE_ALLOW] =			LoadGraph("data/image/allow.png");
	images[IMAGE_RED_IDLE] =		LoadGraph("data/image/redBall_idle.png");
	images[IMAGE_RED_LUMINUS] =		LoadGraph("data/image/redBall_luminus.png");
	images[IMAGE_RED_POP] =			LoadGraph("data/image/redBall_pop.png");
	images[IMAGE_GREEN_IDLE] =		LoadGraph("data/image/greenBall_idle.png");
	images[IMAGE_GREEN_LUMINUS] =	LoadGraph("data/image/greenBall_luminus.png");
	images[IMAGE_GREEN_POP] =		LoadGraph("data/image/greenBall_pop.png");
	images[IMAGE_BLUE_IDLE] =		LoadGraph("data/image/blueBall_idle.png");
	images[IMAGE_BLUE_LUMINUS] =	LoadGraph("data/image/blueBall_luminus.png");
	images[IMAGE_BLUE_POP] =		LoadGraph("data/image/blueBall_pop.png");
	images[IMAGE_YELLOW_IDLE] =		LoadGraph("data/image/yellowBall_idle.png");
	images[IMAGE_YELLOW_LUMINUS] =	LoadGraph("data/image/yellowBall_luminus.png");
	images[IMAGE_YELLOW_POP] =		LoadGraph("data/image/yellowBall_pop.png");
	images[IMAGE_PURPLE_IDLE] =		LoadGraph("data/image/purpleBall_idle.png");
	images[IMAGE_PURPLE_LUMINUS] =	LoadGraph("data/image/purpleBall_luminus.png");
	images[IMAGE_PURPLE_POP] =		LoadGraph("data/image/purpleBall_pop.png");
	images[IMAGE_WHITE_IDLE] =		LoadGraph("data/image/whiteBall_idle.png");
	images[IMAGE_WHITE_LUMINUS] =	LoadGraph("data/image/whiteBall_luminus.png");
	images[IMAGE_WHITE_POP] =		LoadGraph("data/image/whiteBall_pop.png");
	images[IMAGE_BLACK_IDLE] =		LoadGraph("data/image/blackBall_idle.png");
	images[IMAGE_BLACK_LUMINUS] =	LoadGraph("data/image/blackBall_luminus.png");
	images[IMAGE_BLACK_POP] =		LoadGraph("data/image/blackBall_pop.png");
	images[IMAGE_ORANGE_IDLE] =		LoadGraph("data/image/orangeBall_idle.png");
	images[IMAGE_ORANGE_LUMINUS] =	LoadGraph("data/image/orangeBall_luminus.png");
	images[IMAGE_ORANGE_POP] =		LoadGraph("data/image/orangeBall_pop.png");
	images[IMAGE_MONSTER_RED] =		LoadGraph("data/image/monster_red.png");
	images[IMAGE_MONSTER_GREEN] =	LoadGraph("data/image/monster_green.png");
	images[IMAGE_MONSTER_BLUE] =	LoadGraph("data/image/monster_blue.png");
	images[IMAGE_MONSTER_YELLOW] =	LoadGraph("data/image/monster_yellow.png");
	images[IMAGE_MONSTER_PURPLE] =	LoadGraph("data/image/monster_purple.png");
	images[IMAGE_MONSTER_WHITE] =	LoadGraph("data/image/monster_white.png");
	images[IMAGE_MONSTER_BLACK] =	LoadGraph("data/image/monster_black.png");
	images[IMAGE_MONSTER_ORANGE] =	LoadGraph("data/image/monster_orange.png");
	images[IMAGE_LEFT_BABBLEN] =	LoadGraph("data/image/leftBabblen.png");
	images[IMAGE_RIGHT_BABBLEN] =	LoadGraph("data/image/rightBabblen.png");
	images[IMAGE_NEXT] =			LoadGraph("data/image/next.png");
	images[IMAGE_LAUNCHER_BASE] =	LoadGraph("data/image/launcher.png");
	images[IMAGE_LAUNCHER_PIPE] =	LoadGraph("data/image/launcher_pipe.png");
	images[IMAGE_BAR] =				LoadGraph("data/image/bar.png");
	images[IMAGE_ROUNDBOARD] =		LoadGraph("data/image/roundBoard.png");
	images[IMAGE_NUMBER] =			LoadGraph("data/image/number.png");
	images[IMAGE_NUMBER_REVERSE] = LoadGraph("data/image/number_reverse.png");
	images[IMAGE_SCORE_NUMBER] = LoadGraph("data/image/numberScore.png");
	images[IMAGE_TITLE_BG] =		LoadGraph("data/image/title_bg.png");
	images[IMAGE_TITLE_BABBLEN] =	LoadGraph("data/image/title_babblen.png");
	images[IMAGE_TITLE_BOBBLEN] =	LoadGraph("data/image/title_bobblen.png");
	images[IMAGE_ROUND_CLEAR] =		LoadGraph("data/image/round_clear.png");
	images[IMAGE_BUBBLE_GRAY] =		LoadGraph("data/image/bubble_gray.png");
	images[IMAGE_ENDING1] = LoadGraph("data/image/ending1.png");
	images[IMAGE_ENDING2] = LoadGraph("data/image/ending2.png");
	images[IMAGE_ENDING3] = LoadGraph("data/image/ending3.png");
	images[IMAGE_ENDING_HOUSE]= LoadGraph("data/image/ending_house.png");
	images[IMAGE_CLEAR] = LoadGraph("data/image/clear.png");
	images[IMAGE_STAR] = LoadGraph("data/image/star_bg.png");
	images[IMAGE_STAR_WALL] = LoadGraph("data/image/star_wall.png");
	images[IMAGE_STAR_SHUTTER] = LoadGraph("data/image/star_shutter.png");
	images[IMAGE_GLASS] = LoadGraph("data/image/star_glass.png");
	images[IMAGE_GAMEOVER] = LoadGraph("data/image/gameover.png");
	images[IMAGE_SEC] = LoadGraph("data/image/sec.png");
	images[IMAGE_PTS] = LoadGraph("data/image/pts.png");
	images[IMAGE_CREDIT] = LoadGraph("data/image/credit.png");
	images[IMAGE_LEVEL] = LoadGraph("data/image/level.png");
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

