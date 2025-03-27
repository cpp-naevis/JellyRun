#include "pch.h"
#include "Jelly.h"
#include "Resource.h"

CJelly::CJelly()
{
    m_x = 100;     // 초기 X 좌표
    m_y = 250;     // 초기 Y 좌표 (땅 위)
    m_jumpSpeed = 0; // 점프 속도
    m_jumpHeight = 15; // 최대 점프 높이
    m_gravity = 1; // 중력 값
    m_isJumping = false;
    m_isFalling = false;
}

CJelly::~CJelly() {}

void CJelly::LoadCharacter()
{
    // 리소스에서 젤리 캐릭터 비트맵 로드
    m_Character.LoadBitmap(IDB_CHARACTER);
}

// 마우스 클릭 시 점프
void CJelly::Jump()
{
    if (!m_isJumping && m_y >= 250)
    {
        m_isJumping = true;
        m_jumpSpeed = -15; // 위로 뛰는 속도 설정(음수)
    }
}

// 중력 적용
void CJelly::ApplyGravity()
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

// 화면에 하리보 젤리 출력하기
void CJelly::Draw(CDC* pDC)
{
    if (m_Character.m_hObject != NULL)
    {
        CDC memDC;
        memDC.CreateCompatibleDC(pDC);

        CBitmap* pOldBitmap = memDC.SelectObject(&m_Character);

        BITMAP bmp;
        m_Character.GetBitmap(&bmp);

        // 비율로 크기 조정 (30% 크기)
        float scale = 0.3f;
        int newWidth = static_cast<int>(bmp.bmWidth * scale);
        int newHeight = static_cast<int>(bmp.bmHeight * scale);

        // 흰색(RGB(255,255,255))을 투명하게 설정하여 출력
        pDC->TransparentBlt(m_x, m_y, newWidth, newHeight,
            &memDC, 0, 0, bmp.bmWidth, bmp.bmHeight,
            RGB(255, 255, 255));

        memDC.SelectObject(pOldBitmap);
    }
}