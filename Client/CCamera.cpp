#include "pch.h"
#include "CCamera.h"
#include "CEngine.h"

#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CResMgr.h"
#include "CObject.h"
#include "CImage.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CPlayer1.h"

CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_pVeil(nullptr)
	, m_fAlpha(0.f)	
	, m_fAccTime(0.f)
	, m_CamSpeed(1500.f)
{	
	POINT ptResol = CEngine::GetInst()->GetResolution();
	m_pVeil = CResMgr::GetInst()->CreateImg(L"Veil", ptResol.x, ptResol.y);
}

CCamera::~CCamera()
{
}

void CCamera::init()
{
	m_vResolution = CEngine::GetInst()->GetResolution();
	m_vLook = (m_vResolution / 2.f);

	//초기화면 빈공간 만큼 아래로 내린다.
	//m_vLook.y = m_vLook.y + 204.f;



}

void CCamera::tick()
{	
	m_fAccTime += DT;

	if (IsPressed(KEY_TYPE::W))
	{
		m_vLook.y -= DT * 1000.f;
	}
	if (IsPressed(KEY_TYPE::S))
	{
		m_vLook.y += DT * 1000.f;
	}
	if (IsPressed(KEY_TYPE::A))
	{
		m_vLook.x -= DT * 1000.f;
	}
	if (IsPressed(KEY_TYPE::D))
	{
		m_vLook.x += DT * 1000.f;
	}
	//m_vLook.x = m_pTargetObj->GetPos().x;

	
	//
	//특정 지점을 넘어 선다면

	//
	//if (m_pTargetObj->GetPos().x > (m_vLook.x - 90.f))
	//{
	//	//if(m_fAccTime > 0.5f)
	//		m_vLook.x += DT * m_CamSpeed;

	//	m_fAccTime = 0.f;
	//}

	
	// 처리할 카메라 효과가 있으면
	if (!m_CamEffectInfo.empty())
	{
		tCamEffectInfo& info = m_CamEffectInfo.front();

		info.fAccTime += DT;
		float fRatio = (info.fAccTime / info.fDuration);	// 제한 시간 대비 진행시간의 비율을 0 ~ 1 사이로 환산

		if (1.f <= fRatio)
		{
			fRatio = 1.f;
			m_CamEffectInfo.pop_front();
		}

		else
		{
			if (CAM_EFFECT::FADE_IN == info.eEffect)
				m_fAlpha = 1.f - fRatio;
			else if (CAM_EFFECT::FADE_OUT == info.eEffect)
				m_fAlpha = fRatio;
			else
				m_fAlpha = 0.f;
		}
	}

	m_vDiff = m_vLook - (m_vResolution / 2.f);

	/*
	캐릭터가 소환된 경우 일정 속도로 화면을 아래로 내려준다. 
	*/
	if (getSummon()) 
	{
		m_vLook.y += DT * 500.f;
		if (m_vLook.y >= 555.f)
		{
			setSummon(false);
		}
	}

	


}

void CCamera::render(HDC _dc)
{
	if (0.f == m_fAlpha)
		return;

	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = 0;
	tFunc.SourceConstantAlpha = (BYTE)(255.f * m_fAlpha);

	AlphaBlend(_dc, 0, 0
		, m_pVeil->GetWidth(), m_pVeil->GetHeight()
		, m_pVeil->GetDC()
		, 0, 0
		, m_pVeil->GetWidth(), m_pVeil->GetHeight()
		, tFunc);

}
