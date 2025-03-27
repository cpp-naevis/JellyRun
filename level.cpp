#include "pch.h"
#include "level.h"
#include "resource.h"

CLevel::CLevel()
{
    pos = CPoint(800, 320); // �����ʿ��� ����
    speed = 5;
    appeared = false;
    levelUp = false;
    bmpLoaded = bmp.LoadBitmap(IDB_GOAL_FLAG); // ���ҽ����� ��Ʈ�� �ε�

    // ��Ʈ�� ���� ��������
    BITMAP bmpInfo;
    bmp.GetBitmap(&bmpInfo);
    rect.SetRect(pos.x, pos.y, pos.x + bmpInfo.bmWidth, pos.y + bmpInfo.bmHeight);
}

CLevel::~CLevel()
{
    if (bmpLoaded)
        bmp.DeleteObject();
}

void CLevel::Init()
{
    appeared = false;
    levelUp = false;
    pos = CPoint(800, 320);
    speed = 5;

    // ���� ��Ʈ�� ���� �� �ٽ� �ε�
    if (bmp.m_hObject)
        bmp.DeleteObject();
    bmpLoaded = bmp.LoadBitmap(IDB_GOAL_FLAG);

    BITMAP bmpInfo;
    bmp.GetBitmap(&bmpInfo);
    rect.SetRect(pos.x, pos.y, pos.x + bmpInfo.bmWidth, pos.y + bmpInfo.bmHeight);
}

void CLevel::Update(int elapsedTime)
{
    if (!appeared && elapsedTime >= 15000)
    {
        appeared = true;
    }

    if (appeared && !levelUp)
    {
        pos.x -= speed;

        BITMAP bmpInfo;
        bmp.GetBitmap(&bmpInfo);
        rect.SetRect(pos.x, pos.y, pos.x + bmpInfo.bmWidth, pos.y + bmpInfo.bmHeight);
    }
}

void CLevel::Draw(CDC* pDC)
{
    if (!appeared || levelUp || !bmpLoaded) return;

    CDC memDC;
    memDC.CreateCompatibleDC(pDC);
    CBitmap* pOld = memDC.SelectObject(&bmp);

    BITMAP bmpInfo;
    bmp.GetBitmap(&bmpInfo);

    pDC->TransparentBlt(pos.x, pos.y,
        bmpInfo.bmWidth, bmpInfo.bmHeight,
        &memDC, 0, 0,
        bmpInfo.bmWidth, bmpInfo.bmHeight,
        RGB(255, 255, 255));  // ��� ����

    memDC.SelectObject(pOld);
}

void CLevel::CheckCollision(CRect playerRect)
{
    if (appeared && !levelUp && rect.IntersectRect(rect, playerRect))
    {
        levelUp = true;
    }
}

CPoint CLevel::GetPosition() const
{
    return pos;
}

bool CLevel::IsAppeared() const
{
    return appeared;
}

bool CLevel::IsLevelUp() const
{
    return levelUp;
}
