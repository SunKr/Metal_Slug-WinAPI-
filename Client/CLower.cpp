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

		// 벡터의 인덱스를 초과한 경우 ==> Animation 재생 완료
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
	//현재 주인
	CObject* pOwner = m_pAnimator->GetOwner();
	//주인의 위치
	Vec2 vPos = pOwner->GetPos();

	//카메라 연동 여부 연동시 카메라 렌더링 좌표로 좌표 가져옴
	if (m_bCamRelation)
	{
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}

	// 렌더링 AlphaBlend로
	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = 255;

	// Frame 의 Offset 을 더한다. ==> 최종 위치
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
	//이미지 받아와서
	m_pImage = _pImage;
	//카메라 연동 받아와서
	m_bCamRelation = _bCamRelation;

	//프레임 숫자 만큼  vector를 통해 animation자료 넣어준다.
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
		MessageBox(nullptr, L"Animation 이름 중복", L"Animation 생성 실패", MB_OK);
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

