#pragma once
#include <afxwin.h>

class CScore
{
public:
    CPoint pos;
    int speed;
    bool collected;
    bool isRainbow;
    CBitmap bmp;

    CScore(int x, int y, int s, UINT bmpID, bool rainbow = false);
    ~CScore();

    void Update();
    void Draw(CDC* pDC);
    CRect GetRect();
};
