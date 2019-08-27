
#include <UIlib.h>

#include "CDwm.h"
#include "CDPI.h"

#pragma once
class CFrameWindowWnd : public DuiLib::CWindowWnd, public DuiLib::INotifyUI, public CDwm, public CDPI
{
public:
	DuiLib::CPaintManagerUI m_pm;
	::CWndShadow* m_pWndShadow;

public:
	CFrameWindowWnd();
	LPCTSTR GetWindowClassName() const;
	UINT GetClassStyle() const;
	void OnFinalMessage(HWND /*hWnd*/);

	void Init();
	bool OnHChanged(void* param);
	bool OnSChanged(void* param);
	bool OnLChanged(void* param);
	bool OnAlphaChanged(void* param);
	void OnPrepare();
	void Notify(DuiLib::TNotifyUI& msg);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

