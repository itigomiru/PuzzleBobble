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
// PopScoreEffect
// =========================

class PopScoreEffect : public Effect {
private:
	int animCounter;
	static constexpr int LIFE_TIME = 60;
	static constexpr float MOVE_SPEED = 1.0f;
	static constexpr float TEXT_SCALE = 1.0f;
	static constexpr float START_Y_OFFSET = 16.0f;

public:
	PopScoreEffect(float x, float y, int score)
		: Effect(x, y - START_Y_OFFSET, score), animCounter(0) {
	}

	void Update() override
	{
		y -= MOVE_SPEED;
		animCounter++;

		if (animCounter >= LIFE_TIME) {
			isDead = true;
		}
	}

	void Render() override
	{
		int value = state;
		if (value < 0) {
			value = 0;
		}

		int digits[10];
		int digitCount = 0;
		do {
			digits[digitCount++] = value % 10;
			value /= 10;
		} while (value > 0 && digitCount < 10);

		for (int i = digitCount - 1; i >= 0; --i) {
			int drawX = x + ((digitCount - 1 - i) * 10.0f);
			DrawRectRotaGraph(drawX, y, digits[i] * 16, 0, 16, 16, TEXT_SCALE, 0, ImageManager::GetInstance().GetImage(IMAGE_NUMBER), true);
		}
	}
};

// =========================
// DropScoreEffect
// =========================

class DropScoreEffect : public Effect {
private:
	int animCounter;
	static constexpr int APPROACH_FRAMES = 18;
	static constexpr int STOP_FRAMES = 30;
	static constexpr int TOTAL_FRAMES = 90;
	static constexpr float START_X = 0.0f;
	static constexpr float START_Y = 25.0f;
	static constexpr float TARGET_X = SCREEN_W * 0.5f;
	static constexpr float TARGET_Y = 25;
	static constexpr float ARC_HEIGHT = 32.0f;
	static constexpr float EXIT_SPEED = 1.0f;
	static constexpr float TEXT_SCALE = 2.0f;
	static constexpr int DIGIT_WIDTH = 16;
	static constexpr int DIGIT_SPACING = 28;

public:
	DropScoreEffect(int score)
		: Effect(START_X, START_Y, score), animCounter(0) {
	}

	void Update() override
	{
		animCounter++;

		if (animCounter <= APPROACH_FRAMES) {
			float t = static_cast<float>(animCounter) / APPROACH_FRAMES;
			float invT = 1.0f - t;
			x = START_X + (TARGET_X - START_X) * t;
			y = START_Y + (TARGET_Y - START_Y) * t + (ARC_HEIGHT * t * invT);
		}
		else if (animCounter <= APPROACH_FRAMES + STOP_FRAMES) {
			x = TARGET_X;
			y = TARGET_Y;
		}
		else {
			y -= EXIT_SPEED;
		}

		if (animCounter >= TOTAL_FRAMES) {
			isDead = true;
		}
	}

	void Render() override
	{
		int value = state;
		if (value < 0) {
			value = 0;
		}

		int digits[10];
		int digitCount = 0;
		do {
			digits[digitCount++] = value % 10;
			value /= 10;
		} while (value > 0 && digitCount < 10);

		int digitTotalWidth = (digitCount - 1) * DIGIT_SPACING;
		int startX = static_cast<int>(x) - (digitTotalWidth / 2);
		int renderY = static_cast<int>(y);
		bool invert = (animCounter > APPROACH_FRAMES + STOP_FRAMES) && ((animCounter / 3) % 2 == 0);
		int imageHandle = invert ? IMAGE_NUMBER_REVERSE : IMAGE_NUMBER;

		for (int i = digitCount - 1; i >= 0; --i) {
			int index = digitCount - 1 - i;
			int drawX = startX + (index * DIGIT_SPACING);
			DrawRectRotaGraph(drawX, renderY, digits[i] * DIGIT_WIDTH, 0, DIGIT_WIDTH, 16, TEXT_SCALE, 0, ImageManager::GetInstance().GetImage(imageHandle), true);
		}
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