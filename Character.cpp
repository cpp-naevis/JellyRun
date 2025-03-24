#include "pch.h"
#include "Character.h"

CCharacter::CCharacter()
{
    m_x = 100;     // 초기 X 좌표
    m_y = 250;     // 초기 Y 좌표 (땅 위)
    m_jumpSpeed = 0; // 점프 속도
    m_jumpHeight = 35; // 최대 점프 높이
    m_gravity = 1; // 중력 값
    m_isJumping = false;
    m_isFalling = false;
}

CCharacter::~CCharacter()
{
}

void CCharacter::Load(UINT bmpID)
{
    bmp.LoadBitmap(bmpID);
}

// 마우스 클릭 시 점프
void CCharacter::Jump()
{
    if (!m_isJumping && m_y >= 250)
    {
        m_isJumping = true;
        m_jumpSpeed = -15; // 위로 뛰는 속도 설정(음수)
    }
}

// 중력 적용
void CCharacter::ApplyGravity()
{
    if (m_isJumping)
    {
        m_y += m_jumpSpeed;  // 점프 방향으로 이동
        m_jumpSpeed += m_gravity;    // 중력 효과 (속도 감소)

        if (m_y >= 250)  // 땅에 닿으면 점프 종료
        {
            m_y = 250;
            m_isJumping = false;
            m_jumpSpeed = 0;
        }
    }
}

void CCharacter::Draw(CDC* pDC)
{
    if (bmp.m_hObject == NULL) return;

    CDC memDC;
    memDC.CreateCompatibleDC(pDC);
    CBitmap* pOldBmp = memDC.SelectObject(&bmp);

    BITMAP bmpInfo;
    bmp.GetBitmap(&bmpInfo);

    pDC->TransparentBlt(m_x, m_y, bmpInfo.bmWidth, bmpInfo.bmHeight,
        &memDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, RGB(255, 255, 255)); // 마젠타 투명처리

    memDC.SelectObject(pOldBmp);
}

CRect CCharacter::GetRect()
{
    BITMAP bmpInfo;
    bmp.GetBitmap(&bmpInfo);

    int padding = 30;  // ← 여유 공간을 줄 값
    return CRect(
        m_x + padding*2,
        m_y + padding*1.5,
        m_x + bmpInfo.bmWidth - padding*2,
        m_y + bmpInfo.bmHeight - padding*1.5
    );
}