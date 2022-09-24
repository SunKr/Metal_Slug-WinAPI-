#include "pch.h"
#include "CObject.h"

#include "CComponent.h"

CObject::CObject()
	: m_arrComponent{}
	, m_bDead(false)
{
}

CObject::CObject(const CObject& _obj)
	: CEntity(_obj)
	, m_arrComponent{}
	, m_vPos(_obj.m_vPos)
	, m_vScale(_obj.m_vScale)
	, m_bDead(false)
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != _obj.m_arrComponent[i])
		{			
			AddComponent(_obj.m_arrComponent[i]->Clone());
		}
	}
}

CObject::~CObject()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		SAFE_DELETE(m_arrComponent[i]);
	}
}

//컴포넌트 추가 함수
void CObject::AddComponent(CComponent* _pComponent)
{
	//현재 컴포넌트의 타입을 받아온다. 배열에 집어 넣는다.
	m_arrComponent[(UINT)_pComponent->GetType()] = _pComponent;
	//컴포넌트를 소유한 주인을 컴포넌트 주인에 집어 넣는다. 
	_pComponent->m_pOwner = this;
}

void CObject::tick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr == m_arrComponent[i])
			continue;

		m_arrComponent[i]->tick();
	}
}

void CObject::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr == m_arrComponent[i])
			continue;

		m_arrComponent[i]->render(_dc);
	}
}
