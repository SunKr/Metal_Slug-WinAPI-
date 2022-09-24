#include "pch.h"
#include "CBoss.h"
#include "CResMgr.h"
#include "CImage.h"
#include "CCollider.h"

#include "CEventMgr.h"
#include "CMissile.h"
#include "CRigidBody.h"

#include "CAnimator.h"
#include "CCollider.h"

#include "CScene.h"
#include "CSceneMgr.h"

#include "CTimeMgr.h"
#include "CHeliBomb.h"

#include "CKeyMgr.h"

CBoss::CBoss()
	: m_pImage(nullptr)
	, m_pPlayer(nullptr)
	, m_Speed(100.f)
	, m_Time(0.f)
{
	AddComponent(new CAnimator);
	AddComponent(new CCollider);
	//AddComponent(new CRigidBody);

	GetCollider()->SetOffset(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(267.f, 180.f));

	m_pImage = CResMgr::GetInst()->LoadImg(L"Helicopter", L"image\\Helicopter.bmp");
	GetAnimator()->CreateLowerAnimation(L"Lfly",
		m_pImage, Vec2(0.f, 0.f), Vec2(267.f, 204.f), Vec2(0.f, 0.f), 267.f, 3, 0.2f, 1);
	GetAnimator()->CreateLowerAnimation(L"LflyDown",
		m_pImage, Vec2(801.f, 0.f), Vec2(267.f, 204.f), Vec2(0.f, 0.f), 267.f, 4, 0.2f, 1);

	//우측 비행
	GetAnimator()->CreateLowerAnimation(L"Rfly",
		m_pImage, Vec2(0.f, 204.f), Vec2(267.f, 204.f), Vec2(0.f, 0.f), 267.f, 4, 0.8f, 1);
	GetAnimator()->CreateLowerAnimation(L"RflyDown",
		m_pImage, Vec2(1068.f, 204.f), Vec2(267.f, 204.f), Vec2(0.f, 0.f), 267.f, 3, 0.8f, 1);

	//Blade
	GetAnimator()->CreateAnimation(L"BladeReverse",
		m_pImage, Vec2(0.f, 408.f), Vec2(240.f, 60.f), Vec2(-30.f, -70.f), 240.f, 5, 0.2f, 1);
	GetAnimator()->CreateAnimation(L"Blade",
		m_pImage, Vec2(0.f, 468.f), Vec2(240.f, 60.f), Vec2(-30.f, -70.f), 240.f, 5, 0.2f, 1);


	GetAnimator()->PlayLower(L"Lfly", true);
	GetAnimator()->Play(L"BladeReverse", true);
}

CBoss::CBoss(const CBoss& _mon)
	: CObject(_mon)
	, m_pImage(_mon.m_pImage)
	, m_pPlayer(_mon.m_pPlayer)
{
}

CBoss::~CBoss()
{
}

void CBoss::tick()
{
	//현재 씬에 접근해서
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	//플레이어를 가져온다. 
	const vector<CObject*>& vecPlayer = pCurScene->GetObjects(LAYER_TYPE::PLAYER);
	//들어 있는 모든 플레이어를 가져와서
	Vec2 vPos; // 플레이어 위치
	Vec2 hPos; // 헬기 위치받아오기

	m_Time += DT;

	hPos = this->GetPos();
	//
	for (int i = 0; i < vecPlayer.size(); ++i)
	{
		vPos = vecPlayer[i]->GetPos(); //플레이어의 현재 위치를 가져온다.
	}

	switch(nDirection)
	{
		case DIRECTION::RIGHT:
			cDirection = DIRECTION::RIGHT;
			break;
		case DIRECTION::LEFT:
			cDirection = DIRECTION::LEFT;
			break;
	}

	// 우측에 위치
	if ((vPos.x + 50.f) - hPos.x > 0)
	{
		//일정 위치 만큼 우측으로 이동
		hPos.x += m_Speed * DT * 0.8;


		cDirection = DIRECTION::RIGHT; //현재 방향
	}
	//좌측에 위치
	else if ((vPos.x + 50.f) - hPos.x)
	{
		// 일정 위치만큼 좌측으로 이동
		hPos.x -= m_Speed * DT * 0.8;

		cDirection = DIRECTION::LEFT;
	}

	if (!isAtk)
	{
		DropBomb();
	}
	else
	{
		AddBomb();
	}


	//우측 방향이면
	if (m_Direction == DIRECTION::RIGHT && (bDirection != cDirection))
	{
		GetAnimator()->PlayLower(L"Lfly", true);
		GetAnimator()->Play(L"BladeReverse", true);
		nDirection = DIRECTION::LEFT;
	}
	//좌측이면
	else if(m_Direction == DIRECTION::LEFT && (bDirection != cDirection))
	{
		GetAnimator()->PlayLower(L"LflyDown", true);
		GetAnimator()->Play(L"Blade", true);
		nDirection = DIRECTION::RIGHT;
	}


	bDirection = cDirection;



	this->SetPos(hPos);

	CObject::tick();

}

void CBoss::render(HDC _dc)
{
	//Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());



	CObject::render(_dc);
}

void CBoss::DropBomb()
{
	static float m_Time = 0;
	if (m_Time > m_AtkRate)
	{
		m_Time = 0;
		isAtk = true;
	}
	else
		m_Time += DT;
}


//폭탄 추가
void CBoss::AddBomb()
{
	//전역 변수를 통해서 초기화는 한번만 되도록 설정한다.
	static int DropCount = 0;
	static float m_Time = 0;

	if (m_Time > m_DropRate)
	{
		m_Time = 0;
		DropCount++;

		CHeliBomb* pBomb = Instantiate<CHeliBomb>(GetPos() + Vec2(0.f, 0.f), LAYER_TYPE::ENEMY_PROJECTILE);

		Vec2 vV = pBomb->GetRigidBody()->GetVelocity();
		vV.y = +300.f;
		vV.x = 0.f;
		pBomb->GetRigidBody()->SetVelocity(vV);
		pBomb->GetRigidBody()->SetGround(false);
	}
	else
	{
		m_Time += DT;
	}
	if (DropCount == 3)
	{
		DropCount = 0;
		isAtk = false;
	}

}