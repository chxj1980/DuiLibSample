
#include <tchar.h>
#include "UIBase.h"
#include "UIControl.h"
#include "UILabel.h"

class CDuiFrameWnd : public DuiLib::CWindowWnd, public DuiLib::INotifyUI
{
protected:
	DuiLib::CPaintManagerUI m_PaintManager;

public:
	virtual LPCTSTR GetWindowClassName() const;
	virtual void    Notify(DuiLib::TNotifyUI& msg);

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

LPCTSTR CDuiFrameWnd::GetWindowClassName() const
{
	return _T("DUIMainFrame");
}

void CDuiFrameWnd::Notify(DuiLib::TNotifyUI& msg)
{
	//
}

LRESULT CDuiFrameWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;

	if (uMsg == WM_CREATE)
	{
		DuiLib::CControlUI* pWnd = new DuiLib::CLabelUI;
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


int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE /*hPrevInstance*/, _In_ LPTSTR lpCmdLine, _In_ int nCmdShow)
{
	DuiLib::CPaintManagerUI::SetInstance(hInstance);

	CDuiFrameWnd duiFrame;
	duiFrame.Create(NULL, _T("DUIWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	duiFrame.ShowModal();

	return EXIT_SUCCESS;
}
