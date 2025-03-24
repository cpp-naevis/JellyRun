#pragma once
#include <vector>
#include "Coin.h"

class CCoinManager
{
private:
    std::vector<CCoin*> obstacles;
    int spawnCounter = 0;

public:
    ~CCoinManager();
    void Update();
    void Draw(CDC* pDC);
    void SpawnObstacle();
    bool CheckCollision(const CRect& targetRect);
};

