#include "pch.h"
#include "Jelly.h"
#include "Resource.h"

CJelly::CJelly()
{
    m_x = 100;     // �ʱ� X ��ǥ
    m_y = 250;     // �ʱ� Y ��ǥ (�� ��)
    m_jumpSpeed = 0; // ���� �ӵ�
    m_jumpHeight = 15; // �ִ� ���� ����
    m_gravity = 1; // �߷� ��
    m_isJumping = false;
    m_isFalling = false;
}

CJelly::~CJelly() {}

void CJelly::LoadCharacter()
{
    // ���ҽ����� ���� ĳ���� ��Ʈ�� �ε�
    m_Character.LoadBitmap(IDB_CHARACTER);
}

// ���콺 Ŭ�� �� ����
void CJelly::Jump()
{
    if (!m_isJumping && m_y >= 250)
    {
        m_isJumping = true;
        m_jumpSpeed = -15; // ���� �ٴ� �ӵ� ����(����)
    }
}

// �߷� ����
void CJelly::ApplyGravity()
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

// ȭ�鿡 �ϸ��� ���� ����ϱ�
void CJelly::Draw(CDC* pDC)
{
    if (m_Character.m_hObject != NULL)
    {
        CDC memDC;
        memDC.CreateCompatibleDC(pDC);

        CBitmap* pOldBitmap = memDC.SelectObject(&m_Character);

        BITMAP bmp;
        m_Character.GetBitmap(&bmp);

        // ������ ũ�� ���� (30% ũ��)
        float scale = 0.3f;
        int newWidth = static_cast<int>(bmp.bmWidth * scale);
        int newHeight = static_cast<int>(bmp.bmHeight * scale);

        // ���(RGB(255,255,255))�� �����ϰ� �����Ͽ� ���
        pDC->TransparentBlt(m_x, m_y, newWidth, newHeight,
            &memDC, 0, 0, bmp.bmWidth, bmp.bmHeight,
            RGB(255, 255, 255));

        memDC.SelectObject(pOldBitmap);
    }
}