////// App.cpp : Defines the entry point for the application.
//////
////
////#include "stdafx.h"
////
//
//#undef _UNICODE
//#include <tchar.h>
//
//#include "UIBase.h"
//#include "UIControl.h"
//
//using namespace DuiLib;
//
//class CFrameWindowWnd : public CWindowWnd, public INotifyUI
//{
//public:
//	CFrameWindowWnd() { };
//	LPCTSTR GetWindowClassName() const { return _T("UIMainFrame"); };
//	UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; };
//	void OnFinalMessage(HWND /*hWnd*/) { delete this; };
//
//	void Init() { }
//
//	bool OnHChanged(void* param) {
//		TNotifyUI* pMsg = (TNotifyUI*)param;
//		if (pMsg->sType == _T("valuechanged")) {
//			short H, S, L;
//			CPaintManagerUI::GetHSL(&H, &S, &L);
//			CPaintManagerUI::SetHSL(true, (static_cast<CSliderUI*>(pMsg->pSender))->GetValue(), S, L);
//		}
//		return true;
//	}
//
//	bool OnSChanged(void* param) {
//		TNotifyUI* pMsg = (TNotifyUI*)param;
//		if (pMsg->sType == _T("valuechanged")) {
//			short H, S, L;
//			CPaintManagerUI::GetHSL(&H, &S, &L);
//			CPaintManagerUI::SetHSL(true, H, (static_cast<CSliderUI*>(pMsg->pSender))->GetValue(), L);
//		}
//		return true;
//	}
//
//	bool OnLChanged(void* param) {
//		TNotifyUI* pMsg = (TNotifyUI*)param;
//		if (pMsg->sType == _T("valuechanged")) {
//			short H, S, L;
//			CPaintManagerUI::GetHSL(&H, &S, &L);
//			CPaintManagerUI::SetHSL(true, H, S, (static_cast<CSliderUI*>(pMsg->pSender))->GetValue());
//		}
//		return true;
//	}
//
//	bool OnAlphaChanged(void* param) {
//		TNotifyUI* pMsg = (TNotifyUI*)param;
//		if (pMsg->sType == _T("valuechanged")) {
//			m_pm.SetTransparent((static_cast<CSliderUI*>(pMsg->pSender))->GetValue());
//		}
//		return true;
//	}
//
//	void OnPrepare()
//	{
//		CSliderUI* pSilder = static_cast<CSliderUI*>(m_pm.FindControl(_T("alpha_controlor")));
//		if (pSilder) pSilder->OnNotify += MakeDelegate(this, &CFrameWindowWnd::OnAlphaChanged);
//		pSilder = static_cast<CSliderUI*>(m_pm.FindControl(_T("h_controlor")));
//		if (pSilder) pSilder->OnNotify += MakeDelegate(this, &CFrameWindowWnd::OnHChanged);
//		pSilder = static_cast<CSliderUI*>(m_pm.FindControl(_T("s_controlor")));
//		if (pSilder) pSilder->OnNotify += MakeDelegate(this, &CFrameWindowWnd::OnSChanged);
//		pSilder = static_cast<CSliderUI*>(m_pm.FindControl(_T("l_controlor")));
//		if (pSilder) pSilder->OnNotify += MakeDelegate(this, &CFrameWindowWnd::OnLChanged);
//	}
//
//	void Notify(TNotifyUI& msg)
//	{
//		if (msg.sType == _T("windowinit")) OnPrepare();
//		else if (msg.sType == _T("click")) {
//			if (msg.pSender->GetName() == _T("insertimagebtn")) {
//				CRichEditUI* pRich = static_cast<CRichEditUI*>(m_pm.FindControl(_T("testrichedit")));
//				if (pRich) {
//					pRich->RemoveAll();
//				}
//			}
//			else if (msg.pSender->GetName() == _T("changeskinbtn")) {
//				if (CPaintManagerUI::GetResourcePath() == CPaintManagerUI::GetInstancePath())
//					CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath() + _T("skin\\FlashRes"));
//				else
//					CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
//				CPaintManagerUI::ReloadSkin();
//			}
//		}
//	}
//
//	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
//	{
//		if (uMsg == WM_CREATE) {
//			m_pm.Init(m_hWnd);
//			CDialogBuilder builder;
//			CControlUI* pRoot = builder.Create(_T("test1.xml"), (UINT)0, NULL, &m_pm);
//			ASSERT(pRoot && "Failed to parse XML");
//			m_pm.AttachDialog(pRoot);
//			m_pm.AddNotifier(this);
//			Init();
//			return 0;
//		}
//		else if (uMsg == WM_DESTROY) {
//			::PostQuitMessage(0L);
//		}
//		else if (uMsg == WM_ERASEBKGND) {
//			return 1;
//		}
//		LRESULT lRes = 0;
//		if (m_pm.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
//		return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
//	}
//
//public:
//	CPaintManagerUI m_pm;
//};
//
//
//int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
//{
//	CPaintManagerUI::SetInstance(hInstance);
//	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
//
//	HRESULT Hr = ::CoInitialize(NULL);
//	if (FAILED(Hr)) return 0;
//
//	CFrameWindowWnd* pFrame = new CFrameWindowWnd();
//	if (pFrame == NULL) return 0;
//	pFrame->Create(NULL, _T("这是一个最简单的测试用exe，修改test1.xml就可以看到效果"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
//	pFrame->CenterWindow();
//	pFrame->ShowWindow(true);
//	CPaintManagerUI::MessageLoop();
//
//	::CoUninitialize();
//	return 0;
//}



//#include <UIlib.h>


#include "UIBase.h"
#include "UIControl.h"
#include "UILabel.h"

#undef _UNICODE
#include <tchar.h>

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
