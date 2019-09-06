#ifndef __UIDELEGATE_H__
#define __UIDELEGATE_H__

#pragma once

namespace DuiLib {

    /////////////////////////////////////////////////////////////////////////////////////
    //

    class UILIB_API CDelegateBase
    {
    public:
        CDelegateBase(void* pObject, void* pFn);
        CDelegateBase(const CDelegateBase& rhs);
        virtual ~CDelegateBase();
        bool Equals(const CDelegateBase& rhs) const;
        bool operator() (void* param);
        virtual CDelegateBase* Copy() const = 0;    // add const for gcc ??

    protected:
        void* GetFn();
        void* GetObject();
        virtual bool Invoke(void* param) = 0;       //����ʵ��

    private:
        void* m_pObject;
        void* m_pFn;
    };


    /////////////////////////////////////////////////////////////////////////////////////
    //

    class CDelegateStatic : public CDelegateBase
    {
        typedef bool(*Fn)(void*);
    public:
        CDelegateStatic(Fn pFn);
        CDelegateStatic(const CDelegateStatic& rhs);
        virtual CDelegateBase* Copy() const;

    protected:
        virtual bool Invoke(void* param);
    };


    /////////////////////////////////////////////////////////////////////////////////////
    //

    template <class O, class T>
    class CDelegate : public CDelegateBase
    {
        typedef bool (T::* Fn)(void*);
    public:
        CDelegate(O* pObj, Fn pFn) : CDelegateBase(pObj, &pFn), m_pFn(pFn) { }
        CDelegate(const CDelegate& rhs) : CDelegateBase(rhs) { m_pFn = rhs.m_pFn; }
        virtual CDelegateBase* Copy() const { return new CDelegate(*this); }

    protected:
        virtual bool Invoke(void* param)
        {
            O* pObject = (O*)GetObject();
            return (pObject->*m_pFn)(param);
        }

    private:
        Fn m_pFn;
    };


    /////////////////////////////////////////////////////////////////////////////////////
    //

    template <class O, class T>
    CDelegate<O, T> MakeDelegate(O* pObject, bool (T::* pFn)(void*))
    {
        return CDelegate<O, T>(pObject, pFn);
    }


    /////////////////////////////////////////////////////////////////////////////////////
    //

    inline CDelegateStatic MakeDelegate(bool(*pFn)(void*))
    {
        return CDelegateStatic(pFn);
    }


    /////////////////////////////////////////////////////////////////////////////////////
    //

    class UILIB_API CEventSource
    {
        typedef bool(*FnType)(void*);
    public:
        ~CEventSource();
        operator bool();
        void operator+= (const CDelegateBase& d);//����û�����壬�����ߴ��벢����ʵ����CDelegateBase���͵Ķ���		 add const for gcc
        void operator+= (FnType pFn);			 //����ί��
        void operator-= (const CDelegateBase& d);//����û�����壬�����ߴ��벢����ʵ����CDelegateBase���͵Ķ���
        void operator-= (FnType pFn);			 //����ί��
        bool operator() (void* param);           //���ݲ�����������ί��

    protected:
        CStdPtrArray m_aDelegates;
    };

} // namespace DuiLib

#endif // __UIDELEGATE_H__