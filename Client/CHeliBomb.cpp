#include "pch.h"
#include "CHeliBomb.h"'

#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidBody.h"

#include "CResMgr.h"
#include "CImage.h"


#include "CScene.h"
#include "CSceneMgr.h"

#include "CBackgroundCollider.h"
#include  "CAnimation.h"

#include "CTimeMgr.h"



CHeliBomb::CHeliBomb()
	:BombImage(nullptr)
	,BombEffect(nullptr)
	,GranadeCount(0)
	,m_fSpeed(200.f)
	,m_vDir()
	,m_BoundCount(0)
	,BombDelete (false)
{
	AddComponent(new CAnimator);
	AddComponent(new CCollider);
	AddComponent(new CRigidBody);



	BombImage = CResMgr::GetInst()->LoadImg(L"Hbomb", L"image\\HelicopterBomb.bmp");
	BombEffect = CResMgr::GetInst()->LoadImg(L"HExplosion", L"image\\Explosion.bmp");

	GetCollider()->SetOffset(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(50.f, 50.f));

	// 물리 관련 정보 입력
	GetRigidBody()->SetMaxSpeed(200.f);
	GetRigidBody()->SetMaxGravitySpeed(1000.f);
	GetRigidBody()->SetGround(false);
	GetRigidBody()->SetGravityAccel(Vec2(0.f, 10.f));
	GetRigidBody()->SetElasticity(false);// 탄성 가능 하도록 설정
	GetRigidBody()->SetElastic(.0f);

	//
	GetAnimator()->CreateAnimation(L"Hbomb", BombImage,
		Vec2(0.f, 0.f), Vec2(42.f, 78.f), Vec2(0.f, 0.f),
		42.f, 7, 0.1f, 1);

	//폭발
	GetAnimator()->CreateAnimation(L"HExplosion", BombEffect,
		Vec2(0.f, 0.f), Vec2(240.f, 255.f), Vec2(0.f, -100.f),
		240.f, 29, 0.05f, 1);

	GetAnimator()->Play(L"Hbomb", true);

}

CHeliBomb::~CHeliBomb()
{


}





void CHeliBomb::tick()
{

	Vec2 vPos = GetPos();

	//vPos.y += m_fSpeed  * DT;


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
		//GetAnimator()->Play(L"HExplosion", false);
		//땅으로 만들어준다. 
		this->GetRigidBody()->SetGround(true);

		//땅과 두번 충돌시 collider 크기 변경필요

		GetCollider()->SetOffset(Vec2(0.f, 0.f));
		GetCollider()->SetScale(Vec2(0.f, 0.f));
		GetRigidBody()->SetElastic(0.f);
		GetRigidBody()->SetVelocity(Vec2(0.f, 0.f));
		if (BombDelete == false)
		{
			GetAnimator()->Play(L"HExplosion", false);
			if (GetAnimator()->getCurrentAnim() == GetAnimator()->FindAnimation(L"HExplosion"))
			{
				if (GetAnimator()->getCurrentAnim()->GetCurrentFrm() == 28)
				{
					DeleteObject(this);
				}
				else
				{
					BombDelete = true;

				}


			}
		}
	}

	
	// 땅과 충돌 하지 않았을때
	else
	{
		this->GetRigidBody()->SetGround(false);
	}
	
	

	SetPos(vPos);
		
	CObject::tick();

}

void CHeliBomb::render(HDC _dc)
{

	CObject::render(_dc);
}

void CHeliBomb::CollisionBeginOverlap(CCollider* _pOhterCollider)
{
}

