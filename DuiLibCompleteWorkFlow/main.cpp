
#include <Windows.h>
#include <UIlib.h>

class MyClass : public DuiLib::CWindowWnd, public DuiLib::INotifyUI
{
public:
	MyClass();
	~MyClass();

	virtual LPCTSTR GetWindowClassName() const;
	virtual void    Notify(DuiLib::TNotifyUI& msg);

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	DuiLib::CPaintManagerUI m_pm;

private:

};

MyClass::MyClass()
{
}

MyClass::~MyClass()
{
}

LPCTSTR MyClass::GetWindowClassName() const
{
	return _T("DuiLib 完整示例");
}

void MyClass::Notify(DuiLib::TNotifyUI& msg)
{
	if (msg.sType == _T("click"))
	{
		if (msg.pSender->GetName() == _T("buttonUI1"))
		{
			DuiLib::CEditUI* pEditNum1 = static_cast<DuiLib::CEditUI*>(m_pm.FindControl(_T("editUI1")));
			DuiLib::CEditUI* pEditNum2 = static_cast<DuiLib::CEditUI*>(m_pm.FindControl(_T("editUI2")));
			DuiLib::CLabelUI* pLblRes = static_cast<DuiLib::CLabelUI*>(m_pm.FindControl(_T("labelUI1")));

			if (pEditNum1->GetText().IsEmpty() || pEditNum2->GetText().IsEmpty())
			{
				MessageBox(NULL, TEXT("请输入两个加数！"), TEXT("不合法输入"), MB_OK);
				return;
			}

#ifdef _UNICODE
			int add1 = _wtof(pEditNum1->GetText().GetData());
			int add2 = _wtof(pEditNum2->GetText().GetData());
#else
			int add1 = atof(pEditNum1->GetText().GetData());
			int add2 = atof(pEditNum2->GetText().GetData());
#endif // _UNICODE
			int res = add1 + add2;

			TCHAR temp1[2 * sizeof((pEditNum1->GetText()).GetData())];//求和后的值可能装不下
#ifdef _UNICODE
			pLblRes->SetText(_itow(res, temp1, 10));
#else
			pLblRes->SetText(_itoa(res, temp1, 10));
#endif
		}
	}
}

LRESULT MyClass::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;

	if (uMsg == WM_CREATE)
	{
		//DuiLib::CControlUI* pWnd = new DuiLib::CButtonUI;
		//pWnd->SetName("btnHello");
		//pWnd->SetText(_T("Hello World"));   // 设置文字
		//pWnd->SetBkColor(0xFF00FF00);       // 设置背景色

		//m_PaintManager.Init(m_hWnd);
		//m_PaintManager.AttachDialog(pWnd);

		m_pm.Init(m_hWnd);
		DuiLib::CDialogBuilder builder;
		DuiLib::CControlUI* pRoot = builder.Create(_T("UISkin1.xml"), (UINT)0, NULL, &m_pm);
		//ASSERT(pRoot && "Failed to parse XML");
		m_pm.AttachDialog(pRoot);
		m_pm.AddNotifier(this);
		return lRes;
	}
	//else if (uMsg == WM_NCACTIVATE)
	//{
	//	if (!IsIconic(m_hWnd))
	//	{
	//		return (wParam == 0) ? TRUE : FALSE;
	//	}
	//}
	//else if (uMsg == WM_NCCALCSIZE)
	//{
	//	return 0;
	//}
	//else if (uMsg == WM_NCPAINT)
	//{
	//	return 0;
	//}
	else if (uMsg == WM_DESTROY)
	{
		PostQuitMessage(0L);
	}

	if (m_pm.MessageHandler(uMsg, wParam, lParam, lRes))
	{
		return lRes;
	}

	return __super::HandleMessage(uMsg, wParam, lParam);
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE /*hPrevInstance*/, _In_ PSTR /*lpCmdLine*/, _In_ int iCmdShow)
{
	DuiLib::CPaintManagerUI::SetInstance(hInstance);
	DuiLib::CPaintManagerUI::SetResourcePath(DuiLib::CPaintManagerUI::GetInstancePath());

	if (FAILED(CoInitialize(NULL)))
	{
		return EXIT_FAILURE;
	}

	MyClass* pFrame = new MyClass();
	if (!pFrame)
	{
		return EXIT_FAILURE;
	}

	pFrame->Create(NULL, _T("简陋的计算器"), UI_WNDSTYLE_FRAME | WS_CLIPCHILDREN, WS_EX_WINDOWEDGE);
	pFrame->CenterWindow();
	pFrame->ShowWindow(true);

	DuiLib::CPaintManagerUI::MessageLoop();

	CoUninitialize();

	return EXIT_SUCCESS;
}
