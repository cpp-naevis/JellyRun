
#pragma once
#include "Background.h"
#include "CoinManager.h"
#include "Character.h"
#include <vector>
#include "JellyManager.h"

class CJellyRunDlg : public CDialogEx
{
protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    virtual BOOL OnEraseBkgnd(CDC* pDC);

    HICON m_hIcon;              // 아이콘 핸들 선언
    CBackground m_Background;   // 배경 객체
    CCoinManager m_CoinManager;
    CCharacter m_Character;
    CJellyManager m_JellyManager;
    int m_Score = 0;

    DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    CJellyRunDlg(CWnd* pParent = nullptr);
    void RestartGame();  // 게임 재시작 함수 선언
};