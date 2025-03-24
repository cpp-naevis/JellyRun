#pragma once
#include "afxwin.h"

class CJelly
{
public:
    CJelly();  // 생성자
    ~CJelly(); // 소멸자

    void LoadCharacter();    // 젤리 이미지 로드
    void Jump();             // 점프 실행
    void ApplyGravity();     // 중력 적용
    void Draw(CDC* pDC);     // 젤리 캐릭터 출력

    int GetY() { return m_y; }  // 현재 Y 좌표 반환
    bool IsJumping() { return m_isJumping; }

private:
    CBitmap m_Character;  // 젤리 비트맵 이미지
    int m_x;              // X 좌표
    int m_y;              // Y 좌표
    int m_jumpSpeed;      // 점프 속도
    int m_jumpHeight;     // 최대 점프 높이
    int m_gravity;        // 중력 값
    bool m_isJumping;     // 점프 상태 확인
    bool m_isFalling;
};