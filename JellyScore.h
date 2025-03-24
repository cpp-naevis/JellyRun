#pragma once
#include <afxwin.h>

class CJellyScore
{
public:
    CPoint pos;
    int speed;
    bool collected;
    CBitmap bmp;

    CJellyScore(int x, int y, int s, UINT bmpID);
    ~CJellyScore();

    void Update();
    void Draw(CDC* pDC);
    CRect GetRect();
};
