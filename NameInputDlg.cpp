// NameInputDlg.cpp: 구현 파일
//

#include "pch.h"
#include "JellyRun.h"
#include "afxdialogex.h"
#include "NameInputDlg.h"


// NameInputDlg 대화 상자

IMPLEMENT_DYNAMIC(NameInputDlg, CDialogEx)

NameInputDlg::NameInputDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_DIALOG_NAMEINPUT, pParent)
{

}

NameInputDlg::~NameInputDlg()
{
}

void NameInputDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_NAME, m_userName); // Edit Control 연결
}


BEGIN_MESSAGE_MAP(NameInputDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_INPUT, &NameInputDlg::OnBnClickedButtonInput)
    ON_WM_CTLCOLOR()
    ON_WM_DRAWITEM()
    ON_WM_PAINT()  // 배경을 그리기 위한 메시지 핸들러
    ON_WM_ERASEBKGND()  // 배경 지우지 않도록
END_MESSAGE_MAP()

void NameInputDlg::OnPaint()
{
    CPaintDC dc(this);

    // 메모리 DC 생성
    CDC memDC;
    memDC.CreateCompatibleDC(&dc);

    BITMAP bmpInfo;
    m_bmpBackground.GetBitmap(&bmpInfo);  // BMP 크기 얻기

    CBitmap* pOldBitmap = memDC.SelectObject(&m_bmpBackground);

    // 현재 다이얼로그 크기에 맞춰서 StretchBlt
    CRect rect;
    GetClientRect(&rect);
    dc.StretchBlt(0, 0, rect.Width(), rect.Height(),
        &memDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);

    memDC.SelectObject(pOldBitmap);  // 원래대로 복원
}

// NameInputDlg 메시지 처리기
void NameInputDlg::OnBnClickedButtonInput()
{
    UpdateData(TRUE);  // 입력값 m_userName에 저장
    EndDialog(IDOK);   // 다이얼로그 닫기
}

BOOL NameInputDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 창 크기를 800x600으로 설정
    MoveWindow(0, 0, 800, 600);

    // 배경 비트맵 로드
    m_bmpBackground.LoadBitmap(IDB_NICKNAME);

    // ------폰트 설정------
    m_fontEdit.CreateFont(30, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
        HANGEUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Pretendard"));

    m_fontButton.CreateFont(20, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0,
        HANGEUL_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Pretendard"));

    // 폰트 적용
    GetDlgItem(IDC_EDIT_NAME)->SetFont(&m_fontEdit);
    GetDlgItem(IDC_BUTTON_INPUT)->SetFont(&m_fontButton);
    //GetDlgItem(IDC_BUTTON_INPUT)->ModifyStyle(0, BS_OWNERDRAW); // 버튼 스타일 강제 적용 (Owner Draw)

    // 입력창 배경색용 브러시
    m_brEditBg.CreateSolidBrush(RGB(225, 240, 255));  // 하늘색 배경

    return TRUE;
}

BOOL NameInputDlg::OnEraseBkgnd(CDC* pDC)
{
    return TRUE;  // 배경을 지우지 않도록 설정
}

// 닉네임 입력창 배경색 설정
HBRUSH NameInputDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    if (pWnd->GetDlgCtrlID() == IDC_EDIT_NAME)
    {
        // 배경색을 하늘색으로 설정
        pDC->SetBkColor(RGB(225, 240, 255));
        pDC->SetTextColor(RGB(0, 0, 0)); // 검정색 글씨

        // 투명 배경 설정
        pDC->SetBkMode(OPAQUE);  // 배경을 투명하게 설정

        // 입력창의 배경색용 브러시 반환
        return (HBRUSH)m_brEditBg;
    }

    // 나머지 컨트롤은 투명 배경으로 설정
    pDC->SetBkMode(TRANSPARENT);
    return CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
}
