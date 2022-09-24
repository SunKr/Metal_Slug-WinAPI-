#include "pch.h"
#include "CPlayer.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CCamera.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CMissile.h"
#include "CGuidedMissile.h"

#include "CEngine.h"
#include "CImage.h"
#include "CResMgr.h"
#include "CEventMgr.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidBody.h"

CPlayer::CPlayer()	
	: m_fSpeed(200.f)
	, m_fAccTime(0.f)
{	
	AddComponent(new CCollider);
	AddComponent(new CAnimator);
	AddComponent(new CRigidBody);

	GetCollider()->SetScale(Vec2(50.f, 50.f));
	GetCollider()->SetOffset(Vec2(0.f, 10.f));

	CImage* pPlayerAtlas = CResMgr::GetInst()->LoadImg(L"PlayerAtlas", L"image\\link.bmp");
	GetAnimator()->CreateAnimation(L"Walk_Up", pPlayerAtlas, Vec2(0.f, 780.f), Vec2(120.f, 130.f),		Vec2(0.f,-30.f), 120.f, 10, 0.1f);
	GetAnimator()->CreateAnimation(L"Walk_Down", pPlayerAtlas, Vec2(0.f, 520.f), Vec2(120.f, 130.f),	Vec2(0.f,-30.f), 120.f, 10, 0.1f);
	GetAnimator()->CreateAnimation(L"Walk_Left", pPlayerAtlas, Vec2(0.f, 650.f), Vec2(120.f, 130.f),	Vec2(0.f,-30.f), 120.f, 10, 0.1f);
	GetAnimator()->CreateAnimation(L"Walk_Right", pPlayerAtlas, Vec2(0.f, 910.f), Vec2(120.f, 130.f),	Vec2(0.f,-30.f), 120.f, 10, 0.1f);

	GetAnimator()->Play(L"Walk_Down", true);

	GetRigidBody()->SetMaxSpeed(200.f);
	GetRigidBody()->SetMaxGravitySpeed(1000.f);
	GetRigidBody()->SetGround(false);
	GetRigidBody()->SetGravityAccel(Vec2(0.f, 800.f));	


	
}

CPlayer::~CPlayer()
{
	
}

void CPlayer::tick()
{
	m_fAccTime += DT;

	// 키입력에 따른 이동
	Vec2 vPos = GetPos();

	// 시간 동기화
	/*if (IsPressed(KEY_TYPE::UP))
	{		
		GetRigidBody()->AddForce(Vec2(0.f, -500.f));
	}

	if (IsPressed(KEY_TYPE::DOWN))
	{
		GetRigidBody()->AddForce(Vec2(0.f, 500.f));
	}*/

	if (IsPressed(KEY_TYPE::LEFT))
	{
		GetRigidBody()->AddForce(Vec2(-500.f, 0.f));
	}

	if (IsPressed(KEY_TYPE::RIGHT))
	{
		GetRigidBody()->AddForce(Vec2(500.f, 0.f));
	}

	//if (IsTap(KEY_TYPE::UP))
	//	GetAnimator()->Play(L"Walk_Up", true);
	//if (IsTap(KEY_TYPE::DOWN))
	//	GetAnimator()->Play(L"Walk_Down", true);
	if (IsTap(KEY_TYPE::LEFT))
		this->GetAnimator()->Play(L"Walk_Left", true);
	if (IsTap(KEY_TYPE::RIGHT))
		GetAnimator()->Play(L"Walk_Right", true);

	if (IsTap(KEY_TYPE::SPACE))
	{
		Vec2 vV = GetRigidBody()->GetVelocity();
		vV.y = -500.f;
		GetRigidBody()->SetVelocity(vV);
		GetRigidBody()->SetGround(false);

		//if (m_fAccTime >= 0.4f)
		//{
		//	// 미사일 쏘기			
		//	CMissile* pMissile = Instantiate<CGuidedMissile>(GetPos() + Vec2(0.f, -50.f), LAYER_TYPE::PLAYER_PROJECTILE);
		//				
		//	pMissile->SetDir(Vec2(0.f, -1.f));

		//	m_fAccTime = 0.f;
		//}
	}

	SetPos(vPos);

	CObject::tick();
}

void CPlayer::CollisionBeginOverlap(CCollider* _pOtherCollider)
{
	_pOtherCollider->GetOwner();
}