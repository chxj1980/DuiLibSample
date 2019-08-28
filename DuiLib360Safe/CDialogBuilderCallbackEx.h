
#include <UIlib.h>

class CDialogBuilderCallbackEx : public DuiLib::IDialogBuilderCallback
{
public:
	DuiLib::CControlUI* CreateControl(LPCTSTR pstrClass);
};