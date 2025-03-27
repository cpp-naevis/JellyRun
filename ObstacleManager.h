#pragma once
#include <vector>
#include "Obstacle.h"

class CObstacleManager
{
private:
    std::vector<CObstacle*> obstacles;
    int spawnCounter = 0;
    int spawnRate; // �⺻ ���� ���� (������ �� ����)

public:
    ~CObstacleManager();
    void Update();
    void Draw(CDC* pDC);
    void SpawnObstacle();
    void ClearObstacles();
    void SetDifficulty(int level);  // ���̵� ���� �Լ�
    bool CheckCollision(const CRect& targetRect);
    std::vector<CObstacle*>& GetObstacleList();
};

