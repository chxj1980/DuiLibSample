
#include <Windows.h>
#include <tchar.h>

#include "CDPI.h"

CDPI::CDPI()
{
	m_nScaleFactor = 0;
	m_nScaleFactorSDA = 0;
	m_Awareness = PROCESS_DPI_UNAWARE;

	static HINSTANCE hUser32Instance = ::LoadLibrary(_T("User32.dll"));
	static HINSTANCE hShcoreInstance = ::LoadLibrary(_T("Shcore.dll"));

	fnSetProcessDPIAware = hUser32Instance != nullptr ? (FN_SET_PROCESS_DPI_AWARE)::GetProcAddress(hUser32Instance, "SetProcessDPIAware") : nullptr;
	fnSetProcessDpiAwareness = hShcoreInstance != nullptr ? (FN_SET_PROCESS_DPI_AWARENESS) ::GetProcAddress(hShcoreInstance, "SetProcessDpiAwareness") : nullptr;
	fnGetDpiForMonitor = hShcoreInstance != nullptr ? (FN_GET_DPI_FOR_MONITOR) ::GetProcAddress(hShcoreInstance, "GetDpiForMonitor") : nullptr;

	if (fnGetDpiForMonitor != NULL)
	{
		UINT dpix = 0, dpiy = 0;
		HRESULT hr = E_FAIL;
		POINT pt = { 1, 1 };
		HMONITOR hMonitor = ::MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);
		hr = fnGetDpiForMonitor(hMonitor, MDT_EFFECTIVE_DPI, &dpix, &dpiy);
		SetScale(dpix);
	}
	else
	{
		UINT dpix = 0;
		HDC hDC = ::GetDC(::GetDesktopWindow());
		dpix = GetDeviceCaps(hDC, LOGPIXELSX);
		::ReleaseDC(::GetDesktopWindow(), hDC);
		SetScale(dpix);
	}

	SetAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
}

PROCESS_DPI_AWARENESS CDPI::GetAwareness()
{
	return m_Awareness;
}

int CDPI::Scale(int x)
{
	switch (m_Awareness)
	{
	case PROCESS_DPI_UNAWARE:
		return x;
	case PROCESS_SYSTEM_DPI_AWARE:
		return MulDiv(x, m_nScaleFactorSDA, 100);
	default:
		return MulDiv(x, m_nScaleFactor, 100);
	}
}

UINT CDPI::GetScale()
{
	switch (m_Awareness)
	{
	case PROCESS_DPI_UNAWARE:
		return 100;
	case PROCESS_SYSTEM_DPI_AWARE:
		return m_nScaleFactorSDA;
	default:
		return m_nScaleFactor;
	}
}


void CDPI::ScaleRect(__inout RECT* pRect)
{
	pRect->left = Scale(pRect->left);
	pRect->right = Scale(pRect->right);
	pRect->top = Scale(pRect->top);
	pRect->bottom = Scale(pRect->bottom);
}

void CDPI::ScalePoint(__inout POINT* pPoint)
{
	pPoint->x = Scale(pPoint->x);
	pPoint->y = Scale(pPoint->y);
}

void CDPI::OnDPIChanged(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	SetScale(LOWORD(wParam));
	RECT* const prcNewWindow = (RECT*)lParam;

	::SetWindowPos(hWnd,
		NULL,
		prcNewWindow->left,
		prcNewWindow->top,
		prcNewWindow->right - prcNewWindow->left,
		prcNewWindow->bottom - prcNewWindow->top,
		SWP_NOZORDER | SWP_NOACTIVATE);
}

void CDPI::SetScale(__in UINT iDPI)
{
	m_nScaleFactor = MulDiv(iDPI, 100, 96);
	if (m_nScaleFactorSDA == 0) m_nScaleFactorSDA = m_nScaleFactor;
}

BOOL CDPI::SetAwareness(PROCESS_DPI_AWARENESS value)
{
	if (fnSetProcessDpiAwareness != NULL)
	{
		HRESULT Hr = E_NOTIMPL;
		Hr = fnSetProcessDpiAwareness(value);
		if (Hr == S_OK)
		{
			m_Awareness = value;
		}

		return Hr == S_OK;
	}
	else
	{
		if (fnSetProcessDPIAware)
		{
			BOOL bRet = fnSetProcessDPIAware();
			if (bRet)
			{
				m_Awareness = PROCESS_SYSTEM_DPI_AWARE;
			}
			return bRet;
		}
	}

	return FALSE;
}
