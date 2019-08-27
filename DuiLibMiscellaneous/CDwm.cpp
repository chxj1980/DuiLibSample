
#include <Windows.h>
#include <tchar.h>

#include "CDwm.h"

CDwm::CDwm()
{
	static HINSTANCE hDwmInstance = ::LoadLibrary(_T("dwmapi.dll"));
	if (hDwmInstance != nullptr) {
		fnDwmEnableComposition = (FN_DWM_ENABLE_COMPOSITION) ::GetProcAddress(hDwmInstance, "DwmEnableComposition");
		fnDwmIsCompositionEnabled = (FN_DWN_IS_COMPOSITION_ENABLED) ::GetProcAddress(hDwmInstance, "DwmIsCompositionEnabled");
		fnDwmEnableBlurBehindWindow = (FN_ENABLE_BLUR_BEHIND_WINDOW) ::GetProcAddress(hDwmInstance, "DwmEnableBlurBehindWindow");
		fnDwmExtendFrameIntoClientArea = (FN_DWM_EXTEND_FRAME_INTO_CLIENT_AREA) ::GetProcAddress(hDwmInstance, "DwmExtendFrameIntoClientArea");
		fnDwmSetWindowAttribute = (FN_DWM_SET_WINDOW_ATTRIBUTE) ::GetProcAddress(hDwmInstance, "DwmSetWindowAttribute");
	}
	else {
		fnDwmEnableComposition = nullptr;
		fnDwmIsCompositionEnabled = nullptr;
		fnDwmEnableBlurBehindWindow = nullptr;
		fnDwmExtendFrameIntoClientArea = nullptr;
		fnDwmSetWindowAttribute = nullptr;
	}
}

::BOOL CDwm::IsCompositionEnabled() const
{
	::HRESULT hr = E_NOTIMPL;
	::BOOL bRet = FALSE;

	if (fnDwmIsCompositionEnabled != nullptr)
	{
		fnDwmIsCompositionEnabled(&bRet);
	}

	return SUCCEEDED(hr) && bRet;
}

::BOOL CDwm::EnableComposition(::UINT uEnable)
{
	::BOOL bRet = FALSE;

	if (fnDwmEnableComposition != nullptr)
	{
		bRet = SUCCEEDED(fnDwmEnableComposition(uEnable));
	}

	return bRet;
}

::BOOL CDwm::EnableBlurBehindWindow(::HWND hWnd)
{
	::BOOL bRet = FALSE;

	if (fnDwmEnableBlurBehindWindow != NULL)
	{
		DWM_BLUR_BEHIND bb = { 0 };
		bb.dwFlags = DWM_BB_ENABLE;
		bb.bEnable = TRUE;
		bRet = SUCCEEDED(fnDwmEnableBlurBehindWindow(hWnd, &bb));
	}

	return bRet;
}

::BOOL CDwm::EnableBlurBehindWindow(::HWND hWnd, const DWM_BLUR_BEHIND& bb)
{
	::BOOL bRet = FALSE;
	if (fnDwmEnableBlurBehindWindow != NULL) {
		bRet = SUCCEEDED(fnDwmEnableBlurBehindWindow(hWnd, &bb));
	}
	return bRet;
}

::BOOL CDwm::ExtendFrameIntoClientArea(::HWND hWnd, const DWM_MARGINS& Margins)
{
	::BOOL bRet = FALSE;

	if (fnDwmEnableComposition != NULL)
	{
		bRet = SUCCEEDED(fnDwmExtendFrameIntoClientArea(hWnd, &Margins));
	}

	return bRet;
}

::BOOL CDwm::SetWindowAttribute(::HWND hwnd, ::DWORD dwAttribute, ::LPCVOID pvAttribute, ::DWORD cbAttribute)
{
	::BOOL bRet = FALSE;
	if (fnDwmSetWindowAttribute != NULL)
	{
		bRet = SUCCEEDED(fnDwmSetWindowAttribute(hwnd, dwAttribute, pvAttribute, cbAttribute));
	}
	return bRet;
}
