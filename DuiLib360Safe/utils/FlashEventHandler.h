#ifndef FLASHEVENTHANDLER_H
#define FLASHEVENTHANDLER_H

#pragma once

#include <Windows.h>

namespace DuiLib
{
    class CFlashEventHandler
    {
    public:
        CFlashEventHandler() {}
        ~CFlashEventHandler() {}

        virtual ULONG STDMETHODCALLTYPE Release(void) { return S_OK; }
        virtual ULONG STDMETHODCALLTYPE AddRef(void) { return S_OK; }

        virtual HRESULT OnReadyStateChange(long newState)
        {
            return S_OK;
        }

        virtual HRESULT OnProgress(long percentDone)
        {
            return S_OK;
        }

        virtual HRESULT FSCommand(LPCTSTR command, LPCTSTR args)
        {
            return S_OK;
        }

        virtual HRESULT FlashCall(LPCTSTR request)
        {
            return S_OK;
        }
    };
}

#endif // !FLASHEVENTHANDLER_H