#pragma once
#include <afxwin.h>

class CCoin
{
public:
    CPoint pos;       // ��ֹ� ��ġ
    int speed;        // �̵� �ӵ�
    CBitmap bmp;      // ��ֹ� �̹���
    CRect GetRect(); // �浹 �Լ�

    CCoin(int x, int y, int s, UINT bmpID);
    ~CCoin();

    void Update();
    void Draw(CDC* pDC);
    
};
