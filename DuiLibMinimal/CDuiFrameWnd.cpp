#include "CDuiFrameWnd.h"

LPCTSTR CDuiFrameWnd::GetWindowClassName() const
{
	return _T("DUIMainFrame");
}

void CDuiFrameWnd::Notify(DuiLib::TNotifyUI & msg)
{
	//
}

LRESULT CDuiFrameWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;

	if (uMsg == WM_CREATE)
	{
		DuiLib::CControlUI *pWnd = new DuiLib::CButtonUI;
		pWnd->SetText(_T("Hello World"));   // 设置文字
		pWnd->SetBkColor(0xFF00FF00);       // 设置背景色

		m_PaintManager.Init(m_hWnd);
		m_PaintManager.AttachDialog(pWnd);
		return lRes;
	}

	if (m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes))
	{
		return lRes;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}
