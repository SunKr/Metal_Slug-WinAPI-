#include "pch.h"
#include "Game_Scene.h"

#include "CPlayer.h"
#include "CMonster.h"

#include "CEngine.h"
#include "CCollisionMgr.h"

#include "CKeyMgr.h"
#include "CCamera.h"
#include "CForce.h"

#include "CGround.h"
#include "CBackground.h"
#include "CAnimator.h"

#include "CResMgr.h"
#include "CComponent.h"

#include "CImage.h"

#include "CTimeMgr.h"

#include "CPlayer1.h"
#include "CEnemy.h"
#include "CBoss.h"
#include "CGUI.h"

#include "CBackgroundCollider.h"
#include "CRigidBody.h"

#include "CRock.h"
#include "CNpc.h"

#include "CResMgr.h"
#include "CSound.h"
#include "CSoundMgr.h"

Game_Scene::Game_Scene()
	:m_fAccTime(0.f)
{
}

Game_Scene::~Game_Scene()
{
}

void Game_Scene::enter()
{
	Vec2 CamLook;

	CamLook = CCamera::GetInst()->GetLookAt();

	CamLook.y = CamLook.y + 204.f;

	CCamera::GetInst()->SetLookAt(CamLook);

	
	//Sound Test
	CSound* pBGM1 = CResMgr::GetInst()->FindSound(L"BGM_01");
	if (nullptr != pBGM1)
	{
		//pBGM->Play(true);		
		pBGM1->PlayToBGM();
		pBGM1->SetPosition(0.f);
	}

	// Marco
	CObject* p1 = new CPlayer1;
	p1->SetPos(Vec2(300.f, 600.f));
	AddObject(p1, LAYER_TYPE::PLAYER);


	CCamera::GetInst()->SetTargetObject(p1);


	



	/*
	첫번째 백그라운드 폭포1
	*/
	CObject* pBackGround1 = new CBackground;
	pBackGround1->SetPos(Vec2(0.f, 0.f));
	pBackGround1->setBGType(BGTYPE::Map);
	pBackGround1->GetBackground(pBackGround1);
	AddObject(pBackGround1, LAYER_TYPE::BACKGROUND);
	
	//첫번째 배경 Animation
	//CObject* pBackGround3 = pBackGround1->Clone();
	//pBackGround3->SetPos(Vec2(0.f, 0.f));
	//pBackGround3->setBGType(BGTYPE::map4_2);
	//pBackGround3->GetBackground(pBackGround3);
	//AddObject(pBackGround3, LAYER_TYPE::BACKGROUND);
	////두번째 배경 Animation
	//CObject* pBackGround = pBackGround1->Clone();
	//pBackGround->SetPos(Vec2(0.f, 0.f));
	//pBackGround->setBGType(BGTYPE::map4_3);
	//pBackGround->GetBackground(pBackGround);
	//AddObject(pBackGround, LAYER_TYPE::BACKGROUND);


	CObject* pBackCollider = new CBackgroundCollider;
	pBackCollider->SetPos(Vec2(0.f, 0.f));
	pBackCollider->SetScale(Vec2(0.f, 0.f));
	AddObject(pBackCollider, LAYER_TYPE::BACKGROUNDCOLLIDER);

	//두번째 배경
	//CObject* pBackGround2 = pBackGround1->Clone();
	//pBackGround2->SetPos(Vec2(0.f, 0.f));
	//pBackGround2->setBGType(BGTYPE::Map1); //두번째 배경
	//pBackGround2->GetBackground(pBackGround2);
	//AddObject(pBackGround2, LAYER_TYPE::BACKGROUND);




	//if (CCamera::GetInst()->GetTargetObject()->GetPos().x > 
	//	(CCamera::GetInst()->GetLookAt().x - 90.f))
	//{
	//	if (m_fAccTime > 0.5f)
	//		m_vLook.x += DT * m_CamSpeed;

	//	m_fAccTime = 0.f;
	//}
	
	// 적(군인) 
	/*CObject* enemySoldier = new CEnemy;
	enemySoldier->SetPos(Vec2(700.f, 600.f));
	AddObject(enemySoldier, LAYER_TYPE::ENEMY);

	CObject* enemySoldier1 = enemySoldier->Clone();
	enemySoldier1->SetPos(Vec2(1000.f, 600.f));
	AddObject(enemySoldier1, LAYER_TYPE::ENEMY);

	CObject* enemySoldier2 = enemySoldier->Clone();
	enemySoldier2->SetPos(Vec2(1200.f, 600.f));
	AddObject(enemySoldier2, LAYER_TYPE::ENEMY);*/

	//CObject* rock = new CRock;
	//rock->SetPos(Vec2(1700.f,700.f));
	//AddObject(rock, LAYER_TYPE::ROCK);

	//CObject* npc = new CNpc;
	//npc->SetPos(Vec2(500.f, 700.f));
	//AddObject(npc, LAYER_TYPE::NPC);

	////헬기 Boss
	//CObject* Helicopter = new CBoss;
	//Helicopter->SetPos(Vec2(300.f, 400.f));
	//Helicopter->SetScale(Vec2(50.f, 50.f));
	//AddObject(Helicopter, LAYER_TYPE::ENEMY);


	CObject* UI = new CGUI;
	UI->SetPos(Vec2(-450.f, -300.f));
	UI->SetScale(Vec2(50.f, 50.f));
	AddObject(UI, LAYER_TYPE::GUI);
	

	// 충돌 체크
	CCollisionMgr::GetInst()->clear();

	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::ENEMY_PROJECTILE);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::MONSTER, LAYER_TYPE::PLAYER_PROJECTILE);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::MONSTER, LAYER_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::ENEMY);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::DEFAULT);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::ENEMY, LAYER_TYPE::DEFAULT);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::ENEMY, LAYER_TYPE::PLAYER_PROJECTILE);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER, LAYER_TYPE::ROCK);
	CCollisionMgr::GetInst()->CollisionLayerCheck(LAYER_TYPE::PLAYER_PROJECTILE, LAYER_TYPE::NPC);

}

void Game_Scene::exit()
{
	DeleteAllObject();
	CCollisionMgr::GetInst()->clear();
}

void Game_Scene::tick()
{
	CScene::tick();

	//Vec2 CamLook;
	//CObject* target = CCamera::GetInst()->GetTargetObject();
	//CamLook = CCamera::GetInst()->GetLookAt();

	//if (CCamera::GetInst()->GetTargetObject()->GetPos().x > (CamLook.x - 90.f))
	//{
	//	if (m_fAccTime > 0.5f)
	//		CamLook.x += DT * 500.f;

	//	m_fAccTime = 0.f;
	//}

	//CCamera::GetInst()->SetLookAt(CamLook);


	// 마우스 클릭한 위치에 Force 생성	
	if (IsTap(KEY_TYPE::LBTN))
	{
		Vec2 vMousePos = CKeyMgr::GetInst()->GetMousePos();
		Vec2 vObjectPos = CCamera::GetInst()->GetRealPos(vMousePos);

		CForce* pForce = Instantiate<CForce>(vObjectPos, LAYER_TYPE::FORCE);
		pForce->SetForceInfo(500.f, 400.f, 0.2f);
	}





	/*if (IsTap(KEY_TYPE::ENTER))
	{
		SceneChange(SCENE_TYPE::TOOL);
	}*/
}

