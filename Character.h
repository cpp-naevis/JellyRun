#pragma once
#include <afxwin.h>

class CCharacter
{
private:

    CBitmap bmp;          // ĳ���� �̹���
    CBitmap bmpJump;      // ���� �̹���

    int m_x;              // X ��ǥ
    int m_y;              // Y ��ǥ
    int m_jumpSpeed;      // ���� �ӵ�
    int m_jumpHeight;     // �ִ� ���� ����
    int m_gravity;        // �߷� ��
    bool m_isJumping;     // ���� ���� Ȯ��
    bool m_isFalling;     // ���� �� ����

public:
    CCharacter();
    ~CCharacter();

    void Load(UINT normalBmpID, UINT jumpBmpID);  // �̹��� 2�� �ε�
    void Draw(CDC* pDC);     // ���� ���¿� ���� �̹��� �����Ͽ� �׸���
    void Jump();             // ���� ����
    void ApplyGravity();     // �߷� ����
    int GetY() { return m_y; } // ���� Y ��ǥ ��ȯ
    bool IsJumping() { return m_isJumping; }
    CRect GetRect(); // �浹�� �簢��
};