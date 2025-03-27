#pragma once
#include "Background.h"

class CGameClearDlg : public CDialogEx
{
public:
    CGameClearDlg(int score, int highScore, CWnd* pParent = nullptr);
    CBitmap m_Background;
    int m_score;
    int m_highScore;
    CFont m_scoreFont;
    CFont m_highScoreFont;


#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_DIALOG_GAMEOVER };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedRestart();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);


    DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnStnClickedStaticScore();
    afx_msg void OnBnClickedScoreList();
};