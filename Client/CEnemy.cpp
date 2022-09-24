#include "pch.h"
#include "CEnemy.h"

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

#include <time.h>

CEnemy::CEnemy()
	: m_pImage(nullptr)
    , m_fAccTime(0.f)
    , HP(0)
	, _eType()
	, _eMotion()
	, _eDirection()
	, IsDead(false)
{
	srand((unsigned int)time(0)); //���� 0 ���ͻ���
	randNumber = rand() % 10; //������ 0 ���� 9 ���� 
	
	//AddComponent(new CRigidBody);
	// �ִϸ����� ������Ʈ �߰�
	/*AddComponent(new CAnimator);
	AddComponent(new CCollider);
	AddComponent(new CRigidBody);*/
	AddComponent(new CAnimator);
	AddComponent(new CCollider);
	AddComponent(new CRigidBody);

	GetCollider()->SetOffset(Vec2(0.f, -50.f));
	GetCollider()->SetScale(Vec2(70.f, 90.f));

	m_pImage = CResMgr::GetInst()->LoadImg(L"enemy", L"image\\Enemy_Asset.bmp");
	//�� ���� Animation ����
	
	//���� �� ���¿��� ������
	GetAnimator()->CreateAnimation(L"LDie", m_pImage,
		Vec2(0.f, 0.f),Vec2(84.f, 111.f), Vec2(0.f, -60.f),
		84.f, 11, 0.1f);
	//���� �� ���¿��� ������ (������ Animation) �������� ����
	GetAnimator()->CreateReverseAnimation(L"RDie", m_pImage,
		Vec2(0.f, 111.f), Vec2(84.f, 111.f), Vec2(0.f, -70.f),
		84.f, 11, 0.1f, 1);
	//�������� �޸��� 
	GetAnimator()->CreateAnimation(L"LRun", m_pImage,
		Vec2(0.f, 222.f), Vec2(102.f, 117.f), Vec2(0.f, -70.f),
		102.f, 12, 0.1f);
	//������ �޸���
	GetAnimator()->CreateReverseAnimation(L"RRun", m_pImage,
		Vec2(0.f, 339.f), Vec2(102.f, 117.f), Vec2(0.f, -70.f),
		102.f, 12, 0.1f, 1);
	//�������� ������
	GetAnimator()->CreateAnimation(L"LWalk", m_pImage,
		Vec2(0.f, 456.f), Vec2(78.f, 123.f), Vec2(0.f, -70.f),
		78.f, 12, 0.1f);
	//�������� ������
	GetAnimator()->CreateReverseAnimation(L"RWalk", m_pImage,
		Vec2(0.f, 579.f), Vec2(78.f, 123.f), Vec2(0.f, -70.f),
		78.f, 12, 0.1f, 1);
	// �·� ��ź ��ô
	GetAnimator()->CreateAnimation(L"LThrow", m_pImage,
		Vec2(0.f, 705.f), Vec2(129.f, 123.f), Vec2(0.f, -70.f),
		129.f, 17, 0.1f);
	// ��� ��ź ��ô
	GetAnimator()->CreateReverseAnimation(L"RThrow", m_pImage,
		Vec2(0.f, 828.f), Vec2(129.f, 123.f), Vec2(0.f, -70.f),
		129.f, 17, 0.1f, 1);
	// �������� ��� ���
	GetAnimator()->CreateAnimation(L"LSurprise", m_pImage,
		Vec2(0.f, 954.f), Vec2(129.f, 129.f), Vec2(0.f, -70.f),
		129.f, 11, 0.1f);
	// �������� ��� ���
	GetAnimator()->CreateReverseAnimation(L"RSurprise", m_pImage,
		Vec2(0.f, 1083.f), Vec2(129.f, 129.f), Vec2(0.f, -70.f),
		129.f, 11, 0.1f, 1);
	//�������� Į��
	GetAnimator()->CreateAnimation(L"LKnife", m_pImage,
		Vec2(0.f, 1212.f), Vec2(153.f, 111.f), Vec2(-35.f, -63.f),
		153.f, 12, 0.2f);
	GetAnimator()->CreateReverseAnimation(L"LReverseKnife", m_pImage,
		Vec2(0.f, 1212.f), Vec2(153.f, 111.f), Vec2(-35.f, -63.f),
		153.f, 12, 0.2f, 1);
	//�������� Į��
	GetAnimator()->CreateReverseAnimation(L"RKnife", m_pImage,
		Vec2(0.f, 1323.f), Vec2(153.f, 111.f), Vec2(0.f, -70.f),
		153.f, 12, 0.2f, 1);
	GetAnimator()->CreateAnimation(L"RReverseKnife", m_pImage,
		Vec2(0.f, 1323.f), Vec2(153.f, 111.f), Vec2(0.f, -70.f),
		153.f, 12, 0.2f);
	// �������� ����
	GetAnimator()->CreateAnimation(L"LJump", m_pImage,
		Vec2(0.f, 1434.f), Vec2(90.f, 132.f), Vec2(0.f, -70.f),
		90.f, 7, 0.1f);
	// �������� ����
	GetAnimator()->CreateReverseAnimation(L"RJump", m_pImage,
		Vec2(0.f, 1566.f), Vec2(90.f, 132.f), Vec2(0.f, -70.f),
		90.f, 7, 0.1f, 1);
	// Left Idle
	GetAnimator()->CreateAnimation(L"LIdle", m_pImage,
		Vec2(0.f, 1698.f), Vec2(81.f, 132.f), Vec2(0.f, -70.f),
		81.f, 4, 0.7f);
	// Right Idle (�ӵ�0.5)
	GetAnimator()->CreateReverseAnimation(L"RIdle", m_pImage,
		Vec2(0.f, 1830.f), Vec2(81.f, 132.f), Vec2(0.f, -70.f),
		81.f, 4, 0.5f, 1);

	// ��ü ���� ����
	GetRigidBody()->SetMaxSpeed(200.f);
	GetRigidBody()->SetMaxGravitySpeed(1000.f);
	GetRigidBody()->SetGround(false);
	GetRigidBody()->SetGravityAccel(Vec2(0.f, 800.f));
	GetRigidBody()->SetElasticity(false);// ź�� �Ұ���
	GetRigidBody()->SetGravity(false);

	//�ʱ� �ִϸ��̼� ����
	GetAnimator()->Play(L"RIdle", true);
	
	
	enemyState = ENEMY_STATE::IDLE; //���� ������ �ƹ� ��Ȳ�� �ƴ��� ǥ��
	_eDirection = DIRECTION::LEFT;		//������ ���� ����
	m_Block = DIRECTION::RIGHT;
	HP = 1.f;						//ü���� 1�� ����
	walkSpeed = 150.f;				//���� �ȴ� �ӵ� 150���� ����
	runSpeed = 250.f;				// �޸��� �ӵ� 
	isDie = false;
	SetPos(Vec2(500.f, 0.f));
	rootPos = this->GetPos();	//�ʱ� ���� ���� ��ġ�� ����
}

CEnemy::CEnemy(const CEnemy& _mon)
	: CObject(_mon)
	, m_pImage(_mon.m_pImage)
	, m_fAccTime(_mon.m_fAccTime)
	, HP(_mon.HP)
	, _eType(_mon._eType)
	, _eMotion(_mon._eMotion)
	, _eDirection(_mon._eDirection)
{

}

CEnemy::~CEnemy()
{
}

void CEnemy::tick()
{


	m_fAccTime += DT;
	Ground_SET; //�� �Ǻ� �ϵ��� ����

	CScene* CurScene = CSceneMgr::GetInst()->GetCurScene();
	const vector<CObject*>& vecPlayer = CurScene->GetObjects(LAYER_TYPE::PLAYER);
	Vec2 pPos; //�÷��̾� ��ġ
	Vec2 ePos; //�� ��ġ
	
	for (int k = 0; k < vecPlayer.size(); ++k)
	{
		pPos = vecPlayer[k]->GetPos(); //���� �÷��̾��� ��ġ
	}

	//ePos = this->GetPos(); //���� ��ġ�� �����´�.


	if (!isDie)
	{
		MoveFirePos(); //����ź ��ô ���� �� ���� ����
		// ���� ���°� �ȱ� �ų� Idle �̸� ������ ��� üũ�Ѵ�.
		if (beforeEnemyState == ENEMY_STATE::IDLE || beforeEnemyState == ENEMY_STATE::WALK)
		{
			ScoutRangeCheck();
		}
		Move();
		Atk();
		GroundCheck();
		//HPCheck();

		if (triger())
		{
			PlayAnim(this, enemyState);
		}
		beforeEnemyState = enemyState; // �������¿� ���� ���� ����
	}


	

	//������ġ�� ����
	//this->SetPos(ePos);

	CObject::tick();

}

void CEnemy::CollisionBeginOverlap(CCollider* _pOhterCollider)
{
	if (dynamic_cast<CPlayer1*>(_pOhterCollider->GetOwner()))
	{
		enemyCollide = true;
	}
	if (dynamic_cast<CBomb*>(_pOhterCollider->GetOwner()))
	{
		enemyState = ENEMY_STATE::DIE;
	}
	if (dynamic_cast<CBullet*>(_pOhterCollider->GetOwner()))
	{
		enemyState = ENEMY_STATE::DIE;
	}
	
}

// ���°� ���� �Ǹ� Ư�� ���� animation ����
bool CEnemy::triger()
{
	//���� ���¿� ���� ���°� �ٸ��� ���
	if (beforeEnemyState != enemyState)
	{
		return true;
	}
	return false;
}

//���� �� HPüũ �Ѵ�.
void CEnemy::HPCheck()
{
	if (HP <= 0)
	{

		Die();
	}
}
void CEnemy::GroundCheck()
{
	if (m_fAccTime > 3.0f)
	{
		if (!(GetRigidBody()->IsGround())) //���� �ƴҰ�� ����
		{
				enemyState = ENEMY_STATE::JUMP;  //�׶��尡 �ƴϸ� ���� ��� ���
		}
		else //�� �ΰ��
		{
			if (beforeEnemyState == ENEMY_STATE::JUMP) //������ ������ ���¿���
			{
				{
					enemyState = ENEMY_STATE::IDLE; //�Ϲ� ���·� ����
				}
			}
		}
	}
	
}





void CEnemy::Die()
{
	// ���� ��� �״� ����
	// ���� HP 0���� ������ 
	// ���� enemy �ൿ �� ���� ���·� ����
	// ���� Animation ����ϵ��� ����
	enemyState = ENEMY_STATE::DIE;
}



void CEnemy::Atk()
{
	if (beforeEnemyState == ENEMY_STATE::SURPRISE)
	{
		if (GetAnimator()->getCurrentAnim()->IsFinish())
		{
			switch (nextEnemyState)
			{
			case ENEMY_STATE::RUN:
				enemyState = ENEMY_STATE::RUN;
				break;
			case ENEMY_STATE::THROW:
				enemyState = ENEMY_STATE::THROW;
				break;
			case ENEMY_STATE::KNIFE:
				enemyState = ENEMY_STATE::KNIFE;
				break;
			default:
				break;
			}
			isSpot = true;
		}
	}
	else if (beforeEnemyState == ENEMY_STATE::IDLE)
	{
		float AtkRate = 2;
		float DeltaTime = 0;
		DeltaTime += DT;
		if (DeltaTime > AtkRate) //IDLE ���� �ΰ�� 2�� �Ŀ� ���� �ϵ��� �����Ѵ�.
		{
			DeltaTime = 0;
			if (GetAnimator()->getCurrentAnim()->IsFinish()) 
			{
				switch (nextEnemyState)
				{
				case ENEMY_STATE::RUN:
					enemyState = ENEMY_STATE::RUN;
					break;
				case ENEMY_STATE::THROW:
					enemyState = ENEMY_STATE::THROW;
					break;
				case ENEMY_STATE::KNIFE:
					enemyState = ENEMY_STATE::KNIFE;
					break;
				default:
					break;
				}
			}
		}
		else
		{

		}
	}
	if (beforeEnemyState == ENEMY_STATE::KNIFE)
	{
		//�ִϸ��̼� ����� ���� ���
		if (GetAnimator()->getCurrentAnim()->IsFinish())
		{
				if (_eDirection == DIRECTION::LEFT)
				{
					// ���⿡ Į�� ������ ���� 
					enemyState = ENEMY_STATE::COUNTERKNIFE;
				}
				else if (_eDirection == DIRECTION::RIGHT)
				{
					//���⿡ Į�� ������ ����
					enemyState = ENEMY_STATE::COUNTERKNIFE;
				}
		}
	}
	// ������ ����
	else if (beforeEnemyState == ENEMY_STATE::THROW)
	{
		if (GetAnimator()->getCurrentAnim()->IsFinish())
		{
			//������ �ִϸ��̼� ���� �ʿ�
			enemyState = ENEMY_STATE::IDLE;
			if (enemyCollide)
			{
				enemyState = ENEMY_STATE::KNIFE;
			}
		}
	
	}
	else if (beforeEnemyState == ENEMY_STATE::COUNTERKNIFE)
	{
		if (GetAnimator()->getCurrentAnim()->IsFinish())
		{
			//Į ���� ��� ���Ŀ��Ϲ� ���·� ��ȯ
			enemyState = ENEMY_STATE::IDLE;
		}
	
	}

}

void CEnemy::MoveFirePos()
{
	if (_eDirection == DIRECTION::LEFT) //�ൿ ���� ����
	{
		//�������� ����ź ��ô ���� �� ���� �� ����
	}
	else if (_eDirection == DIRECTION::RIGHT) //�ൿ ���� ����
	{
		//�������� ����ź ��ô
	}

}

//�̵� ���� �Լ�
void CEnemy::Move()
{
	Vec2 pos = this->GetPos();
	//�ȱ�
	if (enemyState == ENEMY_STATE::WALK)
	{
		//������ ���� ����
		if (_eDirection == DIRECTION::RIGHT)
		{
			//�����ʿ� ���� �ƴҶ�
			if (m_Block != DIRECTION::RIGHT)
			{
				//������ ������ �ƴϸ� �������� �̵�

				pos.x += walkSpeed * DT;
			}
			else //������ ���϶�
			{
				_eDirection = DIRECTION::LEFT;
			}
			if ((rootPos.x + (randNumber * 50.f)) < pos.x) //���� ���� ������
			{
				GetAnimator()->Play(L"LWalk", true);
				m_Block = DIRECTION::RIGHT;
			}

		}
		else if (_eDirection == DIRECTION::LEFT)
		{
			if (m_Block != DIRECTION::LEFT)
			{
				//������ ������ �ƴϸ� �������� �̵�
				pos.x -= walkSpeed * DT;
			}
			else
			{
				_eDirection = DIRECTION::RIGHT;
			}
			if ((rootPos.x - (randNumber * 50.f)) > pos.x) //���� ���� ������
			{
				GetAnimator()->Play(L"RWalk", true);
				m_Block = DIRECTION::LEFT;
			}
		}
	}
	//�޸���
	else if (enemyState == ENEMY_STATE::RUN)
	{
		if (_eDirection == DIRECTION::LEFT)
		{
			if (m_Block != DIRECTION::LEFT)
			{
				//�������� �޷���
				m_Block = DIRECTION::RIGHT;
			}
			pos.x -= walkSpeed * DT;
		}
		else if (_eDirection == DIRECTION::RIGHT)
		{
			if (m_Block != DIRECTION::RIGHT)
			{
				//�������� �޷���
				m_Block = DIRECTION::LEFT;
			}
			pos.x += walkSpeed * DT;
		}
	}

	//���� ��ġ�� �ٽ� �������ش�.
	SetPos(pos);
}

void CEnemy::ScoutRangeCheck()
{
	CScene* CurScene = CSceneMgr::GetInst()->GetCurScene();
	const vector<CObject*>& vecPlayer = CurScene->GetObjects(LAYER_TYPE::PLAYER);
	Vec2 pPos; //�÷��̾� ��ġ
	Vec2 ePos; //�� ��ġ

	ePos = this->GetPos(); //����ġ �޾� ����
	
	for (int i = 0; i < vecPlayer.size(); ++i)
	{
		pPos = vecPlayer[i]->GetPos(); //���� �÷��̾��� ��ġ

		if (vecPlayer[i] == nullptr)
		{
			isSpot = false;
		}

		if (vecPlayer.size() <= 0)
		{
			enemyState = ENEMY_STATE::IDLE;
		}

		else //�÷��̾ �ּ��� 1�� �ִٸ�
		{
			//�÷��̾�� ���� ��ġ ���� ���� 600 ���϶��
			if (ePos.x - pPos.x < 300)
			{
				//������ �����̶��
				if (_eDirection == DIRECTION::LEFT)
				{
					// �÷��̾�� ���ʿ� ���� ��� 
					if (ePos.x - pPos.x <= 0)
					{
						//������ �������� �ٲ��ְ�
						_eDirection = DIRECTION::LEFT;
						//���� ���¸� �ȱ�� �ٲ۴�.
						enemyState = ENEMY_STATE::WALK;
					}
					//�÷��̾� ���� �����ʿ� ���� ���
					else
					{
						//������ �������� �ٲ��ְ�
						_eDirection = DIRECTION::LEFT;
						//Ÿ������ �� ������
						if (vecPlayer[i] == nullptr)
						{
							enemyState = ENEMY_STATE::SURPRISE;
						}
						//Ÿ���� �Ұ� ������
						else
						{
							//��ġ�� ���� �ʴٸ�
							if (!isSpot)
							{
								//�Ҹ� ���⿡ �ΰ�
								enemyState = ENEMY_STATE::SURPRISE;
							}
							//��ġ�� �ִٸ�
							/*else if (isSpot == true)
							{
								enemyState = ENEMY_STATE::IDLE;
							}*/
						}

						//���� ��Ȳ
						//�űⰡ 150 �����̸�
						if (fabs(pPos.x - ePos.x) < 150.f)
						{
							//150 �ٰŸ� ���� ���
							nextEnemyState = ENEMY_STATE::KNIFE;
						}
						//150 ���� �� ��� ��ô ���� ���
						else
						{
							nextEnemyState = ENEMY_STATE::THROW;
						}



					}
				}
				
				//������ �����λ��� ���
				else if (_eDirection == DIRECTION::RIGHT)
				{
					// �÷��̾�� ����
					if (ePos.x - pPos.x <= 0)
					{
						//������ ���������� ��ȯ
						_eDirection = DIRECTION::RIGHT;
						//�÷��̾ ����ٸ�
						if (vecPlayer[i] == nullptr)
						{
							// ��� ���� ����
							enemyState = ENEMY_STATE::SURPRISE;
						}
						//�÷��̾ �ִٸ�
						else
						{
							//��ġ�� ���� �ʴٸ�
							if (!isSpot)
							{
								//��� ����
								enemyState = ENEMY_STATE::SURPRISE;
							}
							//��ġ�� �ִٸ�
							else if (isSpot == true)
							{
								enemyState = ENEMY_STATE::IDLE;
							}
						}

						// ���� ��Ȳ 
						//150 ���� ���� ��� ���� ���� ��Ȳ�� �̸� �����ؼ�
						if (fabs(pPos.x - ePos.x) < 150)
						{
							nextEnemyState = ENEMY_STATE::KNIFE;
						}
						//150  ���� ���Ÿ� �ϰ��
						else
						{
							nextEnemyState = ENEMY_STATE::THROW;
						}
					}
					//�÷��̾� ���� �������� ��� 
					else
					{
						//������ �������� ����
						_eDirection = DIRECTION::LEFT;
						//�Ҹ� ����
						//��� ���·� ����
						enemyState = ENEMY_STATE::SURPRISE;
						//��� ���Ŀ� ���� ġ���� ����
						nextEnemyState = ENEMY_STATE::RUN;
					}
				}



			}
			//�÷��̾�� ���� �Ÿ��� 600 �̻��� ��� �Ÿ��� �ȴ� ���·� �д�. 
			else
			{ 
			enemyState = ENEMY_STATE::WALK;
			}
		}
	}
	
	

}






void CEnemy::PlayAnim(CEnemy* _object, ENEMY_STATE _estate)
{
	if (_estate == ENEMY_STATE::IDLE)
	{
		if (DIRECTION::LEFT == _eDirection)
		{
			_object->GetAnimator()->Play(L"LIdle", true);
		}
		else if (DIRECTION::RIGHT == _eDirection)
		{
			_object->GetAnimator()->Play(L"RIdle", true);
		}
	}
	else if (_estate == ENEMY_STATE::THROW)
	{
		if (DIRECTION::LEFT == _eDirection)
		{
			_object->GetAnimator()->Play(L"LThrow", false);
		}
		else if (DIRECTION::RIGHT == _eDirection)
		{
			_object->GetAnimator()->Play(L"RThrow", false);
		}
	}
	else if (_estate == ENEMY_STATE::KNIFE)
	{
		if (DIRECTION::LEFT == _eDirection)
		{
			_object->GetAnimator()->Play(L"LKnife", false);
		}
		else if (DIRECTION::RIGHT == _eDirection)
		{
			_object->GetAnimator()->Play(L"RKnife", false);
		}
	}
	else if (_estate == ENEMY_STATE::WALK)
	{
		if (DIRECTION::LEFT == _eDirection)
		{
			_object->GetAnimator()->Play(L"LWalk", true);
		}
		else if (DIRECTION::RIGHT == _eDirection)
		{
			_object->GetAnimator()->Play(L"RWalk", true);
		}
	}
	else if (_estate == ENEMY_STATE::RUN)
	{
		if (DIRECTION::LEFT == _eDirection)
		{
			_object->GetAnimator()->Play(L"LRun", true);
		}
		else if (DIRECTION::RIGHT == _eDirection)
		{
			_object->GetAnimator()->Play(L"RRun", true);
		}
	}
	else if (_estate == ENEMY_STATE::JUMP)
	{
		if (DIRECTION::LEFT == _eDirection)
		{
			_object->GetAnimator()->Play(L"LJump", false);
		}
		else if (DIRECTION::RIGHT == _eDirection)
		{
			_object->GetAnimator()->Play(L"RJump", false);
		}
	}
	else if (_estate == ENEMY_STATE::SURPRISE)
	{
		if (DIRECTION::LEFT == _eDirection)
		{
			_object->GetAnimator()->Play(L"LSurprise", false);
		}
		else if (DIRECTION::RIGHT == _eDirection)
		{
			_object->GetAnimator()->Play(L"RSurprise", false);
		}
	}
	else if (_estate == ENEMY_STATE::DIE)
	{
		if (DIRECTION::LEFT == _eDirection)
		{
			_object->GetAnimator()->Play(L"LDie", false);
		}
		else if (DIRECTION::RIGHT == _eDirection)
		{
			_object->GetAnimator()->Play(L"RDie", false);
		}
	}
	else if (_estate == ENEMY_STATE::COUNTERKNIFE)
	{
		if (DIRECTION::LEFT == _eDirection)
		{
			_object->GetAnimator()->Play(L"LReverseKnife", false);
		}
		else if (DIRECTION::RIGHT == _eDirection)
		{
			_object->GetAnimator()->Play(L"RReverseKnife", false);
		}
	}
	else if (_estate == ENEMY_STATE::NONE)
	{
		return;
	}

}
