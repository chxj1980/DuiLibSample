
#include <windef.h>

#include "DefShellScaling.h"

#pragma once
class CDPI
{
public:
	typedef BOOL(WINAPI* FN_SET_PROCESS_DPI_AWARE)(VOID);
	typedef HRESULT(WINAPI* FN_SET_PROCESS_DPI_AWARENESS)(PROCESS_DPI_AWARENESS);
	typedef HRESULT(WINAPI* FN_GET_DPI_FOR_MONITOR)(HMONITOR, Monitor_DPI_Type, UINT*, UINT*);

	FN_SET_PROCESS_DPI_AWARE fnSetProcessDPIAware; // vista,win7
	FN_SET_PROCESS_DPI_AWARENESS fnSetProcessDpiAwareness; // win8+
	FN_GET_DPI_FOR_MONITOR fnGetDpiForMonitor; //

	CDPI();
	PROCESS_DPI_AWARENESS GetAwareness();
	int  Scale(int x);
	UINT GetScale();
	void ScaleRect(__inout RECT* pRect);
	void ScalePoint(__inout POINT* pPoint);
	void OnDPIChanged(HWND hWnd, WPARAM wParam, LPARAM lParam);

private:
	UINT m_nScaleFactor;
	UINT m_nScaleFactorSDA;
	PROCESS_DPI_AWARENESS m_Awareness;
	void SetScale(__in UINT iDPI);
	BOOL SetAwareness(PROCESS_DPI_AWARENESS value);
};

