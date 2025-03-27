#include "pch.h"
#include "ScoreManager.h"
#include "resource.h"
#include <cmath>  // sinf 사용을 위해 필요

CScoreManager::~CScoreManager()
{
    for (auto j : jellies)
        delete j;
}

void CScoreManager::Update(bool allowSpawn)
{
    if (allowSpawn)
    {
        spawnCounter++;

        if (spawnCounter > 70)
        {
            SpawnJellyWaveLine(10, 40, 300, 60, 4.0f, obstaclesRef);
            spawnCounter = 0;
        }
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


void CScoreManager::Draw(CDC* pDC)
{
    for (auto j : jellies)
        j->Draw(pDC);
}

void CScoreManager::SpawnJelly()
{
    int y = 300 + rand() % 100;  // 점프해서 먹을 수 있는 위치
    jellies.push_back(new CScore(800, y, 5, IDB_EAT));
}

void CScoreManager::CheckCollect(const CRect& playerRect, int& score)
{
    for (auto j : jellies)
    {
        if (!j->collected && j->GetRect().IntersectRect(&playerRect, &j->GetRect()))
        {
            j->collected = true;
            if (j->isRainbow)
                score += 10;  //  무지개 젤리는 +10점
            else
                score += 1;
        }

    }
}

void CScoreManager::SpawnJellyLine(int count, int spacing, int baseY, const std::vector<CObstacle*>& obstacles)
{
    int startX = 800;

    for (int i = 0; i < count; ++i)
    {
        int x = startX + i * spacing;
        int y = baseY;

        //  장애물과 겹치는지 검사
        for (auto ob : obstacles)
        {
            CRect jellyRect(x, y, x + 32, y + 32);         // 가상의 젤리 영역 (크기는 이미지 크기에 맞게)
            CRect obRect = ob->GetRect();

            if (jellyRect.IntersectRect(&jellyRect, &obRect))
            {
                y = obRect.top - 40;

                // 여기서도 한 번 더 확인
                if (y < 100) continue;  // 너무 위쪽이면 생략
            }
        }

        jellies.push_back(new CScore(x, y, 5, IDB_EAT));
    }
}

void CScoreManager::SpawnJellyWaveLine(int count, int spacing, int baseY, int amplitude, float wavelength, const std::vector<CObstacle*>& obstacles)
{
    int startX = 800;

    for (int i = 0; i < count; ++i)
    {
        int x = startX + i * spacing;

        // 이전 위치에서부터 이어지는 사인파 각도
        float angle = m_WavePhase + (float)i / wavelength;

        int y = baseY - static_cast<int>(amplitude * sinf(angle * 3.14159f));  // 사인파

        // 장애물과 겹치는지 검사
        bool overlapped = false;
        for (auto ob : obstacles)
        {
            CRect jellyRect(x, y, x + 32, y + 32);
            CRect obRect = ob->GetRect();

            if (jellyRect.IntersectRect(&jellyRect, &obRect))
            {
                overlapped = true;
                break;
            }
        }

        if (!overlapped)
        {
            jellies.push_back(new CScore(x, y, 5, IDB_EAT)); 

            bool isRainbow = (rand() % 10 == 0);  // 10% 확률로 무지개 젤리

            UINT jellyBmpID = isRainbow ? IDB_RAINBOW_JELLY : IDB_EAT;

            jellies.push_back(new CScore(x, y, 5, jellyBmpID, isRainbow));
        }
    }

    // wave 진행도 업데이트 (끊기지 않도록)
    m_WavePhase += (float)count / wavelength;
}

void CScoreManager::CreateJellyPathTo(CPoint flagPos)
{
    for (auto j : jellies)
        delete j;
    jellies.clear();

    int endX = flagPos.x;
    int interval = 60;

    // 깃발까지 10개 정도 젤리 만들기 (조절 가능)
    int count = 10;
    int y = flagPos.y + 50;  // 깃발보다 살짝 아래로

    for (int i = 0; i < count; ++i)
    {
        int x = endX - (count - i) * interval;
        if (x < 0) break;
        jellies.push_back(new CScore(x, y, 5, IDB_EAT));
    }
}

void CScoreManager::Clear()
{
    for (auto j : jellies)
        delete j;
    jellies.clear();
}

std::vector<CScore*>& CScoreManager::GetJellyList()
{
    return jellies;
}

void CScoreManager::SetObstacleReference(const std::vector<CObstacle*>& ref)
{
    obstaclesRef = ref;
}