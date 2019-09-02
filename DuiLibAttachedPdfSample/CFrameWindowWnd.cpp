
#include "CFrameWindowWnd.h"

CFrameWindowWnd::CFrameWindowWnd()
{
	//
}

LPCTSTR CFrameWindowWnd::GetWindowClassName() const
{
	return _T("UIMainFrame");
}

UINT CFrameWindowWnd::GetClassStyle() const
{
	return UI_CLASSSTYLE_FRAME | CS_DBLCLKS;
}

void CFrameWindowWnd::OnFinalMessage(HWND /*hWnd*/)
{
	delete this;
}

void CFrameWindowWnd::Notify(DuiLib::TNotifyUI& msg)
{
	if (msg.sType == _T("click"))
	{
		if (msg.pSender->GetName() == _T("closebtn"))
		{
			Close();
		}
	}
}

LRESULT CFrameWindowWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_CREATE)
	{
		m_pm.Init(m_hWnd);
		DuiLib::CControlUI* pButton = new DuiLib::CButtonUI;
		pButton->SetName(_T("closebtn"));
		pButton->SetBkColor(0xFFFF0000);
		m_pm.AttachDialog(pButton);
		m_pm.AddNotifier(this);
		return 0;
	}
	else if (uMsg == WM_DESTROY)
	{
		::PostQuitMessage(0);
	}

	LRESULT lRes = 0;
	if (m_pm.MessageHandler(uMsg, wParam, lParam, lRes))
	{
		return lRes;
	}
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}
