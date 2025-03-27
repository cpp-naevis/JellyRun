// StartDlg.cpp: 구현 파일
//

#include "pch.h"
#include "JellyRun.h"
#include "afxdialogex.h"
#include "StartDlg.h"
#include "JellyRunDlg.h"
#include "NameInputDlg.h"


// StartDlg 대화 상자

IMPLEMENT_DYNAMIC(StartDlg, CDialogEx)

StartDlg::StartDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_START, pParent)
{

}

StartDlg::~StartDlg()
{
}

void StartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(StartDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_START, &StartDlg::OnBnClickedButtonStart)
	ON_WM_DRAWITEM() // 버튼 색 바꾸기
	ON_WM_ERASEBKGND() // 배경 지우기
END_MESSAGE_MAP()


// StartDlg 메시지 처리기

void StartDlg::OnBnClickedButtonStart()
{
	EndDialog(IDOK);  // StartDlg 닫기

	// 닉네임 입력창 열기
	NameInputDlg nameDlg;
	if (nameDlg.DoModal() == IDOK)
	{
		CString nickname = nameDlg.m_userName;

		CJellyRunDlg game;
		game.DoModal();  // 게임 시작
	}
}

void StartDlg::OnPaint()
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

BOOL StartDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 창 크기를 800x600으로 설정
	MoveWindow(0, 0, 800, 600);

	// BMP 배경 이미지 로딩
	m_bmpBackground.LoadBitmap(IDB_JELLY_START);

	// 버튼 폰트 생성
	m_fontButton.CreateFont(
		36, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Pretendard Black"));

	// 폰트 적용
	GetDlgItem(IDC_BUTTON_START)->SetFont(&m_fontButton);    // START 버튼
	//GetDlgItem(IDC_BUTTON_START)->ModifyStyle(0, BS_OWNERDRAW);  //  강제 Owner Draw
	return TRUE;
}

void StartDlg::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	AfxMessageBox(_T("DrawItem 호출됨"));  //  테스트용 팝업

	if (lpDrawItemStruct->CtlID == IDC_BUTTON_START)
	{
		CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
		CRect rect = lpDrawItemStruct->rcItem;

		// 둥근 모양 버튼 그리기
		const int radius = 20;  // 둥근 정도 조절 (숫자 크면 더 둥글게)
		CBrush brush(RGB(16, 0, 138));  // 딥블루 배경
		CBrush* pOldBrush = pDC->SelectObject(&brush);

		CPen pen(PS_SOLID, 1, RGB(16, 0, 138));  // 테두리와 동일 색
		CPen* pOldPen = pDC->SelectObject(&pen);

		pDC->RoundRect(rect.left, rect.top, rect.right, rect.bottom, radius, radius);

		// 텍스트: 흰색, 가운데 정렬
		CString text;
		GetDlgItem(IDC_BUTTON_START)->GetWindowText(text);
		pDC->SetTextColor(RGB(255, 255, 255));
		pDC->SetBkMode(TRANSPARENT);
		pDC->DrawText(text, &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

		// 원래 브러시/펜 복원
		pDC->SelectObject(pOldBrush);
		pDC->SelectObject(pOldPen);
	}
}

BOOL StartDlg::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;  // 배경 지우지 않도록 설정
}
