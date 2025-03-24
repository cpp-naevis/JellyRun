#pragma once
#include <afxwin.h>

class CBackground
{
private:
    CBitmap m_Background;       // ��� �̹���
    int m_BackgroundX;          // ����� ���� X ��ġ
    const int BACKGROUND_SPEED = 5;

public:
    CBackground();
    ~CBackground();

    void LoadBackground(UINT resourceID);
    void Update();
    void Draw(CDC* pDC);
};
