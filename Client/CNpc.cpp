#include "pch.h"
#include "CNpc.h"


#include "CEngine.h"
#include "CImage.h"
#include "CResMgr.h"
#include "CEventMgr.h"

#include "CComponent.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CRigidBody.h"

#include "CTimeMgr.h"
#include "CAnimation.h"
#include "CAnimationLower.h"

#include "CKeyMgr.h"
#include "CCamera.h"

#include "CScene.h"
#include "CSceneMgr.h"

#include "CBackgroundCollider.h"
#include "CEnemy.h"

#include "CBomb.h"
#include "CPlayer1.h"
#include "CEnemyBomb.h"
#include "CBullet.h"


CNpc::CNpc()
	:m_NpcImage(nullptr)
	, m_binding(true)
	, m_dropItem(false)

{
	AddComponent(new CAnimator);
	AddComponent(new CCollider);
	//AddComponent(new CRigidBody);

	//�浹ü
	GetCollider()->SetOffset(Vec2(0.f, 10.f));
	GetCollider()->SetScale(Vec2(70.f, 90.f));

	//npc ���� �̹��� �޾ƿ�
	m_NpcImage = CResMgr::GetInst()->LoadImg(L"NPC", L"image\\NPC.bmp");

	//�����ٿ� ���� �ִ� npc 
	GetAnimator()->CreateAnimation(L"binding", m_NpcImage,
		Vec2(0.f, 0.f), Vec2(128.f, 105.f), Vec2(0.f, 0.f),
		128.f, 5, 0.3f);
	//������ Ǫ�� npc
	GetAnimator()->CreateAnimation(L"unbinding", m_NpcImage,
		Vec2(640.f, 0.f), Vec2(128.f, 105.f), Vec2(0.f, 0.f),
		128.f, 4, 0.1f);
	//���� npc
	GetAnimator()->CreateAnimation(L"fall", m_NpcImage,
		Vec2(0.f, 516.f), Vec2(114.f, 128.f), Vec2(0.f, 0.f),
		114.f, 5, 0.2f);
	//���� ���� �ȱ�
	GetAnimator()->CreateAnimation(L"LWalk", m_NpcImage,
		Vec2(0.f, 654.f), Vec2(102.f, 114.f), Vec2(0.f, 0.f),
		102.f, 12, 0.15f);
	//�浹�� ������ ��ġ��
	GetAnimator()->CreateAnimation(L"ShowItem", m_NpcImage,
		Vec2(0.f, 775.f), Vec2(144.f, 105.f), Vec2(-30.f, 0.f),
		144.f, 11, 0.15f);
	//�漺
	GetAnimator()->CreateAnimation(L"Salute", m_NpcImage,
		Vec2(0.f, 892.f), Vec2(123.f, 106.f), Vec2(0.f, 0.f),
		123.f, 14, 0.15f);
	//����
	GetAnimator()->CreateAnimation(L"LRun", m_NpcImage,
		Vec2(0.f, 1001.f), Vec2(127.f, 124.f), Vec2(0.f, 0.f),
		127.f, 8, 0.15f);

	GetAnimator()->Play(L"binding", true);

}

CNpc::CNpc(const CNpc& _npc)
	 : CObject(_npc)
	, m_NpcImage(_npc.m_NpcImage)
{


}

CNpc::~CNpc()
{


}

void CNpc::tick()
{




	CObject::tick();
}


void CNpc::render(HDC _dc)
{




	CObject::render(_dc);
}


//�浹�� NPC ���� �ϵ��� ���� 
void CNpc::CollisionBeginOverlap(CCollider* _pOhterCollider)
{
	//�Ѿ˰� �ε����� �Ǵ� ��� ���ε� Ǭ��. 
	if (dynamic_cast<CBullet*>(_pOhterCollider->GetOwner()))
	{
		GetAnimator()->Play(L"LWalk", true);
	}
}






//NPC ������ ���� ������
void CNpc::Move()
{

}