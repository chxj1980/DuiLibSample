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

	//�������������û������
	void CEventSource::operator+= (const CDelegateBase& d)
	{
		for (int i = 0; i < m_aDelegates.GetSize(); i++) {
			CDelegateBase* pObject = static_cast<CDelegateBase*>(m_aDelegates[i]);
			if (pObject && pObject->Equals(d)) return;
		}

		//d��������CDelegateBaseΪ�����࣬����ʵ��������˴����������ñض��������ࡣ
		//��ʵ����ֻ�г�����CDelegateBase����������������ߣ�Consumer��������ʵ����CDelegateBase���ͣ�
		//Ҳ�͵��µ�ǰ�Ĳ���������û������
		m_aDelegates.Add(d.Copy());
	}

	void CEventSource::operator+= (FnType pFn)
	{
		(*this) += MakeDelegate(pFn);
	}

	//�������û������
	void CEventSource::operator-= (const CDelegateBase& d)
	{
		for (int i = 0; i < m_aDelegates.GetSize(); i++) {
			CDelegateBase* pObject = static_cast<CDelegateBase*>(m_aDelegates[i]);
			if (pObject && pObject->Equals(d)) {
				//��Ϊ�������޷�����CDelegateBase���͵�ʵ�������Ҳ���޷����ø����������
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

	//��������ί��
	bool CEventSource::operator() (void* param)
	{
		for (int i = 0; i < m_aDelegates.GetSize(); i++) {
			CDelegateBase* pObject = static_cast<CDelegateBase*>(m_aDelegates[i]);
			if (pObject && !(*pObject)(param)) return false;
		}
		return true;
	}

} // namespace DuiLib
