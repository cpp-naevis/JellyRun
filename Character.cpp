#include "pch.h"
#include "Character.h"

CCharacter::CCharacter()
{
    m_x = 100;     // �ʱ� X ��ǥ
    m_y = 250;     // �ʱ� Y ��ǥ (�� ��)
    m_jumpSpeed = 0; // ���� �ӵ�
    m_jumpHeight = 35; // �ִ� ���� ����
    m_gravity = 1; // �߷� ��
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

// ���콺 Ŭ�� �� ����
void CCharacter::Jump()
{
    if (!m_isJumping && m_y >= 250)
    {
        m_isJumping = true;
        m_jumpSpeed = -15; // ���� �ٴ� �ӵ� ����(����)
    }
}

// �߷� ����
void CCharacter::ApplyGravity()
{
    if (m_isJumping)
    {
        m_y += m_jumpSpeed;  // ���� �������� �̵�
        m_jumpSpeed += m_gravity;    // �߷� ȿ�� (�ӵ� ����)

        if (m_y >= 250)  // ���� ������ ���� ����
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
        &memDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, RGB(255, 255, 255)); // ����Ÿ ����ó��

    memDC.SelectObject(pOldBmp);
}

CRect CCharacter::GetRect()
{
    BITMAP bmpInfo;
    bmp.GetBitmap(&bmpInfo);

    int padding = 30;  // �� ���� ������ �� ��
    return CRect(
        m_x + padding*2,
        m_y + padding*1.5,
        m_x + bmpInfo.bmWidth - padding*2,
        m_y + bmpInfo.bmHeight - padding*1.5
    );
}