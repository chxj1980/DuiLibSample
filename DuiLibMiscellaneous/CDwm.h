
#include <windef.h>

#include "DefDwm.h"

#pragma once
class CDwm
{
public:
	typedef HRESULT(WINAPI* FN_DWM_ENABLE_COMPOSITION)(UINT);
	typedef HRESULT(WINAPI* FN_DWN_IS_COMPOSITION_ENABLED)(LPBOOL);
	typedef HRESULT(WINAPI* FN_ENABLE_BLUR_BEHIND_WINDOW)(HWND, CONST DWM_BLUR_BEHIND*);
	typedef HRESULT(WINAPI* FN_DWM_EXTEND_FRAME_INTO_CLIENT_AREA)(HWND, CONST DWM_MARGINS*);
	typedef HRESULT(WINAPI* FN_DWM_SET_WINDOW_ATTRIBUTE)(HWND, DWORD, LPCVOID pvAttribute, DWORD);

	FN_DWM_ENABLE_COMPOSITION fnDwmEnableComposition;
	FN_DWN_IS_COMPOSITION_ENABLED fnDwmIsCompositionEnabled;
	FN_ENABLE_BLUR_BEHIND_WINDOW fnDwmEnableBlurBehindWindow;
	FN_DWM_EXTEND_FRAME_INTO_CLIENT_AREA fnDwmExtendFrameIntoClientArea;
	FN_DWM_SET_WINDOW_ATTRIBUTE fnDwmSetWindowAttribute;

	CDwm();
	BOOL IsCompositionEnabled() const;
	BOOL EnableComposition(UINT uEnable);
	BOOL EnableBlurBehindWindow(HWND hWnd);
	BOOL EnableBlurBehindWindow(HWND hWnd, CONST DWM_BLUR_BEHIND &bb);
	BOOL ExtendFrameIntoClientArea(HWND hWnd, CONST DWM_MARGINS& Margins);
	BOOL SetWindowAttribute(HWND hwnd, DWORD dwAttribute, LPCVOID pvAttribute, DWORD cbAttribute);
};

