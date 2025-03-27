#pragma once
#include "Background.h"
#include "Character.h"
#include "ObstacleManager.h"
#include "ScoreManager.h"
#include "level.h"

class CLevel3Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLevel3Dlg)

public:
	CLevel3Dlg(int currentScore, int highScore, CWnd* pParent = nullptr);  // 점수 전달용 생성자
	virtual ~CLevel3Dlg();
	

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LEVEL3_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void SaveHighScore();
	CBitmap m_bmpHeart;  // 하트 비트맵 이미지
	CSize m_szHeart;     // 하트 이미지 크기


	DECLARE_MESSAGE_MAP()


	CBackground m_Background;
	CCharacter m_Character;
	CObstacleManager m_ObstacleManager;
	CScoreManager m_ScoreManager;
	CLevel m_Level;

	int m_Score;
	int m_HighScore;
	int m_ElapsedTime;
	bool m_JellyPathCreated;

	// 생명/무적 기능
	int m_Life = 3;
	bool m_IsInvincible;      // 무적상태 여부
	int m_InvincibleTime;     // 무적상태 남은 시간(프레임 수)
};
