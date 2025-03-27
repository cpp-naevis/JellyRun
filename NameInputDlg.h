#pragma once
#include "afxdialogex.h"


// NameInputDlg 대화 상자

class NameInputDlg : public CDialogEx
{
	DECLARE_DYNAMIC(NameInputDlg)

public:
	NameInputDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~NameInputDlg();

	CString m_userName;  // 닉네임 저장 변수

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NAMEINPUT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	afx_msg void OnBnClickedButtonInput();

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);  // 배경/글자색 지정
	afx_msg BOOL OnInitDialog();

	// 배경 비트맵을 위한 멤버 변수
	CBitmap m_bmpBackground;     // 배경 비트맵
	CBrush m_brEditBg;           // 입력창 배경색용 브러시

	CFont m_fontEdit;
	CFont m_fontButton;

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);  // 배경을 지우지 않도록 설정
};
