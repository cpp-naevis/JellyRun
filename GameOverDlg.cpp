#include "pch.h"
#include "JellyRun.h"
#include "GameOverDlg.h"
#include "afxdialogex.h"
#include "Background.h"


CGameOverDlg::CGameOverDlg(int score, int highScore, CWnd* pParent)
    : CDialogEx(IDD_DIALOG_GAMEOVER, pParent), m_score(score), m_highScore(highScore)
{
}

void CGameOverDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGameOverDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_RESTART, &CGameOverDlg::OnBnClickedRestart)
    ON_WM_ERASEBKGND()
    ON_WM_CTLCOLOR()
    ON_STN_CLICKED(IDC_STATIC_SCORE, &CGameOverDlg::OnStnClickedStaticScore)
    ON_BN_CLICKED(IDC_SCORE_LIST, &CGameOverDlg::OnBnClickedScoreList)
END_MESSAGE_MAP()

BOOL CGameOverDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    MoveWindow(0, 0, 800, 600);  // 다이얼로그 크기 조정

    CString scoreStr;
    scoreStr.Format(_T("%d"), m_score);
    SetDlgItemText(IDC_STATIC_SCORE, scoreStr);  // 점수 출력용 Static Control 필요!

    //  폰트 생성 (크고 굵은 글씨)
    m_scoreFont.CreateFont(
        36,                // 글자 높이 (px)
        0,                 // 너비 (0이면 자동)
        0, 0,              // 기울기, 회전
        FW_BOLD,           // 굵기
        FALSE, FALSE, FALSE,  // 이탤릭, 밑줄, 취소선
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS,
        _T("맑은 고딕")      // 폰트 이름 (변경 가능)
    );

    CString highStr;
    highStr.Format(_T("%d"), m_highScore);
    SetDlgItemText(IDC_STATIC_HIGHSCORE, highStr);

    //  폰트 생성 (크고 굵은 글씨)
    m_highScoreFont.CreateFont(
        36,                // 글자 높이 (px)
        0,                 // 너비 (0이면 자동)
        0, 0,              // 기울기, 회전
        FW_BOLD,           // 굵기
        FALSE, FALSE, FALSE,  // 이탤릭, 밑줄, 취소선
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        DEFAULT_PITCH | FF_SWISS,
        _T("맑은 고딕")      // 폰트 이름 (변경 가능)
    );

    //  폰트를 Static_SCORE에 적용
    GetDlgItem(IDC_STATIC_SCORE)->SetFont(&m_scoreFont);

    //  폰트를 Static_HIGHSCORE에 적용
    GetDlgItem(IDC_STATIC_HIGHSCORE)->SetFont(&m_highScoreFont);

    // 배경 이미지 로드
    m_Background.LoadBitmap(IDB_BACKGROUND_GAMEOVER);

    return TRUE;
}

BOOL CGameOverDlg::OnEraseBkgnd(CDC* pDC)
{
    if (m_Background.m_hObject)
    {
        CDC memDC;
        memDC.CreateCompatibleDC(pDC);
        CBitmap* pOld = memDC.SelectObject(&m_Background);

        BITMAP bmp;
        m_Background.GetBitmap(&bmp);

        CRect rect;
        GetClientRect(&rect);

        pDC->StretchBlt(0, 0, rect.Width(), rect.Height(),
            &memDC, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);

        memDC.SelectObject(pOld);
        return TRUE;
    }

    return CDialogEx::OnEraseBkgnd(pDC);
}

HBRUSH CGameOverDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

    // 점수 Static Text에만 적용
    if (pWnd->GetDlgCtrlID() == IDC_STATIC_SCORE)
    {
        pDC->SetBkMode(TRANSPARENT);               // 배경 투명
        pDC->SetTextColor(RGB(0, 0, 0));     // 글자 색 
        return (HBRUSH)GetStockObject(NULL_BRUSH); // 배경 안 그림
    }

    if (pWnd->GetDlgCtrlID() == IDC_STATIC_HIGHSCORE)
    {
        pDC->SetBkMode(TRANSPARENT);               // 배경 투명
        pDC->SetTextColor(RGB(0, 0, 0));     // 글자 색 
        return (HBRUSH)GetStockObject(NULL_BRUSH); // 배경 안 그림
    }

    return hbr;
}


void CGameOverDlg::OnBnClickedRestart()
{
    EndDialog(IDOK);  // OK 리턴으로 메인 다이얼로그에 알려줌
}
void CGameOverDlg::OnStnClickedStaticScore()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CGameOverDlg::OnBnClickedScoreList()
{
    // TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


