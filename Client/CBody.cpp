#include "pch.h"
#include "CBody.h"


CBody::CBody()
	: CComponent(COMPONENT_TYPE::CBODY)//body 컴포넌트
	, m_bCurAnim(nullptr)//현재 몸체 
	, m_bRepeat(false) //반복 여부
{
	

	//상체 하체를 애니메이션을 바디에 받아 온다. 
	//AddBodyType(new CUpper);
	//AddBodyType(new CLower);

}

CBody::CBody(const CBody& _animator)
	: CComponent(_animator)
	, m_mapBodyAnim()
	, m_bCurAnim(nullptr)
	, m_bRepeat(_animator.m_bRepeat)
{
	//현재 body Animation 받아온 후 iter에 넣는다. 
	map<wstring, CBody*>::const_iterator iter = _animator.m_mapBodyAnim.begin();
	for (iter; iter != _animator.m_mapBodyAnim.end(); ++iter)
	{
		CAnimation* pAnim = new CAnimation(*iter->second);
		pAnim->m_pAnimator = this;
		m_mapAnim.insert(make_pair(iter->first, pAnim));
	}

	//for (const auto& pair : _animator.m_mapAnim)
	//{
	//	pair.second;
	//}

	if (nullptr != _animator.m_pCurAnim)
	{
		Play(_animator.m_pCurAnim->GetName(), m_bRepeat);
	}

}

CBody::~CBody()
{

}

void CBody::tick()
{
	if (nullptr != m_bCurAnim)
	{
		m_bCurAnim->tick();

		if (m_bRepeat && m_bCurAnim->IsFinish())
		{
			m_bCurAnim->Reset();
		}
	}
}

void CBody::render(HDC _dc)
{

}




