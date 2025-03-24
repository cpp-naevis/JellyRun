
// JellyRunDlg.h: 헤더 파일
//

#pragma once
#include "afxwin.h"
#include <gdiplus.h>  // PNG, JPG 지원
#include "Jelly.h"
#include <vector>     // 장애물 관리

using namespace Gdiplus;

// CJellyRunDlg 대화 상자
class CJellyRunDlg : public CDialogEx
{
// 생성입니다.
public:
	CJellyRunDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_JELLYRUN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	DECLARE_MESSAGE_MAP()


private:
	// 배경 비트맵 관련 변수
	CBitmap m_Background;  // 비트맵 객체
	CJelly m_Jelly; // 젤리 캐릭터 객체
};