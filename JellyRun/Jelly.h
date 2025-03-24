#pragma once
#include "afxwin.h"

class CJelly
{
public:
    CJelly();  // ������
    ~CJelly(); // �Ҹ���

    void LoadCharacter();    // ���� �̹��� �ε�
    void Jump();             // ���� ����
    void ApplyGravity();     // �߷� ����
    void Draw(CDC* pDC);     // ���� ĳ���� ���

    int GetY() { return m_y; }  // ���� Y ��ǥ ��ȯ
    bool IsJumping() { return m_isJumping; }

private:
    CBitmap m_Character;  // ���� ��Ʈ�� �̹���
    int m_x;              // X ��ǥ
    int m_y;              // Y ��ǥ
    int m_jumpSpeed;      // ���� �ӵ�
    int m_jumpHeight;     // �ִ� ���� ����
    int m_gravity;        // �߷� ��
    bool m_isJumping;     // ���� ���� Ȯ��
    bool m_isFalling;
};