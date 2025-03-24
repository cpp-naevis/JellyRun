#include "pch.h"
#include "JellyRun.h"
#include "JellyRunView.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TIMER_ID 1

IMPLEMENT_DYNCREATE(CJellyRunView, CView)

BEGIN_MESSAGE_MAP(CJellyRunView, CView)
    ON_WM_TIMER()
END_MESSAGE_MAP()

CJellyRunView::CJellyRunView() noexcept
{
}

void CJellyRunView::OnInitialUpdate()
{
    CView::OnInitialUpdate();
    m_Background.LoadBackground(IDB_BACKGROUND);
    SetTimer(TIMER_ID, 30, NULL);  // 30ms마다 호출
}

void CJellyRunView::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == TIMER_ID)
    {
        m_Background.Update();
        Invalidate();  // 다시 그리기 요청
    }

    CView::OnTimer(nIDEvent);
}

void CJellyRunView::OnDraw(CDC* pDC)
{
    AfxMessageBox(_T("OnDraw 실행됨!"));  // 실행 확인
    m_Background.Draw(pDC);
}