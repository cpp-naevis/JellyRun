#pragma once
#include "afxdialogex.h"


// StartDlg 대화 상자

class StartDlg : public CDialogEx
{
	DECLARE_DYNAMIC(StartDlg)

public:
	StartDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~StartDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_START };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();  // 다이얼로그 초기화 함수 선언

	afx_msg void OnBnClickedButtonStart(); // START 버튼 클릭 함수
	afx_msg void OnPaint(); // OnPaint
	afx_msg void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct); // 버튼 꾸미기
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()

private:
	CBitmap m_bmpBackground; 
	CFont m_fontTitle;   // 제목 텍스트용
	CFont m_fontButton;  // 버튼용

};
