#include "pch.h"
#include "ScoreManager.h"
#include "resource.h"
#include <cmath>  // sinf ����� ���� �ʿ�

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
    int y = 300 + rand() % 100;  // �����ؼ� ���� �� �ִ� ��ġ
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
                score += 10;  //  ������ ������ +10��
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

        //  ��ֹ��� ��ġ���� �˻�
        for (auto ob : obstacles)
        {
            CRect jellyRect(x, y, x + 32, y + 32);         // ������ ���� ���� (ũ��� �̹��� ũ�⿡ �°�)
            CRect obRect = ob->GetRect();

            if (jellyRect.IntersectRect(&jellyRect, &obRect))
            {
                y = obRect.top - 40;

                // ���⼭�� �� �� �� Ȯ��
                if (y < 100) continue;  // �ʹ� �����̸� ����
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

        // ���� ��ġ�������� �̾����� ������ ����
        float angle = m_WavePhase + (float)i / wavelength;

        int y = baseY - static_cast<int>(amplitude * sinf(angle * 3.14159f));  // ������

        // ��ֹ��� ��ġ���� �˻�
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

            bool isRainbow = (rand() % 10 == 0);  // 10% Ȯ���� ������ ����

            UINT jellyBmpID = isRainbow ? IDB_RAINBOW_JELLY : IDB_EAT;

            jellies.push_back(new CScore(x, y, 5, jellyBmpID, isRainbow));
        }
    }

    // wave ���൵ ������Ʈ (������ �ʵ���)
    m_WavePhase += (float)count / wavelength;
}

void CScoreManager::CreateJellyPathTo(CPoint flagPos)
{
    for (auto j : jellies)
        delete j;
    jellies.clear();

    int endX = flagPos.x;
    int interval = 60;

    // ��߱��� 10�� ���� ���� ����� (���� ����)
    int count = 10;
    int y = flagPos.y + 50;  // ��ߺ��� ��¦ �Ʒ���

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