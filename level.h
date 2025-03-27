#pragma once
#include <afxwin.h>

class CLevel
{
private:
    CPoint pos;           // 위치
    int speed;            // 이동 속도
    bool appeared;        // 깃발 등장 여부
    bool levelUp;         // 레벨업 여부
    CRect rect;           // 충돌 판정 영역
    CBitmap bmp;          // 비트맵
    bool bmpLoaded;       // 비트맵 로드 확인
    

public:
    CLevel();
    ~CLevel();

    void Init();                     // 초기화
    void Update(int elapsedTime);    // 시간에 따라 업데이트
    void Draw(CDC* pDC);             // 화면에 그림
    void CheckCollision(CRect playerRect); // 충돌 확인
    bool IsAppeared() const;
    bool IsLevelUp() const;
    CPoint GetPosition() const;
};

