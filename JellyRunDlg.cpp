#include "pch.h"
#include "JellyRun.h"
#include "JellyRunDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#include "Background.h"
#include "Character.h"
#include "GameOverDlg.h"
#include "GameClearDlg.h"
#include "level.h"
#include "LevelUpDlg.h"
#include "Level2Dlg.h"
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CJellyRunDlg 대화 상자

CJellyRunDlg::CJellyRunDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_JELLYRUN_DIALOG, pParent),
    m_GoalVisible(false),
    m_IsInvincible(false),
    m_InvincibleTime(0),
    m_Life(3),
    m_Score(0),
    m_HighScore(0),
    m_JellyPathCreated(false), 
    m_SpawnCounter(0)       
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
    ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

BOOL CJellyRunDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 배경음악 재생 (비동기 + 반복)
    PlaySound(_T("bgm\\bgm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    // 하트 이미지 로드
    m_bmpHeart.LoadBitmap(IDB_HEART);
    BITMAP bmp;
    m_bmpHeart.GetBitmap(&bmp);
    m_szHeart = CSize(bmp.bmWidth, bmp.bmHeight);

    MoveWindow(0, 0, 800, 600);
    LoadHighScore();

    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);

    m_Background.LoadBackground(IDB_BACKGROUND);
    m_Character.Load(IDB_CHARACTER, IDB_JUMP);
    m_ScoreManager.SetObstacleReference(m_ObstacleManager.GetObstacleList());

    m_IsInvincible = false;
    m_InvincibleTime = 0;

    SetTimer(1, 30, NULL);
    RestartGame();
    return TRUE;
}


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
    memDC.FillSolidRect(&rect, RGB(255, 255, 255));

    m_Background.Draw(&memDC);
    m_ObstacleManager.Draw(&memDC);
    m_Character.Draw(&memDC);
    m_ScoreManager.Draw(&memDC);
    m_Level.Draw(&memDC);  // 추가: 깃발 그리기

    // 하트 그리기
    CDC heartDC;
    heartDC.CreateCompatibleDC(&memDC);
    CBitmap* pOldHeart = heartDC.SelectObject(&m_bmpHeart);

    for (int i = 0; i < m_Life; i++)
    {
        memDC.TransparentBlt(30 + i * (m_szHeart.cx + 10), 30,
            m_szHeart.cx, m_szHeart.cy,
            &heartDC, 0, 0, m_szHeart.cx, m_szHeart.cy,
            RGB(255, 255, 255));
    }

    heartDC.SelectObject(pOldHeart);


    // 현재 점수 표시
    CString scoreStr;
    scoreStr.Format(_T("SCORE: %d"), m_Score);

    // 폰트 생성
    CFont font;
    font.CreateFont(
        28, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0,
        DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY, VARIABLE_PITCH, _T("Pretendard")
    );
    CFont* pOldFont = memDC.SelectObject(&font);

    // 배경 투명, 글씨 색상 설정
    memDC.SetBkMode(TRANSPARENT);
    memDC.SetTextColor(RGB(255, 0, 0));
    memDC.TextOutW(630, 35, scoreStr);



    dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
    memDC.SelectObject(pOldBitmap);
}


void CJellyRunDlg::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == 1)
    {
        m_ElapsedTime += 30;
        m_Background.Update();

        if (m_Level.IsAppeared())
        {
            m_ObstacleManager.ClearObstacles();

            if (!m_JellyPathCreated)
            {
                m_ScoreManager.CreateJellyPathTo(m_Level.GetPosition());
                m_JellyPathCreated = true;
            }
            m_ScoreManager.Update(false);
        }
        else
        {
            m_ObstacleManager.Update();
            m_ScoreManager.Update(true);
        }

        m_Character.ApplyGravity();
        m_Level.Update(m_ElapsedTime);

        CRect charRect = m_Character.GetRect();

        // 무적 상태 시간 감소
        if (m_IsInvincible)
        {
            m_InvincibleTime--;
            if (m_InvincibleTime <= 0)
                m_IsInvincible = false;
        }

        // 장애물 충돌 처리
        if (!m_IsInvincible && m_ObstacleManager.CheckCollision(charRect))
        {
            m_Life--;

            if (m_Life <= 0)
            {
                m_Life = 0;
                Invalidate(FALSE);
                UpdateWindow();
                KillTimer(1);
                SaveHighScore();

                CGameOverDlg gameOverDlg(m_Score, m_HighScore);
                if (gameOverDlg.DoModal() == IDOK)
                    RestartGame();
                else
                    PostQuitMessage(0);

                return;
            }

            m_IsInvincible = true;
            m_InvincibleTime = 30;
            Invalidate(FALSE);
        }

        // 깃발 충돌 체크 및 레벨업 처리
        m_Level.CheckCollision(charRect);

        if (m_Level.IsLevelUp())
        {
            KillTimer(1);

            CLevelUpDlg dlg;
            if (dlg.DoModal() == IDOK)
            {
                CLevel2Dlg* pLevel2 = new CLevel2Dlg(m_Score, m_HighScore);
                pLevel2->Create(IDD_LEVEL2_DIALOG, this);
                pLevel2->ShowWindow(SW_SHOW);
                this->ShowWindow(SW_HIDE);


            }
            return;
        }

        m_ScoreManager.CheckCollect(charRect, m_Score);
        Invalidate(FALSE);
    }

    CDialogEx::OnTimer(nIDEvent);
}


HCURSOR CJellyRunDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

BOOL CJellyRunDlg::OnEraseBkgnd(CDC* pDC)
{
    return TRUE;
}

void CJellyRunDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
    m_Character.Jump();
    Invalidate(FALSE);
    CDialogEx::OnLButtonDown(nFlags, point);
}

void CJellyRunDlg::RestartGame()
{
    m_Score = 0;
    m_Life = 3;  // 생명 초기화
    m_ElapsedTime = 0;
    m_GoalVisible = false;
    m_JellyPathCreated = false;

    m_Level.Init();  // 추가: 레벨 시스템 초기화

    m_ObstacleManager = CObstacleManager();
    m_ScoreManager = CScoreManager();
    m_ScoreManager.SetObstacleReference(m_ObstacleManager.GetObstacleList());

    SetTimer(1, 30, NULL);
    Invalidate(FALSE);
}

void CJellyRunDlg::LoadHighScore()
{
    CStdioFile file;
    CString path = _T("highscore.txt");
    CString str;

    if (file.Open(path, CFile::modeRead | CFile::typeText))
    {
        if (file.ReadString(str))
            m_HighScore = _ttoi(str);
        file.Close();
    }
}

void CJellyRunDlg::SaveHighScore()
{
    if (m_Score > m_HighScore)
    {
        m_HighScore = m_Score;
        CStdioFile file;
        CString path = _T("highscore.txt");
        if (file.Open(path, CFile::modeCreate | CFile::modeWrite | CFile::typeText))
        {
            CString str;
            str.Format(_T("%d"), m_HighScore);
            file.WriteString(str);
            file.Close();
        }
    }
}

