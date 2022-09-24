#include "pch.h"
#include "CLower.h"


#include "CObject.h"
#include "CAnimator.h"

#include "CTimeMgr.h"
#include "CCamera.h"

#include "CImage.h"

CLower::CLower()
	: m_pAnimator(nullptr)
	, m_pImage(nullptr)
	, m_iCurFrm(0)
	, m_fAccTime(0.f)
	, m_bCamRelation(false)
	, m_bFinish(false)
{
}

CLower::~CLower()
{
}


void CLower::tick()
{
	if (m_bFinish)
		return;

	m_fAccTime += DT;

	if (m_vecFrm[m_iCurFrm].fDuration < m_fAccTime)
	{
		m_fAccTime -= m_vecFrm[m_iCurFrm].fDuration;

		// ������ �ε����� �ʰ��� ��� ==> Animation ��� �Ϸ�
		if (m_vecFrm.size() <= m_iCurFrm + 1)
		{
			m_bFinish = true;
		}
		else
		{
			++m_iCurFrm;
		}
	}
}

void CLower::render(HDC _dc)
{
	//���� ����
	CObject* pOwner = m_pAnimator->GetOwner();
	//������ ��ġ
	Vec2 vPos = pOwner->GetPos();

	//ī�޶� ���� ���� ������ ī�޶� ������ ��ǥ�� ��ǥ ������
	if (m_bCamRelation)
	{
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}

	// ������ AlphaBlend��
	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = 255;

	// Frame �� Offset �� ���Ѵ�. ==> ���� ��ġ
	vPos += m_vecFrm[m_iCurFrm].vOffset;

	AlphaBlend(_dc
		, int(vPos.x - m_vecFrm[m_iCurFrm].vSize.x / 2.f)
		, int(vPos.y - m_vecFrm[m_iCurFrm].vSize.y / 2.f)
		, int(m_vecFrm[m_iCurFrm].vSize.x)
		, int(m_vecFrm[m_iCurFrm].vSize.y)
		, m_pImage->GetDC()
		, int(m_vecFrm[m_iCurFrm].vLeftTop.x)
		, int(m_vecFrm[m_iCurFrm].vLeftTop.y)
		, int(m_vecFrm[m_iCurFrm].vSize.x)
		, int(m_vecFrm[m_iCurFrm].vSize.y)
		, tFunc);
}

void CLower::Create(CImage* _pImage, Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset, float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation)
{
	//�̹��� �޾ƿͼ�
	m_pImage = _pImage;
	//ī�޶� ���� �޾ƿͼ�
	m_bCamRelation = _bCamRelation;

	//������ ���� ��ŭ  vector�� ���� animation�ڷ� �־��ش�.
	for (UINT i = 0; i < _iFrmCount; ++i)
	{
		tAnimFrm frm = {};

		frm.vLeftTop.x = _vLeftTop.x + (_fStep * (float)i);
		frm.vLeftTop.y = _vLeftTop.y;
		frm.vSize = _vSize;
		frm.vOffset = _vOffset;
		frm.fDuration = _fDuration;

		m_vecFrm.push_back(frm);
	}
}

void CLower::CreateAnimation(const wstring& _strName, CImage* _pImage, Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset, float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation)
{
	CBody* pAnim = FindAnimation(_strName);

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

CBody* CLower::FindAnimation(const wstring& _strKey)
{
	return nullptr;
}

void CLower::Play(const wstring& _strName, bool _bRepeat)
{
}

