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
    // TODO: colorTypeに応じた落ちるバブルの画像IDを指定する
    int imageId = 0; // 例: IMAGE_BUBBLE_RED 等
    effects.push_back(std::make_unique<DropEffect>(x, y, imageId));
}

void EffectManager::AddDropMonsterEffect(float x, float y, int monsterType) {
    // TODO: monsterTypeに応じたモンスターの画像IDを指定する
    int imageId = 0; // 例: IMAGE_MONSTER_A 等
    effects.push_back(std::make_unique<DropEffect>(x, y, imageId));
}

void EffectManager::ClearAll() {
    effects.clear();
}
