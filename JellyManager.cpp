#include "pch.h"
#include "JellyManager.h"
#include "resource.h"

CJellyManager::~CJellyManager()
{
    for (auto j : jellies)
        delete j;
}

void CJellyManager::Update()
{
    spawnCounter++;

    if (spawnCounter > 80)  // 일정 간격으로 젤리 생성
    {
        SpawnJelly();
        spawnCounter = 0;
    }

    for (auto it = jellies.begin(); it != jellies.end(); )
    {
        (*it)->Update();
        if ((*it)->pos.x < -50 || (*it)->collected)
        {
            delete* it;
            it = jellies.erase(it);
        }
        else ++it;
    }
}

void CJellyManager::Draw(CDC* pDC)
{
    for (auto j : jellies)
        j->Draw(pDC);
}

void CJellyManager::SpawnJelly()
{
    int y = 300 + rand() % 100;  // 점프해서 먹을 수 있는 위치
    jellies.push_back(new CJellyScore(800, y, 5, IDB_EAT));
}

void CJellyManager::CheckCollect(const CRect& playerRect, int& score)
{
    for (auto j : jellies)
    {
        if (!j->collected && j->GetRect().IntersectRect(&playerRect, &j->GetRect()))
        {
            j->collected = true;
            score += 1;
        }
    }
}

void CJellyManager::SpawnJellyLine(int count, int spacing, int y)
{
    int startX = 800;  // 오른쪽 끝에서 시작

    for (int i = 0; i < count; ++i)
    {
        int x = startX + i * spacing;
        jellies.push_back(new CJellyScore(x, y, 5, IDB_EAT));
    }
}