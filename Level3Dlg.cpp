#include "pch.h"
#include "JellyRun.h"
#include "Level3Dlg.h"
#include "afxdialogex.h"
#include "GameOverDlg.h"
#include "GameClearDlg.h"
#include "ObstacleManager.h"
#include "ScoreManager.h"
#include "level.h"
#include "Character.h"
#include "Background.h"
#include "JellyRunDlg.h"
#include "LevelUpDlg.h"

IMPLEMENT_DYNAMIC(CLevel3Dlg, CDialogEx)

CLevel3Dlg::CLevel3Dlg(int currentScore, int highScore, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LEVEL3_DIALOG, pParent),
	m_Score(currentScore),         // 이전 점수 이어받음
	m_HighScore(highScore),        // 최고 점수도 유지
	m_ElapsedTime(0),
	m_JellyPathCreated(false)
{
}

CLevel3Dlg::~CLevel3Dlg() {}

void CLevel3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLevel3Dlg, CDialogEx)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

BOOL CLevel3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	MoveWindow(0, 0, 800, 600);

    // 하트 이미지 로드
    m_bmpHeart.LoadBitmap(IDB_HEART);
    BITMAP bmp;
    m_bmpHeart.GetBitmap(&bmp);
    m_szHeart = CSize(bmp.bmWidth, bmp.bmHeight);

	m_Background.LoadBackground(IDB_BACKGROUND_LEVEL3);
	m_Character.Load(IDB_CHARACTER, IDB_JUMP);
	m_Level.Init();

	m_ObstacleManager = CObstacleManager();
	m_ScoreManager = CScoreManager();
	m_ScoreManager.SetObstacleReference(m_ObstacleManager.GetObstacleList());
	m_ObstacleManager.SetDifficulty(3);  // 난이도 3

	m_IsInvincible = false;
	m_InvincibleTime = 0;

	SetTimer(1, 30, NULL);

	return TRUE;
}

void CLevel3Dlg::OnPaint()
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
	m_Level.Draw(&memDC);

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


void CLevel3Dlg::OnTimer(UINT_PTR nIDEvent)
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

        if (m_IsInvincible)
        {
            m_InvincibleTime--;
            if (m_InvincibleTime <= 0)
                m_IsInvincible = false;
        }

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

                CGameOverDlg dlg(m_Score, m_HighScore);
                if (dlg.DoModal() == IDOK)
                {
                    CJellyRunDlg* pLevel1 = new CJellyRunDlg;
                    pLevel1->Create(IDD_JELLYRUN_DIALOG);
                    pLevel1->ShowWindow(SW_SHOW);
                    this->DestroyWindow();
                }
                else
                {
                    PostQuitMessage(0);
                }
                return;
            }

            m_IsInvincible = true;
            m_InvincibleTime = 30;
            Invalidate(FALSE);
        }

        // 깃발 충돌 → 게임 클리어
        m_Level.CheckCollision(charRect);

        if (m_Level.IsLevelUp())
        {
            KillTimer(1);
            CGameClearDlg dlg(m_Score, m_HighScore);
            if (dlg.DoModal() == IDOK)
            {
                CJellyRunDlg* pLevel1 = new CJellyRunDlg;
                pLevel1->Create(IDD_JELLYRUN_DIALOG);
                pLevel1->ShowWindow(SW_SHOW);
                this->DestroyWindow();
            }
            else
            {
                PostQuitMessage(0);
            }
            return;
        }

        m_ScoreManager.CheckCollect(charRect, m_Score);
        Invalidate(FALSE);
    }

    CDialogEx::OnTimer(nIDEvent);
}


void CLevel3Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_Character.Jump();
	Invalidate(FALSE);
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CLevel3Dlg::SaveHighScore()
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


