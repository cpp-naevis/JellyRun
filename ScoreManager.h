#pragma once
#include <vector>
#include "Score.h"
#include "Obstacle.h"

class CScoreManager
{
private:
    std::vector<CScore*> jellies;
    
    int spawnCounter = 0;

public:
    float m_WavePhase = 0.0f;  // �������� ���� ���� ��ġ (���൵)

    ~CScoreManager();
    void Update(bool allowSpawn = true);
    void Draw(CDC* pDC);
    void SpawnJelly();
    void CheckCollect(const CRect& playerRect, int& score);  // �浹 üũ + ���� �ݿ�
    void SpawnJellyLine(int count, int spacing, int y, const std::vector<CObstacle*>& obstacles);
    void SpawnJellyWaveLine(int count, int spacing, int baseY, int amplitude, float wavelength, const std::vector<CObstacle*>& obstacles);
    std::vector<CObstacle*> obstaclesRef;
    void SetObstacleReference(const std::vector<CObstacle*>& ref);
    std::vector<CScore*>& GetJellyList();
    void CreateJellyPathTo(CPoint flagPos);
    void Clear();
};
