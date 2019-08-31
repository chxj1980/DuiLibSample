
#include <Windows.h>

#include <UIlib.h>

#include "CGameFrameWnd.h"


int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE /*hPrevInstance*/, _In_ LPSTR /*lpCmdLine*/, _In_ int nCmdShow)
{
	DuiLib::CPaintManagerUI::SetInstance(hInstance);
	DuiLib::CPaintManagerUI::SetResourcePath(DuiLib::CPaintManagerUI::GetInstancePath());
	DuiLib::CPaintManagerUI::SetResourceZip(_T("GameRes.zip"));

	if (FAILED(::CoInitialize(nullptr)))
	{
		return EXIT_FAILURE;
	}

	CGameFrameWnd* pFrame = new CGameFrameWnd();
	if (pFrame == NULL) return 0;
	pFrame->Create(NULL, _T(""), UI_WNDSTYLE_FRAME, 0L, 0, 0, 1024, 738);
	pFrame->CenterWindow();
	::ShowWindow(*pFrame, SW_SHOWMAXIMIZED);

	DuiLib::CPaintManagerUI::MessageLoop();

	::CoUninitialize();
	return EXIT_SUCCESS;
}