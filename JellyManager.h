#pragma once
#include <vector>
#include "JellyScore.h"

class CJellyManager
{
private:
    std::vector<CJellyScore*> jellies;
    int spawnCounter = 0;

public:
    ~CJellyManager();
    void Update();
    void Draw(CDC* pDC);
    void SpawnJelly();
    void CheckCollect(const CRect& playerRect, int& score);  // �浹 üũ + ���� �ݿ�
    void SpawnJellyLine(int count = 10, int spacing = 40, int y = 300);
};
