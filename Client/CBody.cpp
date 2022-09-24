#include "pch.h"
#include "CBody.h"


CBody::CBody()
	: CComponent(COMPONENT_TYPE::CBODY)//body ������Ʈ
	, m_bCurAnim(nullptr)//���� ��ü 
	, m_bRepeat(false) //�ݺ� ����
{
	

	//��ü ��ü�� �ִϸ��̼��� �ٵ� �޾� �´�. 
	//AddBodyType(new CUpper);
	//AddBodyType(new CLower);

}

CBody::CBody(const CBody& _animator)
	: CComponent(_animator)
	, m_mapBodyAnim()
	, m_bCurAnim(nullptr)
	, m_bRepeat(_animator.m_bRepeat)
{
	//���� body Animation �޾ƿ� �� iter�� �ִ´�. 
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




