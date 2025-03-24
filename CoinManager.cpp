#include "pch.h"
#include "CoinManager.h"
#include "resource.h"  // IDB_OBSTACLE 정의 필요

CCoinManager::~CCoinManager()
{
    for (auto ob : obstacles)
        delete ob;
}

void CCoinManager::Update()
{
    spawnCounter++;

    if (spawnCounter > 50)  // 주기적으로 생성
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

void CCoinManager::Draw(CDC* pDC)
{
    for (auto ob : obstacles)
        ob->Draw(pDC);
}

void CCoinManager::SpawnObstacle()
{
    int y = 400;  // 바닥 위 위치
    obstacles.push_back(new CCoin(800, y, 6, IDB_COIN));  // 오른쪽 끝에서 시작
}

bool CCoinManager::CheckCollision(const CRect& targetRect)
{
    for (auto ob : obstacles)
    {
        if (ob->GetRect().IntersectRect(&targetRect, &ob->GetRect()))
            return true;  // 충돌!
    }
    return false;
}