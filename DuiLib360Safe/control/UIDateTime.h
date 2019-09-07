#ifndef __UIDATETIME_H__
#define __UIDATETIME_H__

#pragma once

#include "../control/UILabel.h"

#define UILIB_API
#define _UNICODE

namespace DuiLib
{
	class CDateTimeWnd;

	/// ʱ��ѡ��ؼ�
	class UILIB_API CDateTimeUI : public CLabelUI
	{
		friend class CDateTimeWnd;
	public:
		CDateTimeUI();
		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		SYSTEMTIME& GetTime();
		void SetTime(SYSTEMTIME* pst);

		void SetReadOnly(bool bReadOnly);
		bool IsReadOnly() const;

		void UpdateText();

		void DoEvent(TEventUI& event);

	protected:
		SYSTEMTIME m_sysTime;
		int        m_nDTUpdateFlag;
		bool       m_bReadOnly;

		CDateTimeWnd* m_pWindow;
	};
}
#endif // __UIDATETIME_H__