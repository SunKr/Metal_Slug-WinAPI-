#include "pch.h"
#include "CAnimator.h"

#include "CAnimation.h"
#include "CAnimationLower.h"

CAnimator::CAnimator()
	: CComponent(COMPONENT_TYPE::ANIMATOR)
	, m_pCurAnim(nullptr)
	, m_bRepeat(false)
{
}

CAnimator::CAnimator(const CAnimator& _animator)
	: CComponent(_animator)
	, m_mapAnim()
	, m_pCurAnim(nullptr)
	, m_bRepeat(_animator.m_bRepeat)
{
	map<wstring, CAnimation*>::const_iterator iter = _animator.m_mapAnim.begin();
	for (iter; iter != _animator.m_mapAnim.end(); ++iter)
	{
		CAnimation* pAnim = new CAnimation(*iter->second);
		pAnim->m_pAnimator = this;
		m_mapAnim.insert(make_pair(iter->first, pAnim));
	}

	//for (const auto& pair : _animator.m_mapAnim)
	//{
	//	pair.second;
	//}

	//���� ���߿� lower ���� �ʿ�
	if (nullptr != _animator.m_pCurAnim)
	{
		Play(_animator.m_pCurAnim->GetName(), m_bRepeat);
	}
}

CAnimator::~CAnimator()
{
	Safe_Del_Map(m_mapAnim);
	Safe_Del_Map(m_mapAnimLower);
}

void CAnimator::tick()
{
	if (nullptr != m_pCurAnim)
	{
		m_pCurAnim->tick();

		if (m_bRepeat && m_pCurAnim->IsFinish())
		{
			m_pCurAnim->Reset(); 
		}
	}

	if (nullptr != m_pCurLowerAnim)
	{
		m_pCurLowerAnim->tick();

		if (m_bRepeat && m_pCurLowerAnim->IsFinish())
		{
			m_pCurLowerAnim->Reset();
		}
	}
}

void CAnimator::render(HDC _dc)
{
	if (nullptr != m_pCurLowerAnim)
		m_pCurLowerAnim->render(_dc);
	if (nullptr != m_pCurAnim)
		m_pCurAnim->render(_dc);

}

//�ִϸ��̼� ��ü
CAnimation* CAnimator::FindAnimation(const wstring& _strKey)
{
	map<wstring, CAnimation*>::iterator iter = m_mapAnim.find(_strKey);

	if (iter == m_mapAnim.end())
	{
		return nullptr;
	}

	return iter->second;
}


//��ü �ִϸ��̼�
CAnimationLower* CAnimator::FindLowerAnimation(const wstring& _strKey)
{
	map<wstring, CAnimationLower*>::iterator iter = m_mapAnimLower.find(_strKey);

	if (iter == m_mapAnimLower.end())
	{
		return nullptr;
	}

	return iter->second;
}

void CAnimator::Play(const wstring& _strName, bool _bRepeat)
{
	m_pCurAnim = FindAnimation(_strName);
	m_pCurAnim->Reset();

	m_bRepeat = _bRepeat;

}


void CAnimator::PlayLower(const wstring& _strName, bool _bRepeat)
{
	m_pCurLowerAnim = FindLowerAnimation(_strName);
	m_pCurLowerAnim->Reset();

	m_bRepeat = _bRepeat;

}



//�Ϲ� �ִϸ��̼� ����
void CAnimator::CreateAnimation(const wstring& _strName
	, CImage* _pImage, Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset
	, float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation)
{
	CAnimation* pAnim = FindAnimation(_strName);

	if (nullptr != pAnim)
	{
		MessageBox(nullptr, L"Animation �̸� �ߺ�", L"Animation ���� ����", MB_OK);
		return;
	}

	pAnim = new CAnimation;
	pAnim->Create(_pImage, _vLeftTop, _vSize, _vOffset, _fStep, _iFrmCount, _fDuration, _bCamRelation);
	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;

	m_mapAnim.insert(make_pair(_strName, pAnim));
}


//��ü �ִϸ��̼� ����
void CAnimator::CreateLowerAnimation(const wstring& _strName
	, CImage* _pImage, Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset
	, float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation)
{
	CAnimationLower* pAnim = FindLowerAnimation(_strName);

	if (nullptr != pAnim)
	{
		MessageBox(nullptr, L"Animation �̸� �ߺ�", L"Animation ���� ����", MB_OK);
		return;
	}

	pAnim = new CAnimationLower;
	pAnim->Create(_pImage, _vLeftTop, _vSize, _vOffset, _fStep, _iFrmCount, _fDuration, _bCamRelation);
	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;

	m_mapAnimLower.insert(make_pair(_strName, pAnim));
}

//�ִϸ��̼��� �������� ����� �ʿ� 
void CAnimator::CreateReverseAnimation(const wstring& _strName
	, CImage* _pImage, Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset
	, float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation)
{
	CAnimation* pAnim = FindAnimation(_strName);

	if (nullptr != pAnim)
	{
		MessageBox(nullptr, L"Animation �̸� �ߺ�", L"Animation ���� ����", MB_OK);
		return;
	}

	pAnim = new CAnimation;
	pAnim->CreateReverse(_pImage, _vLeftTop, _vSize, _vOffset, _fStep, _iFrmCount, _fDuration, _bCamRelation);
	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;

	m_mapAnim.insert(make_pair(_strName, pAnim));
}


//��ü ����
void CAnimator::CreateReverseLowerAnimation(const wstring& _strName
	, CImage* _pImage, Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset
	, float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation)
{
	CAnimationLower* pAnim = FindLowerAnimation(_strName);

	if (nullptr != pAnim)
	{
		MessageBox(nullptr, L"Animation �̸� �ߺ�", L"Animation ���� ����", MB_OK);
		return;
	}

	pAnim = new CAnimationLower;
	pAnim->CreateReverse(_pImage, _vLeftTop, _vSize, _vOffset, _fStep, _iFrmCount, _fDuration, _bCamRelation);
	pAnim->SetName(_strName);
	pAnim->m_pAnimator = this;

	m_mapAnimLower.insert(make_pair(_strName, pAnim));
}