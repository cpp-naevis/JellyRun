#include "pch.h"
#include "CoinManager.h"
#include "resource.h"  // IDB_OBSTACLE ���� �ʿ�

CCoinManager::~CCoinManager()
{
    for (auto ob : obstacles)
        delete ob;
}

void CCoinManager::Update()
{
    spawnCounter++;

    if (spawnCounter > 50)  // �ֱ������� ����
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

void CCoinManager::Draw(CDC* pDC)
{
    for (auto ob : obstacles)
        ob->Draw(pDC);
}

void CCoinManager::SpawnObstacle()
{
    int y = 400;  // �ٴ� �� ��ġ
    obstacles.push_back(new CCoin(800, y, 6, IDB_COIN));  // ������ ������ ����
}

bool CCoinManager::CheckCollision(const CRect& targetRect)
{
    for (auto ob : obstacles)
    {
        if (ob->GetRect().IntersectRect(&targetRect, &ob->GetRect()))
            return true;  // �浹!
    }
    return false;
}