
#include "CDialogBuilderCallbackExt.h"

#include "GameListUI.h"
#include "DeskListUI.h"

DuiLib::CControlUI *CDialogBuilderCallbackEx::CreateControl(LPCTSTR pstrClass)
{
	if (_tcscmp(pstrClass, _T("GameList")) == 0) return new GameListUI;
	else if (_tcscmp(pstrClass, _T("DeskList")) == 0) return new DeskListUI;
	return NULL;
}
