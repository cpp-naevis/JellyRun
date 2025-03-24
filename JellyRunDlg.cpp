#include "pch.h"
#include "JellyRun.h"
#include "JellyRunDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "Background.h"
#include "Character.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

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
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_TIMER()
    ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CJellyRunDlg 메시지 처리기

BOOL CJellyRunDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 아이콘 설정
    SetIcon(m_hIcon, TRUE);   // 큰 아이콘
    SetIcon(m_hIcon, FALSE);  // 작은 아이콘

    // 배경 이미지 로드
    m_Background.LoadBackground(IDB_BACKGROUND);
    m_Character.Load(IDB_CHARACTER);
    m_JellyManager.SpawnJellyLine(15, 40, 300);

    // 타이머 시작 (30ms 간격으로 화면 갱신)
    SetTimer(1, 30, NULL);

    RestartGame();

    return TRUE;
}

// 배경 그리기
void CJellyRunDlg::OnPaint()
{
    CPaintDC dc(this);

    CDC memDC;
    memDC.CreateCompatibleDC(&dc);
    CBitmap memBitmap;
    CRect rect;
    GetClientRect(&rect);
    memBitmap.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());

    CBitmap* pOldBitmap = memDC.SelectObject(&memBitmap);
    memDC.FillSolidRect(&rect, RGB(255, 255, 255)); // 배경색

    m_Background.Draw(&memDC); // 배경 그리기
    m_CoinManager.Draw(&memDC); // 동전 그리기
    m_Character.Draw(&memDC); // 캐릭터 그리기
    m_JellyManager.Draw(&memDC);

    // 점수 텍스트 출력
    CString scoreStr;
    scoreStr.Format(_T("SCORE: %d"), m_Score);
    memDC.SetBkMode(TRANSPARENT);
    memDC.SetTextColor(RGB(255, 0, 0));
    memDC.TextOutW(30, 30, scoreStr);

    dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

    memDC.SelectObject(pOldBitmap);
    
}

// 타이머  배경 위치 업데이트 및 다시 그리기
void CJellyRunDlg::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == 1)
    {
        m_Background.Update();
        m_CoinManager.Update();
        m_Character.ApplyGravity();
        m_JellyManager.Update();

        CRect charRect = m_Character.GetRect();
        if (m_CoinManager.CheckCollision(charRect))
        {
            KillTimer(1);  // 일단 게임 멈추기
            int result = MessageBox(_T("Game Over!\n다시 시작할까요?"), _T("게임 오버"), MB_YESNO | MB_ICONQUESTION);

            if (result == IDYES)
            {
                RestartGame();  // 재시작!
            }
            else
            {
                PostQuitMessage(0);  // 종료
            }
            return;
        }

        m_JellyManager.CheckCollect(charRect, m_Score);
        Invalidate(FALSE);  // OnPaint 호출 유도
    }

    CDialogEx::OnTimer(nIDEvent);
}

// 아이콘 표시
HCURSOR CJellyRunDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

BOOL CJellyRunDlg::OnEraseBkgnd(CDC* pDC)
{
    return TRUE;  // 배경 지우기 방지
}

// 마우스 클릭 시 점프 실행
void CJellyRunDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
    m_Character.Jump(); // 젤리 캐릭터 점프
    Invalidate(FALSE); // 화면 다시 그리기

    CDialogEx::OnLButtonDown(nFlags, point);
}

void CJellyRunDlg::RestartGame()
{
    // 점수 초기화
    m_Score = 0;


    // 장애물, 젤리 매니저 초기화
    m_CoinManager = CCoinManager();
    m_JellyManager = CJellyManager();

    // 젤리 라인 다시 생성
    m_JellyManager.SpawnJellyLine(15, 40, 300);

    // 타이머 재시작
    SetTimer(1, 30, NULL);

    // 화면 갱신
    Invalidate(FALSE);
}