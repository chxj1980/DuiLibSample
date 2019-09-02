
#include <Windows.h>
#include <UIlib.h>

#include "CFrameWindowWnd.h"

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE /*hPrevInstance*/, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	DuiLib::CPaintManagerUI::SetInstance(hInstance);
	DuiLib::CPaintManagerUI::SetResourcePath(DuiLib::CPaintManagerUI::GetInstancePath());

	CFrameWindowWnd* pFrame = new CFrameWindowWnd();
	if (pFrame == NULL)
	{
		return EXIT_FAILURE;
	}

	pFrame->Create(NULL, _T("²âÊÔ"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	pFrame->ShowWindow(true);

	DuiLib::CPaintManagerUI::MessageLoop();

	return EXIT_SUCCESS;
}