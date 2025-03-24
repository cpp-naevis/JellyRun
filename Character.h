#pragma once
#include <afxwin.h>

class CCharacter
{
private:
    
    CBitmap bmp;     // ĳ���� �̹���
    int m_x;              // X ��ǥ
    int m_y;              // Y ��ǥ
    int m_jumpSpeed;      // ���� �ӵ�
    int m_jumpHeight;     // �ִ� ���� ����
    int m_gravity;        // �߷� ��
    bool m_isJumping;     // ���� ���� Ȯ��
    bool m_isFalling;

public:
    CCharacter();
    ~CCharacter();

    void Load(UINT bmpID);
    void Draw(CDC* pDC);
    void Jump();             // ���� ����
    void ApplyGravity();     // �߷� ����
    int GetY() { return m_y; }  // ���� Y ��ǥ ��ȯ
    bool IsJumping() { return m_isJumping; }
    CRect GetRect(); // �浹�� �簢��
};

