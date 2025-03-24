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

    if (m_BackgroundX <= -800)  // ��� �ʺ� ����
        m_BackgroundX = 0;
}

void CBackground::Draw(CDC* pDC)
{
    if (m_Background.m_hObject == NULL)  // ��Ʈ���� ��ȿ���� üũ
    {
        AfxMessageBox(_T("��Ʈ�� �ڵ��� NULL�Դϴ�!"));
        return;
    }

    CBitmap* pOldBitmap;
    CDC memDC;
    memDC.CreateCompatibleDC(pDC);

    pOldBitmap = memDC.SelectObject(&m_Background);

    // ��� 2���� �̾�ٿ� ��ũ�� ȿ��
    pDC->BitBlt(m_BackgroundX, 0, 800, 600, &memDC, 0, 0, SRCCOPY);
    pDC->BitBlt(m_BackgroundX + 800, 0, 800, 600, &memDC, 0, 0, SRCCOPY);

    memDC.SelectObject(pOldBitmap);
}
