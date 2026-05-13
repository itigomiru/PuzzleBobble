#pragma once
#include <vector>
#include <memory>
#include "Effect.h"

class EffectManager {
private:
    std::vector<std::unique_ptr<Effect>> effects;

    // シングルトン化 (ImageManager等に合わせる)
    EffectManager() {}
    ~EffectManager() {}

public:
    // コピー禁止
    EffectManager(const EffectManager&) = delete;
    EffectManager& operator=(const EffectManager&) = delete;

    static EffectManager& GetInstance() {
        static EffectManager instance;
        return instance;
    }

    void Update();
    void Render();

    // エフェクトの登録関数
    void AddPopEffect(float x, float y, int colorType);
    void AddDropBubbleEffect(float x, float y, int colorType);
    void AddDropMonsterEffect(float x, float y, int monsterType);
    
    // リセット用
    void ClearAll(); 
};