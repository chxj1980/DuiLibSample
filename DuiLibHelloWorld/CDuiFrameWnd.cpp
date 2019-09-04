#include "CDuiFrameWnd.h"

LPCTSTR CDuiFrameWnd::GetWindowClassName() const
{
	return _T("DUIMainFrame");
}

void CDuiFrameWnd::Notify(DuiLib::TNotifyUI & msg)
{
	if (msg.sType == _T("click"))
	{
		if (msg.pSender->GetName() == _T("btnHello"))
		{
			MessageBox(NULL, _T("woshianniu"), _T("dianjileanniu"), NULL);
		}
	}
}

LRESULT CDuiFrameWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;

	if (uMsg == WM_CREATE)
	{
		DuiLib::CControlUI *pWnd = new DuiLib::CButtonUI;
		pWnd->SetName("btnHello");
		pWnd->SetText(_T("Hello World"));   // 设置文字
		pWnd->SetBkColor(0xFF00FF00);       // 设置背景色

		m_PaintManager.Init(m_hWnd);
		m_PaintManager.AttachDialog(pWnd);
		m_PaintManager.AddNotifier(this);
		return lRes;
	}
	else if (uMsg == WM_NCACTIVATE)
	{
		if (!IsIconic(m_hWnd))
		{
			return (wParam == 0) ? TRUE : FALSE;
		}
	}
	else if (uMsg == WM_NCCALCSIZE)
	{
		return 0;
	}
	else if (uMsg == WM_NCPAINT)
	{
		return 0;
	}

	if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes))
	{
		return lRes;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}
