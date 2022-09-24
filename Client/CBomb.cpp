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

//������
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
	//��� Ƣ�� ����ź �̹��� �����´�. 
	GranadeImage = CResMgr::GetInst()->LoadImg(L"RGranade", L"image\\RGrenade.bmp");
	//�ʹϴ� ����Ʈ 
	Effect = CResMgr::GetInst()->LoadImg(L"Effect", L"image\\GrenadeExplosion.bmp");
	// �浹ü ũ��� ��ġ ����
	GetCollider()->SetScale(Vec2(10.f, 30.f));
	GetCollider()->SetOffset(Vec2(0.f, -10.f));

	// ���� ���� ���� �Է�
	GetRigidBody()->SetMaxSpeed(200.f);
	GetRigidBody()->SetMaxGravitySpeed(1000.f);
	GetRigidBody()->SetGround(false);
	GetRigidBody()->SetGravityAccel(Vec2(0.f, 800.f));
	GetRigidBody()->SetElasticity(true);// ź�� ���� �ϵ��� ����
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

	// �̻����� ���ϴ� �������� �̵��Ѵ�.
	Vec2 vPos = GetPos();

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	CImage* pImage = nullptr;

	// Player1 Layer �� �����´�.
	const vector<CObject*>& vecCollider = pCurScene->GetObjects(LAYER_TYPE::BACKGROUNDCOLLIDER);

	for (int k = 0; k < vecCollider.size(); ++k)
	{
		pImage = ((CBackgroundCollider*)vecCollider[k])->GetImage();
	}

	//���� �ȼ��϶�
	if (pImage->GetPixelColor(this->GetPos().x, this->GetPos().y)
		== tPixel(0, 255, 0, 255)) //�÷��̾��� ��ġ�� Ư�� ������ ���
	{
		//������ ������ش�. 
		this->GetRigidBody()->SetGround(true);
		++m_BoundCount;
		if (m_BoundCount == 2) //�ι� ƨ��� 
		{
			//���� �ι� �浹�� collider ũ�� �����ʿ�

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
	// ���� �浹 ���� �ʾ�����
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
	//���� �浹�� 
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

