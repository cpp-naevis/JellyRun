#include "pch.h"
#include "Character.h"

CCharacter::CCharacter()
{
    m_x = 100;     // 초기 X 좌표
    m_y = 320;     // 초기 Y 좌표 (땅 위)
    m_jumpSpeed = 20; // 점프 속도
    m_jumpHeight = 0; // 최대 점프 높이
    m_gravity = 1; // 중력 값
    m_isJumping = false;
    m_isFalling = false;
}

CCharacter::~CCharacter()
{
}

void CCharacter::Load(UINT normalBmpID, UINT jumpBmpID)
{
    bmp.LoadBitmap(normalBmpID);    // 기본 이미지 로딩
    bmpJump.LoadBitmap(jumpBmpID);  // 점프 이미지 로딩
}

// 마우스 클릭 시 점프
void CCharacter::Jump()
{
    if (!m_isJumping && m_y >= 320)
    {
        m_isJumping = true;
        m_jumpSpeed = -17; // 위로 뛰는 속도 설정(음수)
    }
}

// 중력 적용
void CCharacter::ApplyGravity()
{
    if (m_isJumping)
    {
        m_y += m_jumpSpeed;  // 점프 방향으로 이동
        m_jumpSpeed += m_gravity;    // 중력 효과 (속도 감소)

        if (m_y >= 320)  // 땅에 닿으면 점프 종료
        {
            m_y = 320;
            m_jumpSpeed = 0;
            m_isJumping = false;
        }
    }
}

void CCharacter::Draw(CDC* pDC)
{
    CDC memDC;
    memDC.CreateCompatibleDC(pDC);

    CBitmap* pOldBitmap;
    BITMAP bmpInfo;
    int width, height;

    // 점프 중이면 점프 이미지 사용
    if (m_isJumping || m_isFalling)
    {
        pOldBitmap = memDC.SelectObject(&bmpJump);
        bmpJump.GetBitmap(&bmpInfo);
    }
    else
    {
        pOldBitmap = memDC.SelectObject(&bmp);
        bmp.GetBitmap(&bmpInfo);
    }

    width = bmpInfo.bmWidth;
    height = bmpInfo.bmHeight;

    pDC->TransparentBlt(
        m_x, m_y,
        width, height,
        &memDC,
        0, 0,
        width, height,
        RGB(0, 0, 255)
    );

    memDC.SelectObject(pOldBitmap);
}

CRect CCharacter::GetRect()
{
    BITMAP bmpInfo;
    bmp.GetBitmap(&bmpInfo);

    int padding = 30;  // ← 여유 공간을 줄 값
    return CRect(
        m_x + padding,
        m_y + padding,
        m_x + bmpInfo.bmWidth - padding,
        m_y + bmpInfo.bmHeight - padding
    );
}