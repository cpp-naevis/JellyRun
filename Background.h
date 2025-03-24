#pragma once
#include <afxwin.h>

class CBackground
{
private:
    CBitmap m_Background;       // 배경 이미지
    int m_BackgroundX;          // 배경의 현재 X 위치
    const int BACKGROUND_SPEED = 5;

public:
    CBackground();
    ~CBackground();

    void LoadBackground(UINT resourceID);
    void Update();
    void Draw(CDC* pDC);
};
