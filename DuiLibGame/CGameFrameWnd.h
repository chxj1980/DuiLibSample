
#include <UIlib.h>

class CGameFrameWnd : public DuiLib::CWindowWnd, public DuiLib::INotifyUI, public DuiLib::IListCallbackUI
{
private:
	DuiLib::CButtonUI* m_pRestoreBtn;
	DuiLib::CButtonUI* m_pCloseBtn;
	DuiLib::CButtonUI* m_pMaxBtn;
	DuiLib::CButtonUI* m_pMinBtn;

public:
	DuiLib::CPaintManagerUI m_pm;

public:
	CGameFrameWnd();
};