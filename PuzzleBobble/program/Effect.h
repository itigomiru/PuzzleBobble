#pragma once
#include "DxLib.h"
#include "ImageManager.h"
#include "SceneManager.h"
#include "GlidManager.h"
#include "Random.h"



// =========================
// Effect Base
// =========================

class Effect {
protected:
	float x, y;
	bool isDead;
	int state;

public:
	Effect(float x, float y)
		: x(x), y(y), isDead(false), state(0) {
	}

	Effect(float x, float y, int state)
		: x(x), y(y), isDead(false), state(state) {
	}

	virtual ~Effect() {}

	virtual void Update() = 0;
	virtual void Render() = 0;

	bool IsDead() const { return isDead; }
};

// =========================
// PopEffect
// =========================

class PopEffect : public Effect {
private:
	int animCounter;

public:
	PopEffect(float x, float y, int colorType)
		: Effect(x, y, colorType), animCounter(0) {
	}

	void Update() override
	{
		animCounter++;

		if (animCounter >= 20) {
			isDead = true;
		}
	}

	void Render() override
	{
		int frame = animCounter / 4;

		DrawRectRotaGraph(x, y, frame * 32, 0, 32, 32, 2.0f, 0, ImageManager::GetInstance().GetImage(ImageManager::GetInstance().GetPopImage(state)), true);
	}
};

// =========================
// DropMonsterEffect
// =========================

class DropMonsterEffect : public Effect {
private:
	float vy;
	float vx;
	float gravity;
	int animCounter;

public:
	DropMonsterEffect(float x, float y, int colorType)
		: Effect(x, y, colorType),
		vy(-5.0f),
		vx(GetRandomF(-2.0f, 2.0f)),
		gravity(0.5f),
		animCounter(0) {
	}

	void Update() override
	{
		vy += gravity;

		x += vx;
		y += vy;

		animCounter++;

		if (animCounter >= 20) {
			animCounter = 0;
		}

		if (y > SCREEN_H) {
			isDead = true;
		}
	}

	void Render() override
	{
		int frame = animCounter / 5;

		DrawRectRotaGraph(x, y, frame * 16, 0, 16, 16, 2.0f, 0, ImageManager::GetInstance().GetImage(ImageManager::GetInstance().GetMonsterImage(state)), true);
	}
};

// =========================
// DropBubbleEffect
// =========================

class DropBubbleEffect : public Effect {
private:
	float vy;
	float gravity;

public:
	DropBubbleEffect(float x, float y, int colorType)
		: Effect(x, y, colorType),
		vy(-2.0f),
		gravity(0.5f) {
	}

	void Update() override
	{
		vy += gravity;
		y += vy;

		if (y > SCREEN_H) {
			isDead = true;
		}
	}

	void Render() override
	{
		DrawRectRotaGraph(x, y, 0, 0, 16, 16, 2.0f, 0, ImageManager::GetInstance().GetImage(ImageManager::GetInstance().GetBubbleImage(state)), true);
	}
};