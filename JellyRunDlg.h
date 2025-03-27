
#pragma once
#include "Background.h"
#include "ObstacleManager.h"
#include "Character.h"
#include <vector>
#include "ScoreManager.h"
#include "Level.h"

class CJellyRunDlg : public CDialogEx
{
protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    virtual BOOL OnEraseBkgnd(CDC* pDC);

    HICON m_hIcon;              // 아이콘 핸들 선언
    CBackground m_Background;   // 배경 객체
    CObstacleManager m_ObstacleManager;
    CCharacter m_Character;
    CScoreManager m_ScoreManager;
    CBitmap m_bmpHeart;  // 하트 비트맵 이미지
    CSize m_szHeart;     // 하트 이미지 크기

    int m_Life = 3;     // 생명 기능
    int m_Score = 0;
    int m_HighScore = 0;
    int m_ElapsedTime = 0;
    bool m_GoalVisible = false;  // 깃발 등장 여부
    bool m_JellyPathCreated = false;  // 깃발 일자 젤리 생성 여부
    CLevel m_Level;

    DECLARE_MESSAGE_MAP()

public:
    int m_SpawnCounter = 60;               // 장애물/젤리 생성 주기
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    CJellyRunDlg(CWnd* pParent = nullptr);
    void RestartGame();  // 게임 재시작 함수 선언
    void LoadHighScore();  // 게임 최고 점수 로드 함수 선언
    void SaveHighScore();  // 게임 최고 점수 저장 함수 선언
    void ShowGameClear();       // 게임 클리어 화면 출력

private:
    bool m_IsInvincible;      // 무적상태 여부
    int m_InvincibleTime;     // 무적상태 남은 시간(프레임 수)
};