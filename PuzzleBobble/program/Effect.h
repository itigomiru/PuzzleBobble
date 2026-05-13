#pragma once
#include "DxLib.h"
#include "ImageManager.h"

class Effect {
protected:
    float x, y;
    bool isDead;

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
    }

    void Update() override {
        animCounter++;
        if (animCounter >= 20) {
            isDead = true;
        }
    }

    void Render() override {
        // int frame = animCounter / 5;
        // DrawRotaGraph(x, y, 1.0, 0, ImageManager::GetInstance().GetImage(IMAGE_BUBBLE_POP), true);
    }
};

class DropEffect : public Effect {
private:
    float vy;
    float gravity;
    int imageId;
    float rot;

public:
    DropEffect(float x, float y, int imageId)
        : Effect(x, y), vy(-2.0f), gravity(0.5f), imageId(imageId), rot(0.0f) {
    }

    void Update() override {
        vy += gravity;
        y += vy;
        rot += 0.1f;

        if (y > 600.0f) {
            isDead = true;
        }
    }

    void Render() override {
        // DrawRotaGraph(x, y, 1.0, rot, ImageManager::GetInstance().GetImage(imageId), true);
    }
};
