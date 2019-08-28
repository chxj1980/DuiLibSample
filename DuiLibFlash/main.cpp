
#include <cstdlib>
#include <Windows.h>
#include <UIlib.h>

#include "CFrameWnd.h"

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE /*hPrevInstance*/, _In_ LPSTR /*lpCmdLine*/, _In_ int nCmdShow)
{
	DuiLib::CPaintManagerUI::SetInstance(hInstance);
	DuiLib::CPaintManagerUI::SetResourcePath(DuiLib::CPaintManagerUI::GetInstancePath());

	if (FAILED(::CoInitialize(nullptr)))
	{
		return EXIT_FAILURE;
	}

	CFrameWnd* pFrame = new CFrameWnd();
	if (pFrame == NULL) return 0;
	pFrame->Create(NULL, NULL, UI_WNDSTYLE_DIALOG, 0);
	pFrame->CenterWindow();
	pFrame->ShowWindow(true);
	DuiLib::CPaintManagerUI::MessageLoop();

	::CoUninitialize();

	return EXIT_SUCCESS;
}