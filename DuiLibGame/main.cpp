
#include <Windows.h>

#include <UIlib.h>


int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE /*hPrevInstance*/, _In_ LPSTR /*lpCmdLine*/, _In_ int nCmdShow)
{
	DuiLib::CPaintManagerUI::SetInstance(hInstance);
	DuiLib::CPaintManagerUI::SetResourcePath(DuiLib::CPaintManagerUI::GetInstancePath());
	DuiLib::CPaintManagerUI::SetResourceZip(_T("GameRes.zip"));

	if (FAILED(::CoInitialize(nullptr)))
	{
		return EXIT_FAILURE;
	}



	DuiLib::CPaintManagerUI::MessageLoop();

	::CoUninitialize();
	return EXIT_SUCCESS;
}