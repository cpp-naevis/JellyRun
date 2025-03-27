#pragma once
#include <vector>
#include "Obstacle.h"

class CObstacleManager
{
private:
    std::vector<CObstacle*> obstacles;
    int spawnCounter = 0;
    int spawnRate; // 기본 생성 간격 (프레임 수 기준)

public:
    ~CObstacleManager();
    void Update();
    void Draw(CDC* pDC);
    void SpawnObstacle();
    void ClearObstacles();
    void SetDifficulty(int level);  // 난이도 설정 함수
    bool CheckCollision(const CRect& targetRect);
    std::vector<CObstacle*>& GetObstacleList();
};

