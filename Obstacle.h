#pragma once
#include <afxwin.h>

class CObstacle
{
public:
    CPoint pos;       // ��ֹ� ��ġ
    int speed;        // �̵� �ӵ�
    CBitmap bmp;      // ��ֹ� �̹���
    CRect GetRect(); // �浹 �Լ�

    CObstacle(int x, int y, int s, UINT bmpID);
    ~CObstacle();

    void Update();
    void Draw(CDC* pDC);
    
};
