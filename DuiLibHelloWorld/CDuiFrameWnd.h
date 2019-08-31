
#include <UIlib.h>

class CDuiFrameWnd : public DuiLib::CWindowWnd, public DuiLib::INotifyUI
{
protected:
	DuiLib::CPaintManagerUI m_PaintManager;

public:
	virtual LPCTSTR GetWindowClassName() const;
	virtual void    Notify(DuiLib::TNotifyUI& msg);

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
};