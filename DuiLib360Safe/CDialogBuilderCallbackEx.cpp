
#include <tchar.h>
#include "CDialogBuilderCallbackEx.h"
#include "ComputerExamineUI.h"

DuiLib::CControlUI* CDialogBuilderCallbackEx::CreateControl(LPCTSTR pstrClass)
{
	return _tcscmp(pstrClass, _T("ComputerExamine")) == 0 ? new ComputerExamineUI : nullptr;
}
