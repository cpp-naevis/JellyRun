#pragma once

// CLevelUpDlg 대화 상자

class CLevelUpDlg : public CDialogEx
{
    DECLARE_DYNAMIC(CLevelUpDlg)

public:
    CLevelUpDlg(CWnd* pParent = nullptr);   // 표준 생성자
    virtual ~CLevelUpDlg();

    // 대화 상자 데이터
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_LEVELUP_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원
    CFont m_fontLevelUp; // 폰트
    CFont m_fontNext; // 폰트
    virtual BOOL OnInitDialog();
    DECLARE_MESSAGE_MAP()
};