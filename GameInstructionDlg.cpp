// GameInstructionDlg.cpp: 구현 파일
//

#include "pch.h"
#include "JellyRun.h"
#include "afxdialogex.h"
#include "GameInstructionDlg.h"


// GameInstructionDlg 대화 상자

IMPLEMENT_DYNAMIC(GameInstructionDlg, CDialogEx)

GameInstructionDlg::GameInstructionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_NAMEINPUT, pParent)
{

}

GameInstructionDlg::~GameInstructionDlg()
{
}

void GameInstructionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GameInstructionDlg, CDialogEx)
END_MESSAGE_MAP()


// GameInstructionDlg 메시지 처리기
