#include "pch.h"
#include "CBomb.h"

#include "CImage.h"
#include "CResMgr.h"

#include "CScene.h"
#include "CSceneMgr.h"
#include "CBackgroundCollider.h"

#include "CRigidBody.h"
#include "CCollider.h"
#include "CAnimator.h"

#include "CAnimation.h"

#include "CEnemy.h"

//생성자
CBomb::CBomb()
	:GranadeImage(nullptr)
	,GranadeCount(10)
	,m_fSpeed(0.f)
	,m_vDir ()
{
	AddComponent(new CRigidBody);
	AddComponent(new CCollider);
	AddComponent(new CAnimator);
	//AddComponent(new CAnimator);
	//우로 튀는 수류탄 이미지 가져온다. 
	GranadeImage = CResMgr::GetInst()->LoadImg(L"RGranade", L"image\\RGrenade.bmp");
	//터니는 이펙트 
	Effect = CResMgr::GetInst()->LoadImg(L"Effect", L"image\\GrenadeExplosion.bmp");
	// 충돌체 크기및 위치 생성
	GetCollider()->SetScale(Vec2(10.f, 30.f));
	GetCollider()->SetOffset(Vec2(0.f, -10.f));

	// 물리 관련 정보 입력
	GetRigidBody()->SetMaxSpeed(200.f);
	GetRigidBody()->SetMaxGravitySpeed(1000.f);
	GetRigidBody()->SetGround(false);
	GetRigidBody()->SetGravityAccel(Vec2(0.f, 800.f));
	GetRigidBody()->SetElasticity(true);// 탄성 가능 하도록 설정
	GetRigidBody()->SetElastic(2.0f);


	GetAnimator()->CreateAnimation(L"Grenade", GranadeImage,
		Vec2(0.f, 0.f), Vec2(57.f, 57.f), Vec2(0.f, 0.f),
		57.f,16, 0.1f);
	GetAnimator()->CreateAnimation(L"Explosion", Effect,
		Vec2(0.f, 0.f), Vec2(150.f, 321.f), Vec2(0.f, -140.f),
		150.f,28, 0.05f);


	GetAnimator()->Play(L"Grenade", true);
}

CBomb::~CBomb()
{

}


void CBomb::tick()
{

	// 미사일이 향하는 방향으로 이동한다.
	Vec2 vPos = GetPos();

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	CImage* pImage = nullptr;

	// Player1 Layer 를 가져온다.
	const vector<CObject*>& vecCollider = pCurScene->GetObjects(LAYER_TYPE::BACKGROUNDCOLLIDER);

	for (int k = 0; k < vecCollider.size(); ++k)
	{
		pImage = ((CBackgroundCollider*)vecCollider[k])->GetImage();
	}

	//땅위 픽셀일때
	if (pImage->GetPixelColor(this->GetPos().x, this->GetPos().y)
		== tPixel(0, 255, 0, 255)) //플레이어의 위치가 특정 색상일 경우
	{
		//땅으로 만들어준다. 
		this->GetRigidBody()->SetGround(true);
		++m_BoundCount;
		if (m_BoundCount == 2) //두번 튕기면 
		{
			//땅과 두번 충돌시 collider 크기 변경필요

			GetCollider()->SetOffset(Vec2(0.f, 0.f));
			GetRigidBody()->SetElastic(0.f);
			GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
			if (BombDelete == false)
			{
				GetAnimator()->Play(L"Explosion", false);
				if (GetAnimator()->getCurrentAnim() == GetAnimator()->FindAnimation(L"Explosion"))
				{
					if (GetAnimator()->getCurrentAnim()->IsFinish())
						DeleteObject(this);
						BombDelete = true;

				}
			}
		}

		if (m_BoundCount == 3)
		{
			if (this->GetRigidBody()->IsGround())
			{
				GetCollider()->SetOffset(Vec2(0.f, 0.f));
			}
		}
		
	}
	// 땅과 충돌 하지 않았을때
	else
	{
		this->GetRigidBody()->SetGround(false);
	}

	//vPos.x += m_fSpeed * m_vDir.x * DT;
	//vPos.y += m_fSpeed * m_vDir.y * DT;

	SetPos(vPos);

	CObject::tick();
}

void CBomb::render(HDC _dc)
{

	CObject::render(_dc);
}

void CBomb::CollisionBeginOverlap(CCollider* _pOhterCollider)
{
	//적과 충돌시 
	if (dynamic_cast<CEnemy*>(_pOhterCollider->GetOwner()))
	{
		//this->GetRigidBody()->SetGround(true);
		GetCollider()->SetOffset(Vec2(0.f, 0.f));
		GetRigidBody()->SetElastic(0.f);
		GetRigidBody()->SetVelocity(Vec2(0.f, 0.f)); 
		if (BombDelete == false)
		{
			GetAnimator()->Play(L"Explosion", false);


			if (GetAnimator()->getCurrentAnim() == GetAnimator()->FindAnimation(L"Explosion"))
			{
				if (GetAnimator()->getCurrentAnim()->IsFinish())
					
					DeleteObject(this);
					BombDelete = true;
			}
		}
	}
}

