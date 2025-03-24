#include "pch.h"
#include "JellyScore.h"

CJellyScore::CJellyScore(int x, int y, int s, UINT bmpID)
{
    pos = CPoint(x, y);
    speed = s;
    collected = false;
    bmp.LoadBitmap(bmpID);
}

CJellyScore::~CJellyScore() {}

void CJellyScore::Update()
{
    pos.x -= speed;
}

void CJellyScore::Draw(CDC* pDC)
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

CRect CJellyScore::GetRect()
{
    BITMAP bmpInfo;
    bmp.GetBitmap(&bmpInfo);
    return CRect(pos.x, pos.y, pos.x + bmpInfo.bmWidth, pos.y + bmpInfo.bmHeight);
}