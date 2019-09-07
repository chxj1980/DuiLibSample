
#include <cstdlib>
#include <Windows.h>

#include "C360SafeFrameWnd.h"


int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE /*hPrevInstance*/, _In_ LPSTR /*lpCmdLine*/, _In_ int nCmdShow)
{
	DuiLib::CPaintManagerUI::SetInstance(hInstance);
	DuiLib::CPaintManagerUI::SetResourcePath(DuiLib::CPaintManagerUI::GetInstancePath());
	DuiLib::CPaintManagerUI::SetResourceZip(_T("360SafeRes.zip"));

	if (FAILED(::CoInitialize(nullptr)))
	{
		return EXIT_FAILURE;
	}

	C360SafeFrameWnd* pFrame = new C360SafeFrameWnd();
	if (pFrame == nullptr)
	{
		return EXIT_FAILURE;
	}
	pFrame->Create(nullptr, _T("360°²È«ÎÀÊ¿"), UI_WNDSTYLE_FRAME, 0L, 0, 0, 800, 572);
	pFrame->CenterWindow();
	::ShowWindow(*pFrame, SW_SHOW);

	DuiLib::CPaintManagerUI::MessageLoop();

	::CoUninitialize();

	return EXIT_SUCCESS;
}