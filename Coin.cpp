#include "pch.h"
#include "Coin.h"

CCoin::CCoin(int x, int y, int s, UINT bmpID)
{
    pos = CPoint(x, y);
    speed = s;
    bmp.LoadBitmap(bmpID);
}

CCoin::~CCoin()
{
}

void CCoin::Update()
{
    pos.x -= speed;
}

void CCoin::Draw(CDC* pDC)
{
    if (bmp.m_hObject == NULL) return;

    CDC memDC;
    memDC.CreateCompatibleDC(pDC);
    CBitmap* pOldBmp = memDC.SelectObject(&bmp);

    BITMAP bmpInfo;
    bmp.GetBitmap(&bmpInfo);

    pDC->TransparentBlt(pos.x, pos.y, bmpInfo.bmWidth, bmpInfo.bmHeight,
        &memDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, RGB(255, 255, 255)); // ����Ÿ ����ó��
}

CRect CCoin::GetRect()
{
    BITMAP bmpInfo;
    bmp.GetBitmap(&bmpInfo);

    int padding = 10;  // ��ֹ��� ���ݸ� �ٿ��� ���
    return CRect(
        pos.x + padding,
        pos.y + padding,
        pos.x + bmpInfo.bmWidth - padding,
        pos.y + bmpInfo.bmHeight - padding
    );
}