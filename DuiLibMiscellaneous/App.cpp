
#include <cstdlib>

#include <Windows.h>
#include <iostream>

#include <UIlib.h>

#include "CFrameWindowWnd.h"


int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE /*hPrevInstance*/, _In_ LPSTR /*lpCmdLine*/, _In_ int nCmdShow)
{
	DuiLib::CPaintManagerUI::SetInstance(hInstance);
	DuiLib::CPaintManagerUI::SetResourcePath(DuiLib::CPaintManagerUI::GetInstancePath());

	::HRESULT hr = ::CoInitialize(nullptr);
	if (FAILED(hr))
	{
		std::cout << "Failed to execute CoInitialize()." << std::endl;
		return EXIT_FAILURE;
	}

	::CWndShadow::Initialize(hInstance);

	::CFrameWindowWnd* pFrame = new ::CFrameWindowWnd();
	if (pFrame == nullptr)
	{
		return EXIT_FAILURE;
	}

	pFrame->Create(NULL, _T("����һ����򵥵Ĳ�����exe���޸�test1.xml�Ϳ��Կ���Ч��"), UI_WNDSTYLE_FRAME | WS_CLIPCHILDREN, WS_EX_WINDOWEDGE);
	pFrame->CenterWindow();
	pFrame->ShowWindow(true);
	DuiLib::CPaintManagerUI::MessageLoop();

	::CoUninitialize();

	return EXIT_SUCCESS;
}