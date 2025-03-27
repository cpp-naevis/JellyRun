#include "pch.h"
#include "Obstacle.h"

CObstacle::CObstacle(int x, int y, int s, UINT bmpID)
{
    pos = CPoint(x, y);
    speed = 6;
    bmp.LoadBitmap(bmpID);
}

CObstacle::~CObstacle()
{
}

void CObstacle::Update()
{
    pos.x -= speed;
}

void CObstacle::Draw(CDC* pDC)
{
    if (bmp.m_hObject == NULL) return;

    CDC memDC;
    memDC.CreateCompatibleDC(pDC);
    CBitmap* pOldBmp = memDC.SelectObject(&bmp);

    BITMAP bmpInfo;
    bmp.GetBitmap(&bmpInfo);

    pDC->TransparentBlt(pos.x, pos.y, bmpInfo.bmWidth, bmpInfo.bmHeight,
        &memDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, RGB(255, 255, 255)); // 배경 투명처리
}

CRect CObstacle::GetRect()
{
    BITMAP bmpInfo;
    bmp.GetBitmap(&bmpInfo);

    int padding = 15;  // 장애물은 조금만 줄여도 충분
    return CRect(
        pos.x + padding,
        pos.y + padding*0.7,
        pos.x + bmpInfo.bmWidth - padding,
        pos.y + bmpInfo.bmHeight - padding*0.7
    );
}