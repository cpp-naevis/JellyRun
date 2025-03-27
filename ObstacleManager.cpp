#include "pch.h"
#include "ObstacleManager.h"
#include "resource.h"  // IDB_OBSTACLE 정의 필요

CObstacleManager::~CObstacleManager()
{
    for (auto ob : obstacles)
        delete ob;
}

void CObstacleManager::Update()
{
    spawnCounter++;

    if (spawnCounter > 60)  // 주기적으로 생성
    {
        SpawnObstacle();
        spawnCounter = 0;
    }

    for (auto it = obstacles.begin(); it != obstacles.end(); )
    {
        (*it)->Update();
        if ((*it)->pos.x < -50)  // 왼쪽 끝 나가면 제거
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
    int y = 400;  // 바닥 위 위치
    obstacles.push_back(new CObstacle(880, y, 6, IDB_OBSTACLE));  // 오른쪽 끝에서 시작
}

bool CObstacleManager::CheckCollision(const CRect& targetRect)
{
    for (auto ob : obstacles)
    {
        if (ob->GetRect().IntersectRect(&targetRect, &ob->GetRect()))
            return true;  // 충돌!
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