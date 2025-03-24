
// JellyRunDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "JellyRun.h"
#include "JellyRunDlg.h"
#include "afxdialogex.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CJellyRunDlg 대화 상자



CJellyRunDlg::CJellyRunDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_JELLYRUN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJellyRunDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CJellyRunDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT() // 화면 다시 그리기
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN() // 마우스 클릭
	ON_WM_TIMER() // 타이머
END_MESSAGE_MAP()


// CJellyRunDlg 메시지 처리기

BOOL CJellyRunDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Jelly.LoadCharacter(); // 젤리 캐릭터 로드

	SetTimer(1, 30, NULL); // 타이머 설정(30ms 단위로 호출)

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	// 리소스에서 비트맵 로드
	m_Background.LoadBitmap(IDB_BACKGROUND);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CJellyRunDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CJellyRunDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 마우스 클릭 시 점프 실행
void CJellyRunDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_Jelly.Jump(); // 젤리 캐릭터 점프
	Invalidate(FALSE); // 화면 다시 그리기

	CDialogEx::OnLButtonDown(nFlags, point);
}

// 중력 적용 타이머
void CJellyRunDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1) // 타이머 ID 1번
	{
		m_Jelly.ApplyGravity(); // 중력 적용하여 위치 업데이트
		Invalidate(FALSE); // 화면 다시 그리기
	}

	CDialogEx::OnTimer(nIDEvent);
}

// 화면 다시 그리기
void CJellyRunDlg::OnPaint()
{
	CPaintDC dc(this); // 실제 화면 DC

	// 더블 버퍼용 메모리 DC 생성
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	// 버퍼용 비트맵 생성 (화면 크기와 동일)
	CRect rect;
	GetClientRect(&rect);
	CBitmap bufferBitmap;
	bufferBitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());

	CBitmap* pOldBitmap = memDC.SelectObject(&bufferBitmap);

	// 배경 이미지 그리기
	CDC bgDC;
	bgDC.CreateCompatibleDC(&dc);
	CBitmap* pOldBg = bgDC.SelectObject(&m_Background);

	BITMAP bmp;
	m_Background.GetBitmap(&bmp);

	// 배경 크기 2배로 확대해서 화면에 출력
	int newWidth = bmp.bmWidth * 2;
	int newHeight = bmp.bmHeight * 2;
	memDC.StretchBlt(0, 0, newWidth, newHeight, &bgDC, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);

	// 캐릭터 그리기
	m_Jelly.Draw(&memDC);

	// 최종적으로 메모리 DC를 실제 DC에 출력
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	// 리소스 정리
	memDC.SelectObject(pOldBitmap); // 원래 비트맵으로 복원
	bgDC.SelectObject(pOldBg);
}