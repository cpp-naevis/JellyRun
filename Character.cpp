#include "pch.h"
#include "Character.h"

CCharacter::CCharacter()
{
    m_x = 100;     // �ʱ� X ��ǥ
    m_y = 320;     // �ʱ� Y ��ǥ (�� ��)
    m_jumpSpeed = 20; // ���� �ӵ�
    m_jumpHeight = 0; // �ִ� ���� ����
    m_gravity = 1; // �߷� ��
    m_isJumping = false;
    m_isFalling = false;
}

CCharacter::~CCharacter()
{
}

void CCharacter::Load(UINT normalBmpID, UINT jumpBmpID)
{
    bmp.LoadBitmap(normalBmpID);    // �⺻ �̹��� �ε�
    bmpJump.LoadBitmap(jumpBmpID);  // ���� �̹��� �ε�
}

// ���콺 Ŭ�� �� ����
void CCharacter::Jump()
{
    if (!m_isJumping && m_y >= 320)
    {
        m_isJumping = true;
        m_jumpSpeed = -17; // ���� �ٴ� �ӵ� ����(����)
    }
}

// �߷� ����
void CCharacter::ApplyGravity()
{
    if (m_isJumping)
    {
        m_y += m_jumpSpeed;  // ���� �������� �̵�
        m_jumpSpeed += m_gravity;    // �߷� ȿ�� (�ӵ� ����)

        if (m_y >= 320)  // ���� ������ ���� ����
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

    // ���� ���̸� ���� �̹��� ���
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

    int padding = 30;  // �� ���� ������ �� ��
    return CRect(
        m_x + padding,
        m_y + padding,
        m_x + bmpInfo.bmWidth - padding,
        m_y + bmpInfo.bmHeight - padding
    );
}