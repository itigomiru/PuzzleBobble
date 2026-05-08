#pragma once
#include "BallController.h"

struct GlidCell
{
    bool isEmpty = true;
    int color = 0;
};

class GlidManager
{
private:
    static constexpr int ROWS = 12;
    static constexpr int COLS = 8;
    GlidCell glid[ROWS][COLS];

    GlidManager(); 
    ~GlidManager();
    GlidManager(const GlidManager&) = delete;
    GlidManager& operator=(const GlidManager&) = delete;

    void GetCellCenter(int row, int col, float& cx, float& cy);
public:
    static GlidManager& GetInstance();

    void Render();
    void AddGlid(BallController* ball, int row, int col);

    
    bool CheckCircleCollision(float ballX, float ballY, float ballR);
};