#include "CFrameWindowWnd.h"

CFrameWindowWnd::CFrameWindowWnd()
{
	m_pWndShadow = nullptr;
}

LPCTSTR CFrameWindowWnd::GetWindowClassName() const
{
	return _T("UIMainFrame");
}

UINT CFrameWindowWnd::GetClassStyle() const
{
	return UI_CLASSSTYLE_FRAME | CS_DBLCLKS;
}

void CFrameWindowWnd::OnFinalMessage(HWND)
{
	delete this;
}

void CFrameWindowWnd::Init()
{
	//
}

bool CFrameWindowWnd::OnHChanged(void* param)
{
	DuiLib::TNotifyUI* pMsg = (DuiLib::TNotifyUI*)param;

	if (pMsg->sType == _T("valuechanged"))
	{
		short H, S, L;
		DuiLib::CPaintManagerUI::GetHSL(&H, &S, &L);
		DuiLib::CPaintManagerUI::SetHSL(true, (static_cast<DuiLib::CSliderUI*>(pMsg->pSender))->GetValue(), S, L);
	}

	return true;
}

bool CFrameWindowWnd::OnSChanged(void* param)
{
	DuiLib::TNotifyUI* pMsg = (DuiLib::TNotifyUI*)param;

	if (pMsg->sType == _T("valuechanged"))
	{
		short H, S, L;
		DuiLib::CPaintManagerUI::GetHSL(&H, &S, &L);
		DuiLib::CPaintManagerUI::SetHSL(true, H, (static_cast<DuiLib::CSliderUI*>(pMsg->pSender))->GetValue(), L);
	}

	return true;
}

bool CFrameWindowWnd::OnLChanged(void* param)
{
	DuiLib::TNotifyUI* pMsg = (DuiLib::TNotifyUI*)param;

	if (pMsg->sType == _T("valuechanged")) {
		short H, S, L;
		DuiLib::CPaintManagerUI::GetHSL(&H, &S, &L);
		DuiLib::CPaintManagerUI::SetHSL(true, H, S, (static_cast<DuiLib::CSliderUI*>(pMsg->pSender))->GetValue());
	}

	return true;
}

bool CFrameWindowWnd::OnAlphaChanged(void* param)
{
	DuiLib::TNotifyUI* pMsg = (DuiLib::TNotifyUI*)param;

	if (pMsg->sType == _T("valuechanged"))
	{
		m_pm.SetOpacity((static_cast<DuiLib::CSliderUI*>(pMsg->pSender))->GetValue());
	}

	return true;
}

void CFrameWindowWnd::OnPrepare()
{
	DuiLib::CSliderUI* pSilder = static_cast<DuiLib::CSliderUI*>(m_pm.FindControl(_T("alpha_controlor")));
	if (pSilder) pSilder->OnNotify += MakeDelegate(this, &CFrameWindowWnd::OnAlphaChanged);
	pSilder = static_cast<DuiLib::CSliderUI*>(m_pm.FindControl(_T("h_controlor")));
	if (pSilder) pSilder->OnNotify += MakeDelegate(this, &CFrameWindowWnd::OnHChanged);
	pSilder = static_cast<DuiLib::CSliderUI*>(m_pm.FindControl(_T("s_controlor")));
	if (pSilder) pSilder->OnNotify += MakeDelegate(this, &CFrameWindowWnd::OnSChanged);
	pSilder = static_cast<DuiLib::CSliderUI*>(m_pm.FindControl(_T("l_controlor")));
	if (pSilder) pSilder->OnNotify += MakeDelegate(this, &CFrameWindowWnd::OnLChanged);
}

void CFrameWindowWnd::Notify(DuiLib::TNotifyUI& msg)
{
	if (msg.sType == _T("windowinit"))
	{
		OnPrepare();
	}
	else if (msg.sType == _T("click"))
	{
		if (msg.pSender->GetName() == _T("insertimagebtn"))
		{
			DuiLib::CRichEditUI* pRich = static_cast<DuiLib::CRichEditUI*>(m_pm.FindControl(_T("testrichedit")));
			if (pRich)
			{
				pRich->RemoveAll();
			}
		}
		else if (msg.pSender->GetName() == _T("changeskinbtn"))
		{
			if (DuiLib::CPaintManagerUI::GetResourcePath() == DuiLib::CPaintManagerUI::GetInstancePath())
			{
				DuiLib::CPaintManagerUI::SetResourcePath(DuiLib::CPaintManagerUI::GetInstancePath() + _T("skin\\FlashRes"));
			}
			else
			{
				DuiLib::CPaintManagerUI::SetResourcePath(DuiLib::CPaintManagerUI::GetInstancePath());
			}

			DuiLib::CPaintManagerUI::ReloadSkin();
		}
	}
}

LRESULT CFrameWindowWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_CREATE)
	{
		m_pm.Init(m_hWnd);
		DuiLib::CDialogBuilder builder;
		DuiLib::CControlUI* pRoot = builder.Create(_T("testapp.xml"), (UINT)0, NULL, &m_pm);
		ASSERT(pRoot && "Failed to parse XML");
		m_pm.AttachDialog(pRoot);
		m_pm.AddNotifier(this);

		m_pWndShadow = new CWndShadow;
		m_pWndShadow->Create(m_hWnd);
		RECT rcCorner = { 3,3,4,4 };
		RECT rcHoleOffset = { 0,0,0,0 };
		m_pWndShadow->SetImage(_T("LeftWithFill.png"), rcCorner, rcHoleOffset);

		DWMNCRENDERINGPOLICY ncrp = DWMNCRP_ENABLED;
		SetWindowAttribute(m_hWnd, DWMWA_TRANSITIONS_FORCEDISABLED, &ncrp, sizeof(ncrp));

		//DWM_BLURBEHIND bb = {0};
		//bb.dwFlags = DWM_BB_ENABLE;
		//bb.fEnable = true;
		//bb.hRgnBlur = NULL;
		//EnableBlurBehindWindow(m_hWnd, bb);

		//DWM_MARGINS margins = {-1}/*{0,0,0,25}*/;
		//ExtendFrameIntoClientArea(m_hWnd, margins);

		Init();
		return 0;
	}
	else if (uMsg == WM_DESTROY)
	{
		::PostQuitMessage(0L);
	}
	else if (uMsg == WM_NCACTIVATE)
	{
		if (!::IsIconic(*this)) return (wParam == 0) ? TRUE : FALSE;
	}

	LRESULT lRes = 0;
	if (m_pm.MessageHandler(uMsg, wParam, lParam, lRes))
	{
		return lRes;
	}

	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}
