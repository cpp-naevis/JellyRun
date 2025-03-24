#include "pch.h"
#include "Background.h"

CBackground::CBackground()
{
    m_BackgroundX = 0;
}

CBackground::~CBackground()
{
}

void CBackground::LoadBackground(UINT resourceID)
{
    m_Background.LoadBitmap(resourceID);
}

void CBackground::Update()
{
    m_BackgroundX -= BACKGROUND_SPEED;

    if (m_BackgroundX <= -800)  // 배경 너비 기준
        m_BackgroundX = 0;
}

void CBackground::Draw(CDC* pDC)
{
    if (m_Background.m_hObject == NULL)  // 비트맵이 유효한지 체크
    {
        AfxMessageBox(_T("비트맵 핸들이 NULL입니다!"));
        return;
    }

    CBitmap* pOldBitmap;
    CDC memDC;
    memDC.CreateCompatibleDC(pDC);

    pOldBitmap = memDC.SelectObject(&m_Background);

    // 배경 2개를 이어붙여 스크롤 효과
    pDC->BitBlt(m_BackgroundX, 0, 800, 600, &memDC, 0, 0, SRCCOPY);
    pDC->BitBlt(m_BackgroundX + 800, 0, 800, 600, &memDC, 0, 0, SRCCOPY);

    memDC.SelectObject(pOldBitmap);
}
