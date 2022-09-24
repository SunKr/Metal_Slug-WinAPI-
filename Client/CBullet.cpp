#include "pch.h"
#include "CBullet.h"

#include "CResMgr.h"
#include "CImage.h"

#include "CTimeMgr.h"
#include "CEnemy.h"
#include "CCollider.h"

#include "CAnimator.h"
#include "CAnimation.h"

#include "CTimeMgr.h"
#include "CNpc.h"


CBullet::CBullet()
	: m_pImage(nullptr)
	, m_Explosion(nullptr)
	, m_fSpeed(1200.f)
	, m_vDir()
{
	AddComponent(new CAnimator);
	AddComponent(new CCollider);

	m_pImage = CResMgr::GetInst()->LoadImg(L"Bullet", L"image\\playerBullet.bmp");
	m_Explosion = CResMgr::GetInst()->LoadImg(L"Explosion", L"image\\bulletExplosion.bmp");

	GetCollider()->SetOffset(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(10.f, 10.f));

	GetAnimator()->CreateAnimation(L"Bullet", m_pImage,
		Vec2(0.f, 0.f), Vec2(24.f, 24.f), Vec2(0.f, 0.f),
		24.f, 1, 1.f);
	GetAnimator()->CreateAnimation(L"Blood", m_Explosion,
		Vec2(0.f, 0.f), Vec2(141.f, 117.f), Vec2(0.f, 0.f),
		141.f, 9, 0.05f);

	GetAnimator()->Play(L"Bullet", false);
}

CBullet::~CBullet()
{



}





void CBullet::tick()
{
	// 미사일이 향하는 방향으로 이동한다.
	Vec2 vPos = GetPos();

	vPos.x -= m_fSpeed * m_vDir.x * DT;

	

	if (m_EnemyCollision == true)
	{
		m_fAccTime += DT;
		
		GetAnimator()->Play(L"Blood", false);
		if (m_fAccTime > .1f)
		{
			DeleteObject(this);
		}
			
		
	}
	
	

	SetPos(vPos);

	CObject::tick();
}

void CBullet::render(HDC _dc)
{
	//총알 렌더링

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());


	CObject::render(_dc);
}

void CBullet::CollisionBeginOverlap(CCollider* _pOhterCollider)
{
	//적과의 충돌시 
	if (dynamic_cast<CEnemy*>(_pOhterCollider->GetOwner()))
	{
		m_EnemyCollision = true;
	}
	if (dynamic_cast<CNpc*>(_pOhterCollider->GetOwner()))
	{
		m_NpcCollision = true;
	}
}
