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
	srand((unsigned int)time(0)); //난수 0 부터생성
	randNumber = rand() % 10; //나머지 0 에서 9 까지 
	
	//AddComponent(new CRigidBody);
	// 애니메이터 컴포넌트 추가
	/*AddComponent(new CAnimator);
	AddComponent(new CCollider);
	AddComponent(new CRigidBody);*/
	AddComponent(new CAnimator);
	AddComponent(new CCollider);
	AddComponent(new CRigidBody);

	GetCollider()->SetOffset(Vec2(0.f, -50.f));
	GetCollider()->SetScale(Vec2(70.f, 90.f));

	m_pImage = CResMgr::GetInst()->LoadImg(L"enemy", L"image\\Enemy_Asset.bmp");
	//적 관련 Animation 제작
	
	//좌측 본 상태에서 죽을때
	GetAnimator()->CreateAnimation(L"LDie", m_pImage,
		Vec2(0.f, 0.f),Vec2(84.f, 111.f), Vec2(0.f, -60.f),
		84.f, 11, 0.1f);
	//우측 본 상태에서 죽을때 (리버스 Animation) 뒷프레임 부터
	GetAnimator()->CreateReverseAnimation(L"RDie", m_pImage,
		Vec2(0.f, 111.f), Vec2(84.f, 111.f), Vec2(0.f, -70.f),
		84.f, 11, 0.1f, 1);
	//좌측으로 달릴때 
	GetAnimator()->CreateAnimation(L"LRun", m_pImage,
		Vec2(0.f, 222.f), Vec2(102.f, 117.f), Vec2(0.f, -70.f),
		102.f, 12, 0.1f);
	//우측을 달릴때
	GetAnimator()->CreateReverseAnimation(L"RRun", m_pImage,
		Vec2(0.f, 339.f), Vec2(102.f, 117.f), Vec2(0.f, -70.f),
		102.f, 12, 0.1f, 1);
	//좌측으로 걸을때
	GetAnimator()->CreateAnimation(L"LWalk", m_pImage,
		Vec2(0.f, 456.f), Vec2(78.f, 123.f), Vec2(0.f, -70.f),
		78.f, 12, 0.1f);
	//우측으로 걸을때
	GetAnimator()->CreateReverseAnimation(L"RWalk", m_pImage,
		Vec2(0.f, 579.f), Vec2(78.f, 123.f), Vec2(0.f, -70.f),
		78.f, 12, 0.1f, 1);
	// 좌로 폭탄 투척
	GetAnimator()->CreateAnimation(L"LThrow", m_pImage,
		Vec2(0.f, 705.f), Vec2(129.f, 123.f), Vec2(0.f, -70.f),
		129.f, 17, 0.1f);
	// 우로 폭탄 투척
	GetAnimator()->CreateReverseAnimation(L"RThrow", m_pImage,
		Vec2(0.f, 828.f), Vec2(129.f, 123.f), Vec2(0.f, -70.f),
		129.f, 17, 0.1f, 1);
	// 좌측으로 놀란 경우
	GetAnimator()->CreateAnimation(L"LSurprise", m_pImage,
		Vec2(0.f, 954.f), Vec2(129.f, 129.f), Vec2(0.f, -70.f),
		129.f, 11, 0.1f);
	// 우측으로 놀란 경우
	GetAnimator()->CreateReverseAnimation(L"RSurprise", m_pImage,
		Vec2(0.f, 1083.f), Vec2(129.f, 129.f), Vec2(0.f, -70.f),
		129.f, 11, 0.1f, 1);
	//좌측으로 칼질
	GetAnimator()->CreateAnimation(L"LKnife", m_pImage,
		Vec2(0.f, 1212.f), Vec2(153.f, 111.f), Vec2(-35.f, -63.f),
		153.f, 12, 0.2f);
	GetAnimator()->CreateReverseAnimation(L"LReverseKnife", m_pImage,
		Vec2(0.f, 1212.f), Vec2(153.f, 111.f), Vec2(-35.f, -63.f),
		153.f, 12, 0.2f, 1);
	//우측으로 칼질
	GetAnimator()->CreateReverseAnimation(L"RKnife", m_pImage,
		Vec2(0.f, 1323.f), Vec2(153.f, 111.f), Vec2(0.f, -70.f),
		153.f, 12, 0.2f, 1);
	GetAnimator()->CreateAnimation(L"RReverseKnife", m_pImage,
		Vec2(0.f, 1323.f), Vec2(153.f, 111.f), Vec2(0.f, -70.f),
		153.f, 12, 0.2f);
	// 좌측으로 점프
	GetAnimator()->CreateAnimation(L"LJump", m_pImage,
		Vec2(0.f, 1434.f), Vec2(90.f, 132.f), Vec2(0.f, -70.f),
		90.f, 7, 0.1f);
	// 우측으로 점프
	GetAnimator()->CreateReverseAnimation(L"RJump", m_pImage,
		Vec2(0.f, 1566.f), Vec2(90.f, 132.f), Vec2(0.f, -70.f),
		90.f, 7, 0.1f, 1);
	// Left Idle
	GetAnimator()->CreateAnimation(L"LIdle", m_pImage,
		Vec2(0.f, 1698.f), Vec2(81.f, 132.f), Vec2(0.f, -70.f),
		81.f, 4, 0.7f);
	// Right Idle (속도0.5)
	GetAnimator()->CreateReverseAnimation(L"RIdle", m_pImage,
		Vec2(0.f, 1830.f), Vec2(81.f, 132.f), Vec2(0.f, -70.f),
		81.f, 4, 0.5f, 1);

	// 강체 정보 설정
	GetRigidBody()->SetMaxSpeed(200.f);
	GetRigidBody()->SetMaxGravitySpeed(1000.f);
	GetRigidBody()->SetGround(false);
	GetRigidBody()->SetGravityAccel(Vec2(0.f, 800.f));
	GetRigidBody()->SetElasticity(false);// 탄성 불가능
	GetRigidBody()->SetGravity(false);

	//초기 애니메이션 설정
	GetAnimator()->Play(L"RIdle", true);
	
	
	enemyState = ENEMY_STATE::IDLE; //현재 적상태 아무 상황이 아님을 표시
	_eDirection = DIRECTION::LEFT;		//좌측을 보고 있음
	m_Block = DIRECTION::RIGHT;
	HP = 1.f;						//체력을 1로 설정
	walkSpeed = 150.f;				//현재 걷는 속도 150으로 설정
	runSpeed = 250.f;				// 달리는 속도 
	isDie = false;
	SetPos(Vec2(500.f, 0.f));
	rootPos = this->GetPos();	//초기 대입 값을 위치로 설정
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
	Ground_SET; //땅 판별 하도록 설정

	CScene* CurScene = CSceneMgr::GetInst()->GetCurScene();
	const vector<CObject*>& vecPlayer = CurScene->GetObjects(LAYER_TYPE::PLAYER);
	Vec2 pPos; //플레이어 위치
	Vec2 ePos; //적 위치
	
	for (int k = 0; k < vecPlayer.size(); ++k)
	{
		pPos = vecPlayer[k]->GetPos(); //현재 플레이어의 위치
	}

	//ePos = this->GetPos(); //적의 위치를 가져온다.


	if (!isDie)
	{
		MoveFirePos(); //수류탄 투척 방향 및 각도 설정
		// 이전 상태가 걷기 거나 Idle 이면 범위만 계속 체크한다.
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
		beforeEnemyState = enemyState; // 이전상태에 현재 상태 저장
	}


	

	//최종위치로 설정
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

// 상태가 변경 되면 특정 상태 animation 구현
bool CEnemy::triger()
{
	//이전 상태와 현재 상태가 다르면 재생
	if (beforeEnemyState != enemyState)
	{
		return true;
	}
	return false;
}

//현재 적 HP체크 한다.
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
		if (!(GetRigidBody()->IsGround())) //땅이 아닐경우 점프
		{
				enemyState = ENEMY_STATE::JUMP;  //그라운드가 아니면 점프 모션 재생
		}
		else //땅 인경우
		{
			if (beforeEnemyState == ENEMY_STATE::JUMP) //이전에 점프한 상태에서
			{
				{
					enemyState = ENEMY_STATE::IDLE; //일반 상태로 변경
				}
			}
		}
	}
	
}





void CEnemy::Die()
{
	// 죽은 경우 죽는 사운드
	// 현재 HP 0으로 변경후 
	// 현재 enemy 행동 을 죽은 상태로 설정
	// 죽은 Animation 재생하도록 설정
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
		if (DeltaTime > AtkRate) //IDLE 상태 인경우 2초 후에 공격 하도록 설정한다.
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
		//애니메이션 재생이 끝난 경우
		if (GetAnimator()->getCurrentAnim()->IsFinish())
		{
				if (_eDirection == DIRECTION::LEFT)
				{
					// 여기에 칼질 데미지 삽입 
					enemyState = ENEMY_STATE::COUNTERKNIFE;
				}
				else if (_eDirection == DIRECTION::RIGHT)
				{
					//여기에 칼질 데이지 삽입
					enemyState = ENEMY_STATE::COUNTERKNIFE;
				}
		}
	}
	// 던지기 구현
	else if (beforeEnemyState == ENEMY_STATE::THROW)
	{
		if (GetAnimator()->getCurrentAnim()->IsFinish())
		{
			//던지는 애니매이션 구현 필요
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
			//칼 접는 모션 이후에일반 상태로 전환
			enemyState = ENEMY_STATE::IDLE;
		}
	
	}

}

void CEnemy::MoveFirePos()
{
	if (_eDirection == DIRECTION::LEFT) //행동 방향 좌측
	{
		//좌측으로 수류탄 투척 각도 및 방향 각 설정
	}
	else if (_eDirection == DIRECTION::RIGHT) //행동 방향 우측
	{
		//우측으로 수류탄 투척
	}

}

//이동 관련 함수
void CEnemy::Move()
{
	Vec2 pos = this->GetPos();
	//걷기
	if (enemyState == ENEMY_STATE::WALK)
	{
		//오른쪽 방향 볼때
		if (_eDirection == DIRECTION::RIGHT)
		{
			//오른쪽에 벽이 아닐때
			if (m_Block != DIRECTION::RIGHT)
			{
				//좌측을 막은게 아니면 좌측으로 이동

				pos.x += walkSpeed * DT;
			}
			else //오른쪽 벽일때
			{
				_eDirection = DIRECTION::LEFT;
			}
			if ((rootPos.x + (randNumber * 50.f)) < pos.x) //우측 벽을 만나면
			{
				GetAnimator()->Play(L"LWalk", true);
				m_Block = DIRECTION::RIGHT;
			}

		}
		else if (_eDirection == DIRECTION::LEFT)
		{
			if (m_Block != DIRECTION::LEFT)
			{
				//우측을 막은게 아니면 우측으로 이동
				pos.x -= walkSpeed * DT;
			}
			else
			{
				_eDirection = DIRECTION::RIGHT;
			}
			if ((rootPos.x - (randNumber * 50.f)) > pos.x) //우측 벽을 만나면
			{
				GetAnimator()->Play(L"RWalk", true);
				m_Block = DIRECTION::LEFT;
			}
		}
	}
	//달리기
	else if (enemyState == ENEMY_STATE::RUN)
	{
		if (_eDirection == DIRECTION::LEFT)
		{
			if (m_Block != DIRECTION::LEFT)
			{
				//좌측으로 달려감
				m_Block = DIRECTION::RIGHT;
			}
			pos.x -= walkSpeed * DT;
		}
		else if (_eDirection == DIRECTION::RIGHT)
		{
			if (m_Block != DIRECTION::RIGHT)
			{
				//우측으로 달려감
				m_Block = DIRECTION::LEFT;
			}
			pos.x += walkSpeed * DT;
		}
	}

	//현재 위치로 다시 설정해준다.
	SetPos(pos);
}

void CEnemy::ScoutRangeCheck()
{
	CScene* CurScene = CSceneMgr::GetInst()->GetCurScene();
	const vector<CObject*>& vecPlayer = CurScene->GetObjects(LAYER_TYPE::PLAYER);
	Vec2 pPos; //플레이어 위치
	Vec2 ePos; //적 위치

	ePos = this->GetPos(); //적위치 받아 오고
	
	for (int i = 0; i < vecPlayer.size(); ++i)
	{
		pPos = vecPlayer[i]->GetPos(); //현재 플레이어의 위치

		if (vecPlayer[i] == nullptr)
		{
			isSpot = false;
		}

		if (vecPlayer.size() <= 0)
		{
			enemyState = ENEMY_STATE::IDLE;
		}

		else //플레이어가 최소한 1명 있다면
		{
			//플레이어와 적의 위치 차이 값이 600 이하라면
			if (ePos.x - pPos.x < 300)
			{
				//방향이 좌측이라면
				if (_eDirection == DIRECTION::LEFT)
				{
					// 플레이어보다 왼쪽에 있을 경우 
					if (ePos.x - pPos.x <= 0)
					{
						//방향을 왼쪽으로 바꿔주고
						_eDirection = DIRECTION::LEFT;
						//현재 상태를 걷기로 바꾼다.
						enemyState = ENEMY_STATE::WALK;
					}
					//플레이어 보다 오른쪽에 있을 경우
					else
					{
						//방향을 왼쪽으로 바꿔주고
						_eDirection = DIRECTION::LEFT;
						//타겟팅할 게 없으면
						if (vecPlayer[i] == nullptr)
						{
							enemyState = ENEMY_STATE::SURPRISE;
						}
						//타겟팅 할게 있으면
						else
						{
							//위치해 있지 않다면
							if (!isSpot)
							{
								//소리 여기에 두고
								enemyState = ENEMY_STATE::SURPRISE;
							}
							//위치해 있다면
							/*else if (isSpot == true)
							{
								enemyState = ENEMY_STATE::IDLE;
							}*/
						}

						//공격 상황
						//거기가 150 이하이면
						if (fabs(pPos.x - ePos.x) < 150.f)
						{
							//150 근거리 무기 사용
							nextEnemyState = ENEMY_STATE::KNIFE;
						}
						//150 보다 멀 경우 투척 무기 사용
						else
						{
							nextEnemyState = ENEMY_STATE::THROW;
						}



					}
				}
				
				//방향이 우측인상태 라면
				else if (_eDirection == DIRECTION::RIGHT)
				{
					// 플레이어보다 왼쪽
					if (ePos.x - pPos.x <= 0)
					{
						//방향을 오른쪽으로 전환
						_eDirection = DIRECTION::RIGHT;
						//플레이어가 비었다면
						if (vecPlayer[i] == nullptr)
						{
							// 놀란 상태 유지
							enemyState = ENEMY_STATE::SURPRISE;
						}
						//플레이어가 있다면
						else
						{
							//위치해 있지 않다면
							if (!isSpot)
							{
								//놀란 상태
								enemyState = ENEMY_STATE::SURPRISE;
							}
							//위치해 있다면
							else if (isSpot == true)
							{
								enemyState = ENEMY_STATE::IDLE;
							}
						}

						// 공격 상황 
						//150 범위 내로 들어 오면 다음 상황을 미리 예약해서
						if (fabs(pPos.x - ePos.x) < 150)
						{
							nextEnemyState = ENEMY_STATE::KNIFE;
						}
						//150  보다 원거리 일경우
						else
						{
							nextEnemyState = ENEMY_STATE::THROW;
						}
					}
					//플레이어 보다 오른쪽일 경우 
					else
					{
						//방향을 왼쪽으로 변경
						_eDirection = DIRECTION::LEFT;
						//소리 삽입
						//놀란 상태로 설정
						enemyState = ENEMY_STATE::SURPRISE;
						//놀란 이후에 도망 치도록 설정
						nextEnemyState = ENEMY_STATE::RUN;
					}
				}



			}
			//플레이어와 적의 거리가 600 이상인 경우 거리를 걷는 상태로 둔다. 
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
