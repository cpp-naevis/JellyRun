#include "pch.h"
#include "Score.h"

CScore::CScore(int x, int y, int s, UINT bmpID, bool rainbow)
{
    pos = CPoint(x, y);
    speed = 6;
    collected = false;
    isRainbow = rainbow;
    bmp.LoadBitmap(bmpID);
}

CScore::~CScore() {}

void CScore::Update()
{
    pos.x -= speed;
}

void CScore::Draw(CDC* pDC)
{
    if (collected || bmp.m_hObject == NULL) return;

    CDC memDC;
    memDC.CreateCompatibleDC(pDC);
    CBitmap* pOld = memDC.SelectObject(&bmp);

    BITMAP bmpInfo;
    bmp.GetBitmap(&bmpInfo);

    pDC->TransparentBlt(pos.x, pos.y, bmpInfo.bmWidth, bmpInfo.bmHeight,
        &memDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, RGB(255, 255, 255));

    memDC.SelectObject(pOld);
}

CRect CScore::GetRect()
{
    BITMAP bmpInfo;
    bmp.GetBitmap(&bmpInfo);
    return CRect(pos.x, pos.y, pos.x + bmpInfo.bmWidth, pos.y + bmpInfo.bmHeight);
}