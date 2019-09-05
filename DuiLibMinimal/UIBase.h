
#include <Windows.h>

#define UILIB_API

#ifndef __UIBASE_H__
#define __UIBASE_H__

#pragma once

namespace DuiLib {

	/////////////////////////////////////////////////////////////////////////////////////
	//

	#define UI_WNDSTYLE_CONTAINER  (0)
	#define UI_WNDSTYLE_FRAME      (WS_VISIBLE | WS_OVERLAPPEDWINDOW)
	#define UI_WNDSTYLE_CHILD      (WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN)
	#define UI_WNDSTYLE_DIALOG     (WS_VISIBLE | WS_POPUPWINDOW | WS_CAPTION | WS_DLGFRAME | WS_CLIPSIBLINGS | WS_CLIPCHILDREN)

	#define UI_WNDSTYLE_EX_FRAME   (WS_EX_WINDOWEDGE)
	#define UI_WNDSTYLE_EX_DIALOG  (WS_EX_TOOLWINDOW | WS_EX_DLGMODALFRAME)

	#define UI_CLASSSTYLE_CONTAINER  (0)
	#define UI_CLASSSTYLE_FRAME      (CS_VREDRAW | CS_HREDRAW)
	#define UI_CLASSSTYLE_CHILD      (CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_SAVEBITS)
	#define UI_CLASSSTYLE_DIALOG     (CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS | CS_SAVEBITS)

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class UILIB_API CWindowWnd
	{
	public:
		CWindowWnd();

		HWND GetHWND() const;
		operator HWND() const;

		bool RegisterWindowClass();
		bool RegisterSuperclass();

		HWND Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, const RECT rc, HMENU hMenu = NULL);//没有菜单的，指定大小的窗口
		HWND Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT, HMENU hMenu = NULL);
		HWND CreateDuiWindow(HWND hwndParent, LPCTSTR pstrWindowName, DWORD dwStyle = 0, DWORD dwExStyle = 0);            //没有菜单的，尺寸为0的窗口
		HWND Subclass(HWND hWnd);
		void Unsubclass();
		void ShowWindow(bool bShow = true, bool bTakeFocus = true);
		UINT ShowModal();
		void Close(UINT nRet = IDOK);
		void CenterWindow();	// 居中，支持扩展屏幕
		void SetIcon(UINT nRes);

		LRESULT SendMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L);
		LRESULT PostMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L);
		void ResizeClient(int cx = -1, int cy = -1);

	protected:
		virtual LPCTSTR GetWindowClassName() const = 0;//当前类并未实现，留给子类实现
		virtual LPCTSTR GetSuperClassName() const;     //
		virtual UINT GetClassStyle() const;            //获取窗体风格（class style），比如：CS_HREDRAW | CS_VREDRAW

		virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
		virtual void OnFinalMessage(HWND hWnd);

		static LRESULT CALLBACK __WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);    //static成员，相当于一个独立的函数，该函数作为窗体的回调函数——窗体过程。
		static LRESULT CALLBACK __ControlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);//static成员，相当于一个独立的函数，该函数作为控件的回调函数？

	protected:
		HWND m_hWnd;            //注册的窗体的句柄
		WNDPROC m_OldWndProc;
		bool m_bSubclassed;
	};

} // namespace DuiLib

#endif // __UIBASE_H__
