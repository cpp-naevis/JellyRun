﻿#pragma once
#include "afxdialogex.h"


// GameInstructionDlg 대화 상자

class GameInstructionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GameInstructionDlg)

public:
	GameInstructionDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~GameInstructionDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NAMEINPUT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
