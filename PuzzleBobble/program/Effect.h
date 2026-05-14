#pragma once
#include "DxLib.h"
#include "ImageManager.h"
#include "SceneManager.h"`
#include "GlidManager.h"
#include"Random.h"
class Effect {
protected:
	float x, y;
	bool isDead;
	int state;
public:
	Effect(float x, float y) : x(x), y(y), isDead(false), state(0) {}
	Effect(float x, float y, int state) : x(x), y(y), isDead(false), state(state) {}
	virtual ~Effect() {}
	virtual void Update() = 0;
	virtual void Render() = 0;
	bool IsDead() const { return isDead; }
};

class PopEffect : public Effect {
private:
	int animCounter;

public:
	PopEffect(float x, float y, int colorType)
		: Effect(x, y, colorType), animCounter(0) {
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
			DrawRectRotaGraph(x, y, frame * 32, 0, 32, 32, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_RED_POP), true);
			break;
		case GREEN:
			DrawRectRotaGraph(x, y, frame * 32, 0, 32, 32, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_GREEN_POP), true);
			break;
		case BLUE:
			DrawRectRotaGraph(x, y, frame * 32, 0, 32, 32, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_BLUE_POP), true);
			break;
		case YELLOW:
			DrawRectRotaGraph(x, y, frame * 32, 0, 32, 32, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_YELLOW_POP), true);
			break;
		case PURPLE:
			DrawRectRotaGraph(x, y, frame * 32, 0, 32, 32, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_PURPLE_POP), true);
			break;
		case WHITE:
			DrawRectRotaGraph(x, y, frame * 32, 0, 32, 32, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_WHITE_POP), true);
			break;
		case BLACK:
			DrawRectRotaGraph(x, y, frame * 32, 0, 32, 32, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_BLACK_POP), true);
			break;
		}
	}
};

class DropMonsterEffect : public Effect {
private:
	float vy;
	float vx;
	float gravity;
	int imageId;
	int animCounter;

public:
	DropMonsterEffect(float x, float y, int colorType)
		: Effect(x, y, colorType), vy(-5.0f), vx(GetRandomF(-2.0f, 2.0f)), gravity(0.5f), imageId(0), animCounter(0) {
	}

	void Update() override {
		vy += gravity;
		x += vx;
		y += vy;
		animCounter++;
		if (animCounter >= 20)animCounter = 0;

		if (y > SCREEN_H) {
			isDead = true;
		}
	}

	void Render() override {
		int frame = animCounter / 5;
		switch (state)
		{
		case RED:
			DrawRectRotaGraph(x, y, frame * 16, 0, 16, 16, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_MONSTER_RED), true);
			break;
		case GREEN:
			DrawRectRotaGraph(x, y, frame * 16, 0, 16, 16, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_MONSTER_GREEN), true);
			break;
		case BLUE:
			DrawRectRotaGraph(x, y, frame * 16, 0, 16, 16, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_MONSTER_BLUE), true);
			break;
		case YELLOW:
			DrawRectRotaGraph(x, y, frame * 16, 0, 16, 16, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_MONSTER_YELLOW), true);
			break;
		case PURPLE:
			DrawRectRotaGraph(x, y, frame * 16, 0, 16, 16, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_MONSTER_PURPLE), true);
			break;
		case WHITE:
			DrawRectRotaGraph(x, y, frame * 16, 0, 16, 16, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_MONSTER_WHITE), true);
			break;
		case BLACK:
			DrawRectRotaGraph(x, y, frame * 16, 0, 16, 16, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_MONSTER_BLACK), true);
			break;
		default:
			break;
		}
	}
};
class DropBubbleEffect : public Effect {
private:
	float vy;

	float gravity;
	int imageId;

public:
	DropBubbleEffect(float x, float y, int colorType)
		: Effect(x, y, colorType), vy(-2.0f), gravity(0.5f), imageId(0) {
	}

	void Update() override {
		vy += gravity;
		y += vy;

		if (y > SCREEN_H) {
			isDead = true;
		}
	}

	void Render() override {
		switch (state)
		{
		case RED:
			DrawRectRotaGraph(x, y,  0, 0, 16, 16,2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_RED_IDLE), true);
			break;
		case GREEN:
			DrawRectRotaGraph(x, y,  0, 0, 16, 16, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_GREEN_IDLE), true);
			break;
		case BLUE:
			DrawRectRotaGraph(x, y,  0, 0, 16, 16, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_BLUE_IDLE), true);
			break;
		case YELLOW:
			DrawRectRotaGraph(x, y,  0, 0, 16, 16, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_YELLOW_IDLE), true);
			break;
		case PURPLE:
			DrawRectRotaGraph(x, y,  0, 0, 16, 16, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_PURPLE_IDLE), true);
			break;
		case WHITE:
			DrawRectRotaGraph(x, y,  0, 0, 16, 16, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_WHITE_IDLE), true);
			break;
		case BLACK:
			DrawRectRotaGraph(x, y,  0, 0, 16, 16, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_BLACK_IDLE), true);
			break;
		default:
			break;
		}
	}
};
