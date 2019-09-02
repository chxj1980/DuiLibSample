
#include <UIlib.h>

class CFrameWindowWnd : public DuiLib::CWindowWnd, public DuiLib::INotifyUI
{
public:
	DuiLib::CPaintManagerUI m_pm;

	CFrameWindowWnd();
	LPCTSTR GetWindowClassName() const;
	UINT GetClassStyle() const;
	void OnFinalMessage(HWND /*hWnd*/);

	void Notify(DuiLib::TNotifyUI& msg);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};