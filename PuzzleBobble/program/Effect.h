#pragma once
#include "DxLib.h"
#include "ImageManager.h"
#include "SceneManager.h"`
#include "GlidManager.h"

class Effect {
protected:
	float x, y;
	bool isDead;
	int state;
public:
	Effect(float x, float y) : x(x), y(y), isDead(false) {}
	virtual ~Effect() {}
	virtual void Update() = 0;
	virtual void Render() = 0;
	bool IsDead() const { return isDead; }
};

class PopEffect : public Effect {
private:
	int animCounter;
	int colorType;

public:
	PopEffect(float x, float y, int colorType)
		: Effect(x, y), animCounter(0), colorType(colorType) {
		state = colorType;
	}

	void Update() override {
		animCounter++;
		if (animCounter >= 20) {
			isDead = true;
		}
	}

	void Render() override {
		int frame = animCounter / 4;
		switch (state)
		{
		case RED:
			DrawRectRotaGraph(x, y, frame * 16, 0, 16, 16, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_RED_LUMINUS), true);
			break;
		case GREEN:
			DrawRectRotaGraph(x, y, frame * 16, 0, 16, 16, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_GREEN_LUMINUS), true);
			break;
		case BLUE:
			DrawRectRotaGraph(x, y, frame * 16, 0, 16, 16, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_BLUE_LUMINUS), true);
			break;
		case YELLOW:
			DrawRectRotaGraph(x, y, frame * 16, 0, 16, 16, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_YELLOW_LUMINUS), true);
			break;
		case PURPLE:
			DrawRectRotaGraph(x, y, frame * 16, 0, 16, 16, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_PURPLE_LUMINUS), true);
			break;
		case WHITE:
			DrawRectRotaGraph(x, y, frame * 16, 0, 16, 16, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_WHITE_LUMINUS), true);
			break;
		case BLACK:
			DrawRectRotaGraph(x, y, frame * 16, 0, 16, 16, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_BLACK_LUMINUS), true);
			break;
		}
	}
};

class DropEffect : public Effect {
private:
	float vy;
	float gravity;
	int imageId;

public:
	DropEffect(float x, float y, int imageId)
		: Effect(x, y), vy(-2.0f), gravity(0.5f), imageId(imageId) {
	}

	void Update() override {
		vy += gravity;
		y += vy;

		if (y > SCREEN_H) {
			isDead = true;
		}
	}

	void Render() override {
		// DrawRotaGraph(x, y, 1.0, rot, ImageManager::GetInstance().GetImage(imageId), true);
	}
};
