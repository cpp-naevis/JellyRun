#include "pch.h"
#include "ObstacleManager.h"
#include "resource.h"  // IDB_OBSTACLE ���� �ʿ�

CObstacleManager::~CObstacleManager()
{
    for (auto ob : obstacles)
        delete ob;
}

void CObstacleManager::Update()
{
    spawnCounter++;

    if (spawnCounter > 60)  // �ֱ������� ����
    {
        SpawnObstacle();
        spawnCounter = 0;
    }

    for (auto it = obstacles.begin(); it != obstacles.end(); )
    {
        (*it)->Update();
        if ((*it)->pos.x < -50)  // ���� �� ������ ����
        {
            delete* it;
            it = obstacles.erase(it);
        }
        else ++it;
    }
}

void CObstacleManager::Draw(CDC* pDC)
{
    for (auto ob : obstacles)
        ob->Draw(pDC);
}

void CObstacleManager::SpawnObstacle()
{
    int y = 400;  // �ٴ� �� ��ġ
    obstacles.push_back(new CObstacle(880, y, 6, IDB_OBSTACLE));  // ������ ������ ����
}

bool CObstacleManager::CheckCollision(const CRect& targetRect)
{
    for (auto ob : obstacles)
    {
        if (ob->GetRect().IntersectRect(&targetRect, &ob->GetRect()))
            return true;  // �浹!
    }
    return false;
}

void CObstacleManager::SetDifficulty(int level)
{
    switch (level)
    {
    case 1: spawnRate = 70; break;
    case 2: spawnRate = 50; break;
    case 3: spawnRate = 30; break;
    default: spawnRate = 70; break;
    }
}

void CObstacleManager::ClearObstacles()
{
    obstacles.clear();
}

std::vector<CObstacle*>& CObstacleManager::GetObstacleList()
{
    return obstacles;
}