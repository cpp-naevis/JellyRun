#pragma once
#include <afxwin.h>

class CCoin
{
public:
    CPoint pos;       // 장애물 위치
    int speed;        // 이동 속도
    CBitmap bmp;      // 장애물 이미지
    CRect GetRect(); // 충돌 함수

    CCoin(int x, int y, int s, UINT bmpID);
    ~CCoin();

    void Update();
    void Draw(CDC* pDC);
    
};
