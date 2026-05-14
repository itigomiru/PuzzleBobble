#include "EffectManager.h"

void EffectManager::Update() {
    for (auto it = effects.begin(); it != effects.end();) {
        (*it)->Update();
        
        if ((*it)->IsDead()) {
            it = effects.erase(it); // 寿命が来たらリストから削除
        } else {
            ++it;
        }
    }
}

void EffectManager::Render() {
    for (const auto& effect : effects) {
        effect->Render();
    }
}

void EffectManager::AddPopEffect(float x, float y, int colorType) {
    effects.push_back(std::make_unique<PopEffect>(x, y, colorType));
}

void EffectManager::AddDropBubbleEffect(float x, float y, int colorType) {
    effects.push_back(std::make_unique<DropBubbleEffect>(x, y, colorType));
}

void EffectManager::AddDropMonsterEffect(float x, float y, int monsterType) {
    effects.push_back(std::make_unique<DropMonsterEffect>(x, y, monsterType));
}

void EffectManager::ClearAll() {
    effects.clear();
}
