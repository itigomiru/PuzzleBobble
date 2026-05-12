#include "NextBallController.h"
#include "dxlib.h"
#include "GlidManager.h"

void NextBall::update() {
    // 線形補間（Lerp）などで target に近づける
    x += (targetX - x) * 0.1f;
    y += (targetY - y) * 0.1f;
}

void NextBall::Render() {
    int dxColor = GetColor(255, 255, 255);
    switch (color) {
    case RED: dxColor = GetColor(255, 0, 0); break;
    case GREEN: dxColor = GetColor(0, 255, 0); break;
    case BLUE: dxColor = GetColor(0, 0, 255); break;
    case YELLOW: dxColor = GetColor(255, 255, 0); break;
    case PURPLE: dxColor = GetColor(255, 0, 255); break;
    case WHITE: dxColor = GetColor(255, 255, 255); break;
    case BLACK: dxColor = GetColor(0, 0, 0); break;
    }
    DrawCircle(x, y, 16, dxColor, true);
}
