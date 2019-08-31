
#include <UIlib.h>

class DeskListUI : public DuiLib::CTileLayoutUI
{
private:
	UINT m_uButtonState;
	POINT m_ptLastMouse;
	LONG m_dwDelayDeltaY;
	DWORD m_dwDelayNum;
	DWORD m_dwDelayLeft;

public:
	enum { SCROLL_TIMERID = 10 };

	DeskListUI();
	void DoEvent(DuiLib::TEventUI &event);
};