
#include <UIlib.h>

class CFrameWindowWnd : public DuiLib::CWindowWnd, public DuiLib::INotifyUI
{
public:
	DuiLib::CPaintManagerUI m_pm;

	CFrameWindowWnd();

    //�̳и��� CWindowWnd
	LPCTSTR GetWindowClassName() const;
    //�̳и��� CWindowWnd
	UINT GetClassStyle() const;
    //�̳и��� CWindowWnd
	void OnFinalMessage(HWND /*hWnd*/);

    //�̳нӿ� INotifyUI
	void Notify(DuiLib::TNotifyUI& msg);
    //�̳и��� CWindowWnd
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};