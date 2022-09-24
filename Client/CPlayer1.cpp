#include "pch.h"
#include "CPlayer1.h"

#include "CEngine.h"
#include "CImage.h"
#include "CResMgr.h"
#include "CEventMgr.h"

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
#include "CBullet.h"

#include "CHeliBomb.h"

#include "CSound.h"
#include "CSoundMgr.h"


CPlayer1::CPlayer1()
	: m_pImage(nullptr)
	, m_pImageLeft(nullptr)
	, m_fSpeed(100.f)
	, m_fAccTime(0.f)
	, eArmorType(ARMOR_TYPE::NORMAL) //�Ϲ� ARM ���� ���� (�Ϲ���)
	, m_BulletCount(200) //Machine Gun �Ѿ˼� �� 0���� �����Ѵ�.
	, m_Bomb(10)  //�ʱ� ��ź���� 10���� �����Ѵ�.
	, m_knife(false)
{
	// �ִϸ����� ������Ʈ �߰�
	AddComponent(new CCollider);
	AddComponent(new CAnimator);
	AddComponent(new CRigidBody);

	GetCollider()->SetScale(Vec2(90.f, 120.f));
	GetCollider()->SetOffset(Vec2(0.f, -65.f));
	
	m_fAccTime += DT;

	static CSound* pBGM2 = CResMgr::GetInst()->FindSound(L"MissionStart");
	if (nullptr != pBGM2)
	{
		pBGM2->Play(true);
		//pBGM2->PlayToBGM();
		pBGM2->Stop(true);
		pBGM2->SetPosition(0.f);
	}


	//�̹��� �����ö� ���� ä�� ����ִ��� Ȯ�� �Ұ�
	//m_pImage = CResMgr::GetInst()->LoadImg(L"PlayerAtlas", L"image\\player1.bmp");
	m_pImage = CResMgr::GetInst()->LoadImg(L"PlayerAtlas", L"image\\player1_3.bmp");

	// ��ȯ �ɶ� 
	GetAnimator()->CreateAnimation(L"Summon", m_pImage, Vec2(0.f, 0.f),
		Vec2(93.f, 720.f), Vec2(-50.f, -200.f), 93.f, 6, 0.1f);
	//���  �Ʒ��� ���̴� ���
	GetAnimator()->CreateAnimation(L"Crounch", m_pImage, Vec2(0.f, 1101.f),
		Vec2(87.f, 123.f), Vec2(6.f, -60.f), 87.f, 4, 0.1f); 
	// �Ʒ��� ���̴°� ���� ���
	GetAnimator()->CreateLowerAnimation(L"Crounch1", m_pImage, Vec2(0.f, 1224.f),
		Vec2(93.f, 81.f), Vec2(0.f, -30.f), 93.f, 4, 0.1f, 1);
	// �Ʒ��� ���̰� �ȱ�
	GetAnimator()->CreateAnimation(L"CrounchWalking", m_pImage, Vec2(0.f, 1305.f),
		Vec2(105.f, 72.f), Vec2(18.f, -35.f), 105.f, 7, 0.1f);
	// Crounch and shooting
	GetAnimator()->CreateAnimation(L"CrounchShooting", m_pImage, Vec2(0.f, 1740.f),
		Vec2(156.f, 81.f), Vec2(38.f, -35.f), 156.f, 10, 0.1f);
	// Crounch and Knife
	GetAnimator()->CreateAnimation(L"CrounchKnife", m_pImage, Vec2(0.f, 2127.f),
		Vec2(126.f, 105.f), Vec2(5.f, -25.f), 126.f, 4, 0.1f);


	//===============��ü====================

	//��ü Standing  �Ϸ�
	GetAnimator()->CreateLowerAnimation(L"LowerBody", m_pImage, Vec2(0.f, 4350.f),
		Vec2(63.f, 48.f), Vec2(0.f, -20.f), 63.f, 4, 0.5f, true);
	// ��ü Running �Ϸ�
	GetAnimator()->CreateLowerAnimation(L"Running", m_pImage, Vec2(0.f, 4398.f),
		Vec2(93.f, 60.f), Vec2(14.f, -28.f), 93.f, 12, 0.1f, true);
	// ��ü Jumping (�Ʒ� �� ��ü)
	GetAnimator()->CreateLowerAnimation(L"Jumping", m_pImage, Vec2(6.f, 4458.f),
		Vec2(69.f, 72.f), Vec2(3.f, 0.f), 69.f, 6, 0.1f, true);
	// ��ü Jumping_Running
	GetAnimator()->CreateLowerAnimation(L"JumpRunning", m_pImage, Vec2(0.f, 4530.f),
		Vec2(99.f, 63.f), Vec2(18.f, -18.f), 99.f, 6, 0.1f, true);
	
	
	//��ü 12��
	GetAnimator()->CreateAnimation(L"UpperBody", m_pImage, Vec2(0.f, 807.f),
		Vec2(96.f, 84.f), Vec2(15.f, -67.f), 96.f, 12, 0.5f);
	// ��ü �ٴ� ���
	GetAnimator()->CreateAnimation(L"UpperBodyJumping", m_pImage, Vec2(0.f, 891.f),
		Vec2(96.f, 105.f), Vec2(0.f, -60.f), 96.f, 3, 0.1f);
	// ��ü �ѽ�� ��� ���� line10 104x52 ����(0,918) ������ 10��
	GetAnimator()->CreateAnimation(L"Shooting", m_pImage, Vec2(0.f, 1386.f),
		Vec2(156.f, 69.f), Vec2(40.f, -70.f), 156.f, 10, 0.05f);
	// ��ü ���� �ѽ�� ��� line11 58x138 ����(0,970) ������ 10��
	GetAnimator()->CreateAnimation(L"ShootingUpper", m_pImage, Vec2(0.f, 1464.f),
		Vec2(87.f, 198.f), Vec2(10.f, -140.f), 87.f, 10, 0.1f);
	// ���� ���� ���� line12	120x48	������(0,1108) ������ 4��
	GetAnimator()->CreateAnimation(L"JumpShootingLeft", m_pImage, Vec2(0.f, 1662.f),
		Vec2(180.f, 71.f), Vec2(-49.f, -62.f), 180, 4, 0.1f);
	// ������ �Ʒ��� ��� ��
	GetAnimator()->CreateAnimation(L"JumpShootingDown", m_pImage, Vec2(0.f, 1821.f),
		Vec2(69.f, 164.f), Vec2(0.f, -5.f), 69, 5, 0.1f);
	// �Ʒ��� ����
	GetAnimator()->CreateAnimation(L"ShootingDown", m_pImage, Vec2(345.f, 1821.f),
		Vec2(69.f, 164.f), Vec2(0.f, -5.f), 69, 1, 0.1f);
	//��ź ������
	GetAnimator()->CreateAnimation(L"Throw", m_pImage, Vec2(0.f, 3525.f),
		Vec2(87.f, 87.f), Vec2(0.f, -60.f), 97.f, 6, 0.1f);
	//���� ��
	GetAnimator()->CreateAnimation(L"Upper", m_pImage, Vec2(783.f, 1464.f),
		Vec2(87.f, 198.f), Vec2(15.f, -140.f), 97.f, 1, 0.1f);


	//===============��ü========================
	//Machine Gun
	GetAnimator()->CreateAnimation(L"MachineGunStanding", m_pImage, Vec2(0.f, 2232.f),
		Vec2(111.f, 87.f), Vec2(0.f, -65.f), 111, 1, 0.1f);


		
	//Į 0, 2031 ��ü
	GetAnimator()->CreateAnimation(L"Knife", m_pImage, Vec2(0.f, 1983.f),
		Vec2(132.f, 146.f), Vec2(-62.f, -65.f), 132.f, 6,  0.1f);

	//���� �ִϸ��̼� ����
	ImageAnimation();


	GetRigidBody()->SetMaxSpeed(200.f);
	GetRigidBody()->SetMaxGravitySpeed(1000.f);
	GetRigidBody()->SetGround(false);
	GetRigidBody()->SetGravityAccel(Vec2(0.f, 800.f));
	GetRigidBody()->SetElasticity(false);// ź�� �Ұ��� �ϵ��� ����
	GetRigidBody()->SetElastic(1.f);

	//ĳ���� ��ȯ
	GetAnimator()->Play(L"UpperBody", false);
	GetAnimator()->PlayLower(L"LowerBody", false);
	bLower = LOWERSTATE::LSTAND;
	bUpper = UPPERSTATE::STAND;
	pDirection = DIRECTION::RIGHT;
	//ĳ���� ��ü
	//GetAnimator()->PlayLower(L"Jumping", true);
	//ī�޶� �÷��̾� ��ȯ ���� true �� ����
	CCamera::GetInst()->setSummon(true);

	//ī�޶� ���� �ٴϵ��� ����
	CCamera::GetInst()->SetTargetObject(this);


}

CPlayer1::~CPlayer1()
{

	
}


void CPlayer1::ImageAnimation()
{
	//���� ���� ���� �ִϸ��̼� �̹����� �޾ƿ´�.
	m_pImageLeft = CResMgr::GetInst()->LoadImg(L"PlayerLeft", L"image\\player2.bmp");

	//��ü
	GetAnimator()->CreateReverseLowerAnimation(L"LowerBodyLeft", m_pImageLeft, Vec2(0.f, 4350.f),
		Vec2(63.f, 48.f), Vec2(0.f, -20.f), 63.f, 4, 0.5f, true);
	// ��ü Running �Ϸ�
	GetAnimator()->CreateReverseLowerAnimation(L"RunningLeft", m_pImageLeft, Vec2(0.f, 4398.f),
		Vec2(93.f, 60.f), Vec2(-8.f, -28.f), 93.f, 12, 0.1f, true);
	// ��ü Jumping (�Ʒ� �� ��ü)
	GetAnimator()->CreateReverseLowerAnimation(L"JumpingLeft", m_pImageLeft, Vec2(6.f, 4458.f),
		Vec2(69.f, 72.f), Vec2(3.f, -30.f), 69.f, 6, 0.1f, true);
	// ��ü Jumping_Running
	GetAnimator()->CreateReverseLowerAnimation(L"JumpRunningLeft", m_pImageLeft, Vec2(0.f, 4530.f),
		Vec2(99.f, 63.f), Vec2(0.f, -20.f), 99.f, 6, 0.1f, true);


	//��ü 12��
	GetAnimator()->CreateReverseAnimation(L"UpperBodyLeft", m_pImageLeft, Vec2(0.f, 807.f),
		Vec2(96.f, 84.f), Vec2(-5.f, -70.f), 96.f, 12, 0.5f, 1);
	// ��ü �ٴ� ���
	GetAnimator()->CreateAnimation(L"UpperBodyJumpingLeft", m_pImageLeft, Vec2(0.f, 891.f),
		Vec2(96.f, 105.f), Vec2(-5.f, -60.f), 96.f, 3, 0.1f, 1);
	// ��ü �ѽ�� ��� ���� line10 104x52 ����(0,918) ������ 10��
	GetAnimator()->CreateReverseAnimation(L"ShootingLeft", m_pImageLeft, Vec2(0.f, 1386.f),
		Vec2(156.f, 69.f), Vec2(-45.f, -71.f), 156.f, 10, 0.05f, 1);
	// ��ü ���� �ѽ�� ��� line11 58x138 ����(0,970) ������ 10��
	GetAnimator()->CreateReverseAnimation(L"ShootingUpperLeft", m_pImageLeft, Vec2(0.f, 1464.f),
		Vec2(87.f, 198.f), Vec2(0.f, -140.f), 87.f, 10, 0.1f, 1);
	// ���� ���� ���� line12	120x48	������(0,1108) ������ 4��
	GetAnimator()->CreateReverseAnimation(L"JumpShootingLeftLeft", m_pImageLeft, Vec2(0.f, 1662.f),
		Vec2(180.f, 71.f), Vec2(-49.f, -62.f), 180, 4, 0.1f, 1);
	// ������ �Ʒ��� ��� ��
	GetAnimator()->CreateReverseAnimation(L"JumpShootingDownLeft", m_pImageLeft, Vec2(69.f, 1821.f),
		Vec2(69.f, 164.f), Vec2(0.f, -5.f), 69, 5, 0.1f, 1);
	// �Ʒ��� ����
	GetAnimator()->CreateAnimation(L"ShootingDownLeft", m_pImageLeft, Vec2(0.f, 1821.f),
		Vec2(69.f, 164.f), Vec2(0.f, -5.f), 69, 1, 0.1f, 1);
	//��ź ������
	GetAnimator()->CreateReverseAnimation(L"ThrowLeft", m_pImageLeft, Vec2(0.f, 3525.f),
		Vec2(87.f, 87.f), Vec2(0.f, -30.f), 97.f, 6, 0.1f, 1);
	//���� ��
	GetAnimator()->CreateAnimation(L"UpperLeft", m_pImageLeft, Vec2(0.f, 1464.f),
		Vec2(87.f, 198.f), Vec2(0.f, -140.f), 97.f, 1, 0.1f, 1);

}


void CPlayer1::Grenade()
{
	//��ź ���������� �۵��ϵ����Ѵ�.
	if (m_Bomb > 0)
	{
		// ��ź�� ������ �Ǹ� ��ź�� ������ �پ� ���. 
		--m_Bomb;
	}
}

void CPlayer1::tick()
{
	m_fAccTime += DT;

	static CSound* pBGM2 = CResMgr::GetInst()->FindSound(L"MissionStart");
	if (nullptr != pBGM2)
	{
		if(m_fAccTime > 1.1)
		pBGM2->Stop(true);
	}


	// Ű�Է¿� ���� �̵�
	Vec2 vPos = GetPos();


	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene(); 
	CImage* pImage = nullptr; 
	const vector<CObject*>& vecCollider = pCurScene->GetObjects(LAYER_TYPE::BACKGROUNDCOLLIDER); 
	for (int k = 0; k < vecCollider.size(); ++k)
	{
		pImage = ((CBackgroundCollider*)vecCollider[k])->GetImage(); 
	}
	if (pImage->GetPixelColor(this->GetPos().x, this->GetPos().y)
		== tPixel(0, 255, 0, 255))
	{
		this->GetRigidBody()->SetGround(true); 
	}
	else
	{
		this->GetRigidBody()->SetGround(false); 
	}


	//��ü
	switch (nUpper)
	{
	case UPPERSTATE::STAND:
		pUpper = UPPERSTATE::STAND;
		break;
	case UPPERSTATE::SHOOT:
		pUpper = UPPERSTATE::SHOOT;
		break;
	case UPPERSTATE::JUMP:
		pUpper = UPPERSTATE::JUMP;
		break;
	case UPPERSTATE::UPPERGUN:
		pUpper = UPPERSTATE::UPPERGUN;
		break;
	case UPPERSTATE::UPPERSHOOTING:
		pUpper = UPPERSTATE::UPPERSHOOTING;
		break;
	case UPPERSTATE::SHOOTINGDOWN:
		pUpper = UPPERSTATE::SHOOTINGDOWN;
		break;
	case UPPERSTATE::SHOOTINGLOWER:
		pUpper = UPPERSTATE::SHOOTINGLOWER;
		break;
	case UPPERSTATE::THROWINGBOMB:
		pUpper = UPPERSTATE::THROWINGBOMB;
		break;
	default:
		break;
	}

	//��ü
	switch (nLower)
	{
	case LOWERSTATE::LSTAND:
		pLower = LOWERSTATE::LSTAND;
		break;
	case LOWERSTATE::LRUN:
		pLower = LOWERSTATE::LRUN;
		break;
	case LOWERSTATE::LJUMP:
		pLower = LOWERSTATE::LJUMP;
		break;
	case LOWERSTATE::LUNDERJUMP:
		pLower = LOWERSTATE::LUNDERJUMP;
		break;
	}


	//��ü ��ü �и�
	if (IsPressed(KEY_TYPE::RIGHT))
	{
		GetRigidBody()->AddForce(Vec2(500.f, 0.f));
	}
	if (IsPressed(KEY_TYPE::LEFT))
	{
		GetRigidBody()->AddForce(Vec2(-500.f, 0.f));
	}

	if (IsTap(KEY_TYPE::G) && GetRigidBody()->IsGround()) //����ź ��ô
	{
		if (m_Bomb > 0)
		{
			if (m_fAccTime >= 0.1f)
			{
				nUpper = UPPERSTATE::THROWINGBOMB;
				// �̻��� ���			
				CBomb* pBomb = Instantiate<CBomb>(GetPos() + Vec2(0.f, -50.f), LAYER_TYPE::PLAYER_PROJECTILE);

				Vec2 vV = pBomb->GetRigidBody()->GetVelocity();
				vV.y = -500.f;
				vV.x = +500.f;
				pBomb->GetRigidBody()->SetVelocity(vV);
				pBomb->GetRigidBody()->SetGround(false);

				m_fAccTime = 0.f;
				//����ź ���� �ϳ��� �ٿ��ش�. 
				Grenade();
			}
		}

	}
	else if (pUpper == UPPERSTATE::THROWINGBOMB && GetRigidBody()->IsGround() 
		&& GetAnimator()->getCurrentAnim()->IsFinish()		)
	{
		nUpper = UPPERSTATE::STAND;
	}

	//����( ���� �������� ��쿡�� �ۼ� �ֵ��� ����)
	if (GetRigidBody()->IsGround())
	{
		if (IsTap(KEY_TYPE::SPACE))
		{
			Vec2 vV = GetRigidBody()->GetVelocity();
			vV.y = -500.f;
			GetRigidBody()->SetVelocity(vV);
			GetRigidBody()->SetGround(false);
			//�� ��ü ����
			nUpper = UPPERSTATE::JUMP;	 // ��ü
			nLower = LOWERSTATE::LJUMP; // ��ü
		}
		//���� ���� ������ ��ҽ� ���ִ� �ڼ�
		else if (pLower == LOWERSTATE::LJUMP && GetRigidBody()->IsGround())
		{
			//�� ��ü ����
			nUpper = UPPERSTATE::STAND;	 // ��ü
			nLower = LOWERSTATE::LSTAND; // ��ü
		}
	}
	




	// ��ü ���� run
	if (IsTap(KEY_TYPE::RIGHT) && GetRigidBody()->IsGround())
	{
		nLower = LOWERSTATE::LRUN; //��ü �޸�����
		pDirection = DIRECTION::RIGHT;
	}
	else if (IsRelease(KEY_TYPE::RIGHT) && pLower == LOWERSTATE::LRUN
		&& GetRigidBody()->IsGround())
	{
		nUpper = UPPERSTATE::STAND;	 // ��ü
		nLower = LOWERSTATE::LSTAND; // ��ü
	}




	// ��ü ���� run
	if (IsTap(KEY_TYPE::LEFT) && GetRigidBody()->IsGround() && pLower != LOWERSTATE::LRUN)
	{
		nLower = LOWERSTATE::LRUN; //��ü �޸�����
		pDirection = DIRECTION::LEFT;
	}
	else if (IsRelease(KEY_TYPE::LEFT) && pLower == LOWERSTATE::LRUN
		&& GetRigidBody()->IsGround())
	{
		nUpper = UPPERSTATE::STAND;	 // ��ü
		nLower = LOWERSTATE::LSTAND; // ��ü
	}


	if (IsTap(KEY_TYPE::UP) && GetRigidBody()->IsGround())
	{
		nUpper = UPPERSTATE::UPPERGUN; //�� ���� ���
	}
	else if (IsRelease(KEY_TYPE::UP) && pUpper == UPPERSTATE::UPPERGUN
		&& GetRigidBody()->IsGround())
	{
		nUpper = UPPERSTATE::STAND;
	}


	//��ü ���� �Լ�(��)
	if ((IsTap(KEY_TYPE::X)) && GetRigidBody()->IsGround())
	{
		if (pUpper == UPPERSTATE::UPPERGUN)
		{
			nUpper = UPPERSTATE::UPPERSHOOTING;
		}
		else //�Ϲ� ���� ��
		{
			nUpper = UPPERSTATE::SHOOT; //��ü
		}

	}
	else if (IsTap(KEY_TYPE::X) && !GetRigidBody()->IsGround() &&
		pUpper == UPPERSTATE::SHOOTINGDOWN && pLower == LOWERSTATE::LUNDERJUMP) //x ������ ���߻��¿��� �Ʒ�����
	{
		nUpper = UPPERSTATE::SHOOTINGLOWER;
		//�Ʒ��� �ѽ�� ���� �Բ� �Ʒ��� �Ѿ� �߻�

	}
	else if (IsRelease(KEY_TYPE::X) && pUpper == UPPERSTATE::UPPERSHOOTING   //������ ��� ���� XŰ release�߻���
		&& GetRigidBody()->IsGround())
	{
		nUpper = UPPERSTATE::UPPERGUN;
	}
	else if (IsRelease(KEY_TYPE::X) && pUpper == UPPERSTATE::SHOOT
		&& GetRigidBody()->IsGround())
	{
		nUpper = UPPERSTATE::STAND;	
	}
	else if (IsRelease(KEY_TYPE::X) && pUpper == UPPERSTATE::SHOOTINGLOWER) //xŰ Ǯ���� �� �ڼ��� ����
	{
		nUpper = UPPERSTATE::SHOOTINGDOWN;
	}

	//�Ʒ��� ����
	if (pUpper == UPPERSTATE::JUMP && pLower == LOWERSTATE::LJUMP)
	{
		if (IsTap(KEY_TYPE::DOWN))
		{
			//���� ���¿��� �Ʒ���ư�� ���� �Ʒ��� �������� ����
			nUpper = UPPERSTATE::SHOOTINGDOWN;
			nLower = LOWERSTATE::LUNDERJUMP;
		}
	}


	//���� ���°� �Ʒ� ���̸� ���� ��� ���� ���ĵ� ���·� ����
	if (pUpper == UPPERSTATE::SHOOTINGDOWN && pLower == LOWERSTATE::LUNDERJUMP && GetRigidBody()->IsGround())
	{
		nUpper = UPPERSTATE::STAND;
		nLower = LOWERSTATE::LSTAND;
	}
	else if (pUpper == UPPERSTATE::SHOOTINGLOWER && pLower == LOWERSTATE::LUNDERJUMP && GetRigidBody()->IsGround())
	{
		nUpper = UPPERSTATE::STAND;
		nLower = LOWERSTATE::LSTAND;
	}
	
	//���� ����ü ���¿� ���� �ִϸ��̼� ����
	if (trigerUpper())
	{
		PlayU(this, pUpper);
	}
	if (trigerLower())
	{
		PlayL(this, pLower);
	}

	//���� ���¸� ���� ���·� �����ش�.


	//���� ��ü ���� ��ü�� �Ѱ���
	bLower = pLower;
	bUpper = pUpper;

	// ���� ����
	bDirection = pDirection; 

	SetPos(vPos);

	CObject::tick();

}

//��ü �ִϸ��̼�
void CPlayer1::PlayL(CObject* _object, LOWERSTATE _Lstate)
{
	
	if (_Lstate == LOWERSTATE::LSTAND) // �ȱ�
	{
		if(pDirection == DIRECTION::RIGHT)
		_object->GetAnimator()->PlayLower(L"LowerBody", true);
		else
		_object->GetAnimator()->PlayLower(L"LowerBodyLeft", true);
	}
	else if (_Lstate == LOWERSTATE::LRUN) //�޸���
	{
		if (pDirection == DIRECTION::RIGHT)
		_object->GetAnimator()->PlayLower(L"Running", true);
		else
		_object->GetAnimator()->PlayLower(L"RunningLeft", true);
	}
	else if (_Lstate == LOWERSTATE::LJUMP) //����
	{
		if (pDirection == DIRECTION::RIGHT)
			_object->GetAnimator()->PlayLower(L"JumpRunning", false);
		else
			_object->GetAnimator()->PlayLower(L"JumpRunningLeft", false);
	}
	else if (_Lstate == LOWERSTATE::LUNDERJUMP) //�Ʒ�������
	{
		if (pDirection == DIRECTION::RIGHT)
			_object->GetAnimator()->PlayLower(L"Jumping", false);
		else
			_object->GetAnimator()->PlayLower(L"JumpingLeft", false);
	}

}

//��ü �ִϸ��̼�
void CPlayer1::PlayU(CObject* _object, UPPERSTATE _Ustate)
{
	if (_Ustate == UPPERSTATE::STAND) // ���ֱ�
	{
		if (pDirection == DIRECTION::RIGHT)
		_object->GetAnimator()->Play(L"UpperBody", true);
		else
		_object->GetAnimator()->Play(L"UpperBodyLeft", true);
	}
	else if (_Ustate == UPPERSTATE::SHOOT) //���
	{

		if (pDirection == DIRECTION::RIGHT)
		_object->GetAnimator()->Play(L"Shooting", true);
		else
		_object->GetAnimator()->Play(L"ShootingLeft", true);
	}
	else if (_Ustate == UPPERSTATE::JUMP) //����
	{
		if (pDirection == DIRECTION::RIGHT)
			_object->GetAnimator()->Play(L"UpperBodyJumping", false);
		else
			_object->GetAnimator()->Play(L"UpperBodyJumpingLeft", false);
	}
	else if (_Ustate == UPPERSTATE::UPPERGUN) //���� ��
	{
		if (pDirection == DIRECTION::RIGHT)
			_object->GetAnimator()->Play(L"Upper", true);
		else
			_object->GetAnimator()->Play(L"UpperLeft", true);
	}
	else if (_Ustate == UPPERSTATE::UPPERSHOOTING) //���� �� ���
	{
		if (pDirection == DIRECTION::RIGHT)
			_object->GetAnimator()->Play(L"ShootingUpper", true);
		else
			_object->GetAnimator()->Play(L"ShootingUpperLeft", true);
	}
	else if (_Ustate == UPPERSTATE::SHOOTINGDOWN) //�Ʒ��� ����
	{
		if (pDirection == DIRECTION::RIGHT)
			_object->GetAnimator()->Play(L"ShootingDown", true);
		else
			_object->GetAnimator()->Play(L"ShootingDownLeft", true);
	}
	else if (_Ustate == UPPERSTATE::SHOOTINGLOWER) //�Ʒ��� ��� �ִ� ����
	{
		if (pDirection == DIRECTION::RIGHT)
			_object->GetAnimator()->Play(L"JumpShootingDown", false);
		else
			_object->GetAnimator()->Play(L"JumpShootingDownLeft", false);
	}
	else if (_Ustate == UPPERSTATE::THROWINGBOMB) //��ź ������
	{
		if (pDirection == DIRECTION::RIGHT)
			_object->GetAnimator()->Play(L"Throw", false);
		else
			_object->GetAnimator()->Play(L"ThrowLeft", false);
	}
}


bool CPlayer1::trigerUpper()
{
	if (bUpper != pUpper || (bDirection != pDirection))
	{
		return true;
	}
	return false;
}


bool CPlayer1::trigerLower()
{
	if (bLower != pLower || (bDirection != pDirection))
	{
		return true;
	}
	return false;
}


void CPlayer1::render(HDC _dc)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());



	CObject::render(_dc);

}

//�̵� ���� �Լ� 
void CPlayer1::Move()
{

}




void CPlayer1::UAnimation()
{

}

void CPlayer1::LAnimation()
{

}





// �浹 ����
void CPlayer1::CollisionBeginOverlap(CCollider* _pOhterCollider)
{
	_pOhterCollider->GetOwner();
}





//�浹�� ���� ����
void CPlayer1::CollisionEndOverlap(CCollider* _pOhterCollider)
{

}




void CPlayer1::Shooting(SHOOTINGDIR _dir)
{
	if (m_fAccTime >= 0.4f)
	{
		// �̻��� ���			
		CBullet* pMissile = Instantiate<CBullet>(GetPos() + Vec2(-50.f, 0.f), LAYER_TYPE::PLAYER_PROJECTILE);

		pMissile->SetDir(Vec2(0.f, -1.f));

		m_fAccTime = 0.f;
	}

	if (_dir == SHOOTINGDIR::KEY0)
	{

	}
}
