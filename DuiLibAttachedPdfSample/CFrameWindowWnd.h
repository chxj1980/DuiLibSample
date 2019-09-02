
#include <UIlib.h>

class CFrameWindowWnd : public DuiLib::CWindowWnd, public DuiLib::INotifyUI
{
public:
	DuiLib::CPaintManagerUI m_pm;

	CFrameWindowWnd();

    //ºÃ≥–∏∏¿‡ CWindowWnd
	LPCTSTR GetWindowClassName() const;
    //ºÃ≥–∏∏¿‡ CWindowWnd
	UINT GetClassStyle() const;
    //ºÃ≥–∏∏¿‡ CWindowWnd
	void OnFinalMessage(HWND /*hWnd*/);

    //ºÃ≥–Ω”ø⁄ INotifyUI
	void Notify(DuiLib::TNotifyUI& msg);
    //ºÃ≥–∏∏¿‡ CWindowWnd
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};