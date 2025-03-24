#pragma once
#include "Background.h"

class CJellyRunView : public CView
{
protected:
    CJellyRunView() noexcept;
    DECLARE_DYNCREATE(CJellyRunView)

public:
    CBackground m_Background;

protected:
    virtual void OnDraw(CDC* pDC);
    virtual void OnInitialUpdate();

    afx_msg void OnTimer(UINT_PTR nIDEvent);
    DECLARE_MESSAGE_MAP()
};
