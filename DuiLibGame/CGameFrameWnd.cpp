
//#include <tchar.h>
#include <comdef.h>

#include "CGameFrameWnd.h"
#include "GameListUI.h"
#include "CLoginFrameWnd.h"
#include "DeskListUI.h"
#include "CDialogBuilderCallbackExt.h"

CGameFrameWnd::CGameFrameWnd()
{
}

LPCTSTR CGameFrameWnd::GetWindowClassName() const
{
	return _T("UIMainFrame");
}

UINT CGameFrameWnd::GetClassStyle() const
{
	return CS_DBLCLKS;
}

void CGameFrameWnd::OnFinalMessage(HWND)
{
	delete this;
}

void CGameFrameWnd::Init()
{
	m_pCloseBtn = static_cast<DuiLib::CButtonUI*>(m_pm.FindControl(_T("closebtn")));
	m_pMaxBtn = static_cast<DuiLib::CButtonUI*>(m_pm.FindControl(_T("maxbtn")));
	m_pRestoreBtn = static_cast<DuiLib::CButtonUI*>(m_pm.FindControl(_T("restorebtn")));
	m_pMinBtn = static_cast<DuiLib::CButtonUI*>(m_pm.FindControl(_T("minbtn")));

	DuiLib::CActiveXUI* pActiveXUI = static_cast<DuiLib::CActiveXUI*>(m_pm.FindControl(_T("ie")));
	if (pActiveXUI) {
		IWebBrowser2* pWebBrowser = NULL;
		pActiveXUI->GetControl(IID_IWebBrowser2, (void**)&pWebBrowser);
		if (pWebBrowser != NULL) {
			pWebBrowser->Navigate(_bstr_t(_T("https://code.google.com/p/duilib/")), NULL, NULL, NULL, NULL);
			//pWebBrowser->Navigate(L"about:blank",NULL,NULL,NULL,NULL); 
			pWebBrowser->Release();
		}
	}
}

void CGameFrameWnd::OnPrepare()
{
	GameListUI* pGameList = static_cast<GameListUI*>(m_pm.FindControl(_T("gamelist")));
	GameListUI::Node* pCategoryNode = NULL;
	GameListUI::Node* pGameNode = NULL;
	GameListUI::Node* pServerNode = NULL;
	GameListUI::Node* pRoomNode = NULL;
	pCategoryNode = pGameList->AddNode(_T("{x 4}{i gameicons.png 18 3}{x 4}�Ƽ���Ϸ"));
	for (int i = 0; i < 4; ++i)
	{
		pGameNode = pGameList->AddNode(_T("{x 4}{i gameicons.png 18 10}{x 4}���˶�����"), pCategoryNode);
		for (int i = 0; i < 3; ++i)
		{
			pServerNode = pGameList->AddNode(_T("{x 4}{i gameicons.png 18 10}{x 4}���Է�����"), pGameNode);
			for (int i = 0; i < 3; ++i)
			{
				pRoomNode = pGameList->AddNode(_T("{x 4}{i gameicons.png 18 10}{x 4}���Է���"), pServerNode);
			}
		}
	}
	pCategoryNode = pGameList->AddNode(_T("{x 4}{i gameicons.png 18 3}{x 4}����������Ϸ"));
	for (int i = 0; i < 2; ++i)
	{
		pGameList->AddNode(_T("��ȱһ"), pCategoryNode);
	}
	pCategoryNode = pGameList->AddNode(_T("{x 4}{i gameicons.png 18 3}{x 4}������Ϸ"));
	for (int i = 0; i < 8; ++i)
	{
		pGameList->AddNode(_T("˫��"), pCategoryNode);
	}
	pCategoryNode = pGameList->AddNode(_T("{x 4}{i gameicons.png 18 3}{x 4}������Ϸ"));
	for (int i = 0; i < 8; ++i)
	{
		pGameList->AddNode(_T("������"), pCategoryNode);
	}

	DuiLib::CListUI* pUserList = static_cast<DuiLib::CListUI*>(m_pm.FindControl(_T("userlist")));
	pUserList->SetTextCallback(this);
	for (int i = 0; i < 400; i++) {
		DuiLib::CListTextElementUI* pListElement = new DuiLib::CListTextElementUI;
		pUserList->Add(pListElement);
	}

	CLoginFrameWnd* pLoginFrame = new CLoginFrameWnd();
	if (pLoginFrame == NULL) { Close(); return; }
	pLoginFrame->Create(m_hWnd, _T(""), UI_WNDSTYLE_DIALOG, 0, 0, 0, 0, 0, NULL);
	pLoginFrame->CenterWindow();
	pLoginFrame->ShowModal();
}

void CGameFrameWnd::SendChatMessage()
{
	DuiLib::CEditUI* pChatEdit = static_cast<DuiLib::CEditUI*>(m_pm.FindControl(_T("chatEdit")));
	if (pChatEdit == NULL) return;
	pChatEdit->SetFocus();
	if (pChatEdit->GetText().IsEmpty()) return;

	DuiLib::CRichEditUI* pRichEdit = static_cast<DuiLib::CRichEditUI*>(m_pm.FindControl(_T("chatmsglist")));
	if (pRichEdit == NULL) return;
	long lSelBegin = 0, lSelEnd = 0;
	CHARFORMAT2 cf;
	ZeroMemory(&cf, sizeof(CHARFORMAT2));
	cf.cbSize = sizeof(cf);
	cf.dwReserved = 0;
	cf.dwMask = CFM_COLOR;
	cf.crTextColor = RGB(220, 0, 0);

	lSelEnd = lSelBegin = pRichEdit->GetTextLength();
	pRichEdit->SetSel(lSelEnd, lSelEnd);
	pRichEdit->ReplaceSel(_T("ĳ��"), false);
	lSelEnd = pRichEdit->GetTextLength();
	pRichEdit->SetSel(lSelBegin, lSelEnd);
	pRichEdit->SetSelectionCharFormat(cf);

	lSelBegin = lSelEnd;
	pRichEdit->SetSel(-1, -1);
	pRichEdit->ReplaceSel(_T("˵:"), false);

	pRichEdit->SetSel(-1, -1);
	pRichEdit->ReplaceSel(pChatEdit->GetText(), false);
	pChatEdit->SetText(_T(""));

	pRichEdit->SetSel(-1, -1);
	pRichEdit->ReplaceSel(_T("\n"), false);

	cf.crTextColor = RGB(0, 0, 0);
	lSelEnd = pRichEdit->GetTextLength();
	pRichEdit->SetSel(lSelBegin, lSelEnd);
	pRichEdit->SetSelectionCharFormat(cf);

	pRichEdit->EndDown();
}

void CGameFrameWnd::Notify(DuiLib::TNotifyUI & msg)
{
	if (msg.sType == _T("windowinit")) OnPrepare();
	else if (msg.sType == _T("click")) {
		if (msg.pSender == m_pCloseBtn) {
			DuiLib::COptionUI* pControl = static_cast<DuiLib::COptionUI*>(m_pm.FindControl(_T("hallswitch")));
			if (pControl && pControl->IsSelected() == false) {
				DuiLib::CControlUI* pFadeControl = m_pm.FindControl(_T("fadeEffect"));
				if (pFadeControl) pFadeControl->SetVisible(true);
			}
			else {
				/*Close()*/PostQuitMessage(0); // ��Ϊactivex��ԭ��ʹ��close���ܻ���ִ���
			}
			return;
		}
		else if (msg.pSender == m_pMinBtn) { SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0); return; }
		else if (msg.pSender == m_pMaxBtn) { SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0); return; }
		else if (msg.pSender == m_pRestoreBtn) { SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0); return; }
		DuiLib::CDuiString name = msg.pSender->GetName();
		if (name == _T("quitbtn")) {
			/*Close()*/PostQuitMessage(0); // ��Ϊactivex��ԭ��ʹ��close���ܻ���ִ���
		}
		else if (name == _T("returnhallbtn")) {
			DuiLib::CControlUI* pFadeControl = m_pm.FindControl(_T("fadeEffect"));
			if (pFadeControl) pFadeControl->SetVisible(false);

			DuiLib::COptionUI* pControl = static_cast<DuiLib::COptionUI*>(m_pm.FindControl(_T("hallswitch")));
			pControl->Activate();
			DuiLib::CHorizontalLayoutUI* pH = static_cast<DuiLib::CHorizontalLayoutUI*>(m_pm.FindControl(_T("roomswitchpanel")));
			if (pH) pH->SetVisible(false);
		}
		else if (name == _T("fontswitch")) {
			DuiLib::TFontInfo* pFontInfo = m_pm.GetDefaultFontInfo();
			if (pFontInfo->iSize < 18) {
				DuiLib::TFontInfo* pFontInfo = m_pm.GetFontInfo(0);
				if (pFontInfo)m_pm.SetDefaultFont(pFontInfo->sFontName, pFontInfo->iSize, pFontInfo->bBold,
					pFontInfo->bUnderline, pFontInfo->bItalic);
			}
			else {
				DuiLib::TFontInfo* pFontInfo = m_pm.GetFontInfo(1);
				if (pFontInfo)m_pm.SetDefaultFont(pFontInfo->sFontName, pFontInfo->iSize, pFontInfo->bBold,
					pFontInfo->bUnderline, pFontInfo->bItalic);
			}
			m_pm.GetRoot()->NeedUpdate();
		}
		else if (name == _T("leaveBtn") || name == _T("roomclosebtn")) {
			DuiLib::COptionUI* pControl = static_cast<DuiLib::COptionUI*>(m_pm.FindControl(_T("hallswitch")));
			if (pControl) {
				pControl->Activate();
				DuiLib::CHorizontalLayoutUI* pH = static_cast<DuiLib::CHorizontalLayoutUI*>(m_pm.FindControl(_T("roomswitchpanel")));
				if (pH) pH->SetVisible(false);
			}
		}
		else if (name == _T("sendbtn")) {
			SendChatMessage();
		}
	}
	else if (msg.sType == _T("selectchanged")) {
		DuiLib::CDuiString name = msg.pSender->GetName();
		if (name == _T("hallswitch")) {
			DuiLib::CTabLayoutUI* pControl = static_cast<DuiLib::CTabLayoutUI*>(m_pm.FindControl(_T("switch")));
			if (pControl && pControl->GetCurSel() != 0) pControl->SelectItem(0);
		}
		else if (name == _T("roomswitch")) {
			DuiLib::CTabLayoutUI* pControl = static_cast<DuiLib::CTabLayoutUI*>(m_pm.FindControl(_T("switch")));
			if (pControl && pControl->GetCurSel() != 1) {
				pControl->SelectItem(1);
				DeskListUI* pDeskList = static_cast<DeskListUI*>(m_pm.FindControl(_T("destlist")));
				pDeskList->SetFocus();
				DuiLib::CRichEditUI* pRichEdit = static_cast<DuiLib::CRichEditUI*>(m_pm.FindControl(_T("chatmsglist")));
				if (pRichEdit) {
					pRichEdit->SetText(_T("��ӭ����XXX��Ϸ��ף��Ϸ��죡\n\n"));
					long lSelBegin = 0, lSelEnd = 0;
					CHARFORMAT2 cf;
					ZeroMemory(&cf, sizeof(CHARFORMAT2));
					cf.cbSize = sizeof(cf);
					cf.dwReserved = 0;
					cf.dwMask = CFM_COLOR;
					cf.crTextColor = RGB(255, 0, 0);
					lSelEnd = pRichEdit->GetTextLength();
					pRichEdit->SetSel(lSelBegin, lSelEnd);
					pRichEdit->SetSelectionCharFormat(cf);
				}
			}
		}
	}
	else if (msg.sType == _T("itemclick")) {
		GameListUI* pGameList = static_cast<GameListUI*>(m_pm.FindControl(_T("gamelist")));
		if (pGameList->GetItemIndex(msg.pSender) != -1)
		{
			if (_tcscmp(msg.pSender->GetClass(), _T("ListLabelElementUI")) == 0) {
				GameListUI::Node* node = (GameListUI::Node*)msg.pSender->GetTag();

				POINT pt = { 0 };
				::GetCursorPos(&pt);
				::ScreenToClient(m_pm.GetPaintWindow(), &pt);
				pt.x -= msg.pSender->GetX();
				SIZE sz = pGameList->GetExpanderSizeX(node);
				if (pt.x >= sz.cx && pt.x < sz.cy)
					pGameList->ExpandNode(node, !node->data()._expand);
			}
		}
	}
	else if (msg.sType == _T("itemactivate")) {
		GameListUI* pGameList = static_cast<GameListUI*>(m_pm.FindControl(_T("gamelist")));
		if (pGameList->GetItemIndex(msg.pSender) != -1)
		{
			if (_tcscmp(msg.pSender->GetClass(), _T("ListLabelElementUI")) == 0) {
				GameListUI::Node* node = (GameListUI::Node*)msg.pSender->GetTag();
				pGameList->ExpandNode(node, !node->data()._expand);
				if (node->data()._level == 3) {
					DuiLib::COptionUI* pControl = static_cast<DuiLib::COptionUI*>(m_pm.FindControl(_T("roomswitch")));
					if (pControl) {
						DuiLib::CHorizontalLayoutUI* pH = static_cast<DuiLib::CHorizontalLayoutUI*>(m_pm.FindControl(_T("roomswitchpanel")));
						if (pH) pH->SetVisible(true);
						pControl->SetText(node->parent()->parent()->data()._text);
						pControl->Activate();
					}
				}
			}
		}
	}
	else if (msg.sType == _T("itemselect")) {
		if (msg.pSender->GetName() == _T("chatCombo")) {
			DuiLib::CEditUI* pChatEdit = static_cast<DuiLib::CEditUI*>(m_pm.FindControl(_T("chatEdit")));
			if (pChatEdit) pChatEdit->SetText(msg.pSender->GetText());
			static_cast<DuiLib::CComboUI*>(msg.pSender)->SelectItem(-1);
		}
	}
	else if (msg.sType == _T("return")) {
		if (msg.pSender->GetName() == _T("chatEdit")) {
			SendChatMessage();
		}
	}
}

LPCTSTR CGameFrameWnd::GetItemText(DuiLib::CControlUI * pControl, int iIndex, int iSubItem)
{
	if (pControl->GetParent()->GetParent()->GetName() == _T("userlist")) {
		if (iSubItem == 0) return _T("<i vip.png>");
		if (iSubItem == 1) return _T("<i vip.png>");
		if (iSubItem == 2) return _T("�����ǳ�");
		if (iSubItem == 3) return _T("5");
		if (iSubItem == 4) return _T("50%");
		if (iSubItem == 5) return _T("0%");
		if (iSubItem == 6) return _T("100");
	}

	return _T("");
}

LRESULT CGameFrameWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_pm.Init(m_hWnd);
	DuiLib::CDialogBuilder builder;
	CDialogBuilderCallbackEx cb;
	DuiLib::CControlUI* pRoot = builder.Create(_T("hall.xml"), (UINT)0, &cb, &m_pm);
	ASSERT(pRoot && "Failed to parse XML");
	m_pm.AttachDialog(pRoot);
	m_pm.AddNotifier(this);

	Init();
	return 0;
}

LRESULT CGameFrameWnd::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT CGameFrameWnd::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	::PostQuitMessage(0L);

	bHandled = FALSE;
	return 0;
}

LRESULT CGameFrameWnd::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	if (::IsIconic(*this)) bHandled = FALSE;
	return (wParam == 0) ? TRUE : FALSE;
}

LRESULT CGameFrameWnd::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	return 0;
}

LRESULT CGameFrameWnd::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	return 0;
}

LRESULT CGameFrameWnd::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);

	if (!::IsZoomed(*this)) {
		RECT rcSizeBox = m_pm.GetSizeBox();
		if (pt.y < rcClient.top + rcSizeBox.top) {
			if (pt.x < rcClient.left + rcSizeBox.left) return HTTOPLEFT;
			if (pt.x > rcClient.right - rcSizeBox.right) return HTTOPRIGHT;
			return HTTOP;
		}
		else if (pt.y > rcClient.bottom - rcSizeBox.bottom) {
			if (pt.x < rcClient.left + rcSizeBox.left) return HTBOTTOMLEFT;
			if (pt.x > rcClient.right - rcSizeBox.right) return HTBOTTOMRIGHT;
			return HTBOTTOM;
		}
		if (pt.x < rcClient.left + rcSizeBox.left) return HTLEFT;
		if (pt.x > rcClient.right - rcSizeBox.right) return HTRIGHT;
	}

	RECT rcCaption = m_pm.GetCaptionRect();
	if (pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
		&& pt.y >= rcCaption.top && pt.y < rcCaption.bottom) {
		DuiLib::CControlUI* pControl = static_cast<DuiLib::CControlUI*>(m_pm.FindControl(pt));
		if (pControl && _tcscmp(pControl->GetClass(), _T("ButtonUI")) != 0 &&
			_tcscmp(pControl->GetClass(), _T("OptionUI")) != 0 &&
			_tcscmp(pControl->GetClass(), _T("TextUI")) != 0)
			return HTCAPTION;
	}

	return HTCLIENT;
}

LRESULT CGameFrameWnd::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	SIZE szRoundCorner = m_pm.GetRoundCorner();
	if (!::IsIconic(*this) && (szRoundCorner.cx != 0 || szRoundCorner.cy != 0)) {
		DuiLib::CDuiRect rcWnd;
		::GetWindowRect(*this, &rcWnd);
		rcWnd.Offset(-rcWnd.left, -rcWnd.top);
		rcWnd.right++; rcWnd.bottom++;
		HRGN hRgn = ::CreateRoundRectRgn(rcWnd.left, rcWnd.top, rcWnd.right, rcWnd.bottom, szRoundCorner.cx, szRoundCorner.cy);
		::SetWindowRgn(*this, hRgn, TRUE);
		::DeleteObject(hRgn);
	}

	bHandled = FALSE;
	return 0;
}

LRESULT CGameFrameWnd::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	MONITORINFO oMonitor = {};
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);
	DuiLib::CDuiRect rcWork = oMonitor.rcWork;
	LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
	lpMMI->ptMaxPosition.x = rcWork.left;
	lpMMI->ptMaxPosition.y = rcWork.top;
	lpMMI->ptMaxSize.x = rcWork.right - rcWork.left;
	lpMMI->ptMaxSize.y = rcWork.bottom - rcWork.top;
	bHandled = FALSE;
	return 0;
}

LRESULT CGameFrameWnd::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	// ��ʱ�����յ�WM_NCDESTROY���յ�wParamΪSC_CLOSE��WM_SYSCOMMAND
	if (wParam == SC_CLOSE) {
		::PostQuitMessage(0L);
		bHandled = TRUE;
		return 0;
	}
	BOOL bZoomed = ::IsZoomed(*this);
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	if (::IsZoomed(*this) != bZoomed) {
		if (!bZoomed) {
			DuiLib::CControlUI* pControl = static_cast<DuiLib::CControlUI*>(m_pm.FindControl(_T("maxbtn")));
			if (pControl) pControl->SetVisible(false);
			pControl = static_cast<DuiLib::CControlUI*>(m_pm.FindControl(_T("restorebtn")));
			if (pControl) pControl->SetVisible(true);
		}
		else {
			DuiLib::CControlUI* pControl = static_cast<DuiLib::CControlUI*>(m_pm.FindControl(_T("maxbtn")));
			if (pControl) pControl->SetVisible(true);
			pControl = static_cast<DuiLib::CControlUI*>(m_pm.FindControl(_T("restorebtn")));
			if (pControl) pControl->SetVisible(false);
		}
	}
	return lRes;
}

LRESULT CGameFrameWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch (uMsg) {
	case WM_CREATE:        lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
	case WM_CLOSE:         lRes = OnClose(uMsg, wParam, lParam, bHandled); break;
	case WM_DESTROY:       lRes = OnDestroy(uMsg, wParam, lParam, bHandled); break;
	case WM_NCACTIVATE:    lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); break;
	case WM_NCCALCSIZE:    lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); break;
	case WM_NCPAINT:       lRes = OnNcPaint(uMsg, wParam, lParam, bHandled); break;
	case WM_NCHITTEST:     lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); break;
	case WM_SIZE:          lRes = OnSize(uMsg, wParam, lParam, bHandled); break;
	case WM_GETMINMAXINFO: lRes = OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled); break;
	case WM_SYSCOMMAND:    lRes = OnSysCommand(uMsg, wParam, lParam, bHandled); break;
	default:
		bHandled = FALSE;
	}
	if (bHandled) return lRes;
	if (m_pm.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}
