#pragma once
#include <afxwin.h>

class CCharacter
{
private:
    
    CBitmap bmp;     // 캐릭터 이미지
    int m_x;              // X 좌표
    int m_y;              // Y 좌표
    int m_jumpSpeed;      // 점프 속도
    int m_jumpHeight;     // 최대 점프 높이
    int m_gravity;        // 중력 값
    bool m_isJumping;     // 점프 상태 확인
    bool m_isFalling;

public:
    CCharacter();
    ~CCharacter();

    void Load(UINT bmpID);
    void Draw(CDC* pDC);
    void Jump();             // 점프 실행
    void ApplyGravity();     // 중력 적용
    int GetY() { return m_y; }  // 현재 Y 좌표 반환
    bool IsJumping() { return m_isJumping; }
    CRect GetRect(); // 충돌용 사각형
};

