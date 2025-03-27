#include "pch.h"
#include "JellyRun.h"
#include "LevelUpDlg.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CLevelUpDlg, CDialogEx)

CLevelUpDlg::CLevelUpDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_LEVELUP_DIALOG, pParent)
{
}

CLevelUpDlg::~CLevelUpDlg()
{
}

void CLevelUpDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLevelUpDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL CLevelUpDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // Pretendard 폰트 생성
    m_fontLevelUp.CreateFont(
        40, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0,
        HANGEUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Pretendard")
    );

    m_fontNext.CreateFont(
        20, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0,
        HANGEUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Pretendard")
    );

    GetDlgItem(IDC_STATIC_LEVELUP)->SetFont(&m_fontLevelUp);
    GetDlgItem(IDOK)->SetFont(&m_fontNext);
    return TRUE;
}

