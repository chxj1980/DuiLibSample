#include "../StdAfx.h"

namespace DuiLib {

	///////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//

	CDelegateBase::CDelegateBase(void* pObject, void* pFn)
	{
		m_pObject = pObject;
		m_pFn = pFn;
	}

	CDelegateBase::CDelegateBase(const CDelegateBase& rhs)
	{
		m_pObject = rhs.m_pObject;
		m_pFn = rhs.m_pFn;
	}

	CDelegateBase::~CDelegateBase()
	{

	}

	bool CDelegateBase::Equals(const CDelegateBase& rhs) const
	{
		return m_pObject == rhs.m_pObject && m_pFn == rhs.m_pFn;
	}

	bool CDelegateBase::operator() (void* param)
	{
		return Invoke(param);
	}

	void* CDelegateBase::GetFn()
	{
		return m_pFn;
	}

	void* CDelegateBase::GetObject()
	{
		return m_pObject;
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//

	CDelegateStatic::CDelegateStatic(Fn pFn) : CDelegateBase(NULL, pFn)
	{

	}

	CDelegateStatic::CDelegateStatic(const CDelegateStatic& rhs) : CDelegateBase(rhs)
	{

	}

	CDelegateBase* CDelegateStatic::Copy() const
	{
		return new CDelegateStatic(*this);
	}

	bool CDelegateStatic::Invoke(void* param)
	{
		Fn pFn = (Fn)GetFn();
		return (*pFn)(param);
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//

	CEventSource::~CEventSource()
	{
		for (int i = 0; i < m_aDelegates.GetSize(); i++) {
			CDelegateBase* pObject = static_cast<CDelegateBase*>(m_aDelegates[i]);
			if (pObject) delete pObject;
		}
	}

	CEventSource::operator bool()
	{
		return m_aDelegates.GetSize() > 0;
	}

	//这个操作符重载没有意义
	void CEventSource::operator+= (const CDelegateBase& d)
	{
		for (int i = 0; i < m_aDelegates.GetSize(); i++) {
			CDelegateBase* pObject = static_cast<CDelegateBase*>(m_aDelegates[i]);
			if (pObject && pObject->Equals(d)) return;
		}

		//d变量类型CDelegateBase为抽象类，不可实例化，因此传进来的引用必定是其子类。
		//但实际上只有抽象类CDelegateBase被导出，因此消费者（Consumer）不可能实例化CDelegateBase类型，
		//也就导致当前的操作符重载没有意义
		m_aDelegates.Add(d.Copy());
	}

	void CEventSource::operator+= (FnType pFn)
	{
		(*this) += MakeDelegate(pFn);
	}

	//这个重载没有意义
	void CEventSource::operator-= (const CDelegateBase& d)
	{
		for (int i = 0; i < m_aDelegates.GetSize(); i++) {
			CDelegateBase* pObject = static_cast<CDelegateBase*>(m_aDelegates[i]);
			if (pObject && pObject->Equals(d)) {
				//因为消费者无法产生CDelegateBase类型的实例，因此也就无法调用该重载运算符
				delete pObject;
				m_aDelegates.Remove(i);
				return;
			}
		}
	}

	void CEventSource::operator-= (FnType pFn)
	{
		(*this) -= MakeDelegate(pFn);
	}

	//调用所有委托
	bool CEventSource::operator() (void* param)
	{
		for (int i = 0; i < m_aDelegates.GetSize(); i++) {
			CDelegateBase* pObject = static_cast<CDelegateBase*>(m_aDelegates[i]);
			if (pObject && !(*pObject)(param)) return false;
		}
		return true;
	}

} // namespace DuiLib
