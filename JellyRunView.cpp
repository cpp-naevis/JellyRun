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
    SetTimer(TIMER_ID, 30, NULL);  // 30ms���� ȣ��
}

void CJellyRunView::OnTimer(UINT_PTR nIDEvent)
{
    if (nIDEvent == TIMER_ID)
    {
        m_Background.Update();
        Invalidate();  // �ٽ� �׸��� ��û
    }

    CView::OnTimer(nIDEvent);
}

void CJellyRunView::OnDraw(CDC* pDC)
{
    AfxMessageBox(_T("OnDraw �����!"));  // ���� Ȯ��
    m_Background.Draw(pDC);
}