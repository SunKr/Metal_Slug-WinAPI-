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
	, eArmorType(ARMOR_TYPE::NORMAL) //일반 ARM 으로 설정 (일반총)
	, m_BulletCount(200) //Machine Gun 총알수 는 0개로 제한한다.
	, m_Bomb(10)  //초기 폭탄수는 10개로 제한한다.
	, m_knife(false)
{
	// 애니메이터 컴포넌트 추가
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


	//이미지 가져올때 알파 채널 들어있는지 확인 할것
	//m_pImage = CResMgr::GetInst()->LoadImg(L"PlayerAtlas", L"image\\player1.bmp");
	m_pImage = CResMgr::GetInst()->LoadImg(L"PlayerAtlas", L"image\\player1_3.bmp");

	// 소환 될때 
	GetAnimator()->CreateAnimation(L"Summon", m_pImage, Vec2(0.f, 0.f),
		Vec2(93.f, 720.f), Vec2(-50.f, -200.f), 93.f, 6, 0.1f);
	//놀라서  아래로 숚이는 모션
	GetAnimator()->CreateAnimation(L"Crounch", m_pImage, Vec2(0.f, 1101.f),
		Vec2(87.f, 123.f), Vec2(6.f, -60.f), 87.f, 4, 0.1f); 
	// 아래로 숚이는거 유지 모션
	GetAnimator()->CreateLowerAnimation(L"Crounch1", m_pImage, Vec2(0.f, 1224.f),
		Vec2(93.f, 81.f), Vec2(0.f, -30.f), 93.f, 4, 0.1f, 1);
	// 아래로 숚이고 걷기
	GetAnimator()->CreateAnimation(L"CrounchWalking", m_pImage, Vec2(0.f, 1305.f),
		Vec2(105.f, 72.f), Vec2(18.f, -35.f), 105.f, 7, 0.1f);
	// Crounch and shooting
	GetAnimator()->CreateAnimation(L"CrounchShooting", m_pImage, Vec2(0.f, 1740.f),
		Vec2(156.f, 81.f), Vec2(38.f, -35.f), 156.f, 10, 0.1f);
	// Crounch and Knife
	GetAnimator()->CreateAnimation(L"CrounchKnife", m_pImage, Vec2(0.f, 2127.f),
		Vec2(126.f, 105.f), Vec2(5.f, -25.f), 126.f, 4, 0.1f);


	//===============하체====================

	//하체 Standing  완료
	GetAnimator()->CreateLowerAnimation(L"LowerBody", m_pImage, Vec2(0.f, 4350.f),
		Vec2(63.f, 48.f), Vec2(0.f, -20.f), 63.f, 4, 0.5f, true);
	// 하체 Running 완료
	GetAnimator()->CreateLowerAnimation(L"Running", m_pImage, Vec2(0.f, 4398.f),
		Vec2(93.f, 60.f), Vec2(14.f, -28.f), 93.f, 12, 0.1f, true);
	// 하체 Jumping (아래 총 하체)
	GetAnimator()->CreateLowerAnimation(L"Jumping", m_pImage, Vec2(6.f, 4458.f),
		Vec2(69.f, 72.f), Vec2(3.f, 0.f), 69.f, 6, 0.1f, true);
	// 하체 Jumping_Running
	GetAnimator()->CreateLowerAnimation(L"JumpRunning", m_pImage, Vec2(0.f, 4530.f),
		Vec2(99.f, 63.f), Vec2(18.f, -18.f), 99.f, 6, 0.1f, true);
	
	
	//상체 12개
	GetAnimator()->CreateAnimation(L"UpperBody", m_pImage, Vec2(0.f, 807.f),
		Vec2(96.f, 84.f), Vec2(15.f, -67.f), 96.f, 12, 0.5f);
	// 상체 뛰는 모습
	GetAnimator()->CreateAnimation(L"UpperBodyJumping", m_pImage, Vec2(0.f, 891.f),
		Vec2(96.f, 105.f), Vec2(0.f, -60.f), 96.f, 3, 0.1f);
	// 상체 총쏘는 모습 발포 line10 104x52 시작(0,918) 프레임 10개
	GetAnimator()->CreateAnimation(L"Shooting", m_pImage, Vec2(0.f, 1386.f),
		Vec2(156.f, 69.f), Vec2(40.f, -70.f), 156.f, 10, 0.05f);
	// 상체 위로 총쏘는 모습 line11 58x138 시작(0,970) 프레임 10개
	GetAnimator()->CreateAnimation(L"ShootingUpper", m_pImage, Vec2(0.f, 1464.f),
		Vec2(87.f, 198.f), Vec2(10.f, -140.f), 87.f, 10, 0.1f);
	// 점프 좌측 슈팅 line12	120x48	시작점(0,1108) 프레임 4개
	GetAnimator()->CreateAnimation(L"JumpShootingLeft", m_pImage, Vec2(0.f, 1662.f),
		Vec2(180.f, 71.f), Vec2(-49.f, -62.f), 180, 4, 0.1f);
	// 점프후 아래로 쏘는 총
	GetAnimator()->CreateAnimation(L"JumpShootingDown", m_pImage, Vec2(0.f, 1821.f),
		Vec2(69.f, 164.f), Vec2(0.f, -5.f), 69, 5, 0.1f);
	// 아래총 상태
	GetAnimator()->CreateAnimation(L"ShootingDown", m_pImage, Vec2(345.f, 1821.f),
		Vec2(69.f, 164.f), Vec2(0.f, -5.f), 69, 1, 0.1f);
	//폭탄 던지기
	GetAnimator()->CreateAnimation(L"Throw", m_pImage, Vec2(0.f, 3525.f),
		Vec2(87.f, 87.f), Vec2(0.f, -60.f), 97.f, 6, 0.1f);
	//위로 총
	GetAnimator()->CreateAnimation(L"Upper", m_pImage, Vec2(783.f, 1464.f),
		Vec2(87.f, 198.f), Vec2(15.f, -140.f), 97.f, 1, 0.1f);


	//===============상체========================
	//Machine Gun
	GetAnimator()->CreateAnimation(L"MachineGunStanding", m_pImage, Vec2(0.f, 2232.f),
		Vec2(111.f, 87.f), Vec2(0.f, -65.f), 111, 1, 0.1f);


		
	//칼 0, 2031 상체
	GetAnimator()->CreateAnimation(L"Knife", m_pImage, Vec2(0.f, 1983.f),
		Vec2(132.f, 146.f), Vec2(-62.f, -65.f), 132.f, 6,  0.1f);

	//좌측 애니메이션 구현
	ImageAnimation();


	GetRigidBody()->SetMaxSpeed(200.f);
	GetRigidBody()->SetMaxGravitySpeed(1000.f);
	GetRigidBody()->SetGround(false);
	GetRigidBody()->SetGravityAccel(Vec2(0.f, 800.f));
	GetRigidBody()->SetElasticity(false);// 탄성 불가능 하도록 설정
	GetRigidBody()->SetElastic(1.f);

	//캐릭터 소환
	GetAnimator()->Play(L"UpperBody", false);
	GetAnimator()->PlayLower(L"LowerBody", false);
	bLower = LOWERSTATE::LSTAND;
	bUpper = UPPERSTATE::STAND;
	pDirection = DIRECTION::RIGHT;
	//캐릭터 하체
	//GetAnimator()->PlayLower(L"Jumping", true);
	//카메라 플레이어 소환 여부 true 로 변경
	CCamera::GetInst()->setSummon(true);

	//카메라가 따라 다니도록 설정
	CCamera::GetInst()->SetTargetObject(this);


}

CPlayer1::~CPlayer1()
{

	
}


void CPlayer1::ImageAnimation()
{
	//좌측 방향 보는 애니메이션 이미지로 받아온다.
	m_pImageLeft = CResMgr::GetInst()->LoadImg(L"PlayerLeft", L"image\\player2.bmp");

	//하체
	GetAnimator()->CreateReverseLowerAnimation(L"LowerBodyLeft", m_pImageLeft, Vec2(0.f, 4350.f),
		Vec2(63.f, 48.f), Vec2(0.f, -20.f), 63.f, 4, 0.5f, true);
	// 하체 Running 완료
	GetAnimator()->CreateReverseLowerAnimation(L"RunningLeft", m_pImageLeft, Vec2(0.f, 4398.f),
		Vec2(93.f, 60.f), Vec2(-8.f, -28.f), 93.f, 12, 0.1f, true);
	// 하체 Jumping (아래 총 하체)
	GetAnimator()->CreateReverseLowerAnimation(L"JumpingLeft", m_pImageLeft, Vec2(6.f, 4458.f),
		Vec2(69.f, 72.f), Vec2(3.f, -30.f), 69.f, 6, 0.1f, true);
	// 하체 Jumping_Running
	GetAnimator()->CreateReverseLowerAnimation(L"JumpRunningLeft", m_pImageLeft, Vec2(0.f, 4530.f),
		Vec2(99.f, 63.f), Vec2(0.f, -20.f), 99.f, 6, 0.1f, true);


	//상체 12개
	GetAnimator()->CreateReverseAnimation(L"UpperBodyLeft", m_pImageLeft, Vec2(0.f, 807.f),
		Vec2(96.f, 84.f), Vec2(-5.f, -70.f), 96.f, 12, 0.5f, 1);
	// 상체 뛰는 모습
	GetAnimator()->CreateAnimation(L"UpperBodyJumpingLeft", m_pImageLeft, Vec2(0.f, 891.f),
		Vec2(96.f, 105.f), Vec2(-5.f, -60.f), 96.f, 3, 0.1f, 1);
	// 상체 총쏘는 모습 발포 line10 104x52 시작(0,918) 프레임 10개
	GetAnimator()->CreateReverseAnimation(L"ShootingLeft", m_pImageLeft, Vec2(0.f, 1386.f),
		Vec2(156.f, 69.f), Vec2(-45.f, -71.f), 156.f, 10, 0.05f, 1);
	// 상체 위로 총쏘는 모습 line11 58x138 시작(0,970) 프레임 10개
	GetAnimator()->CreateReverseAnimation(L"ShootingUpperLeft", m_pImageLeft, Vec2(0.f, 1464.f),
		Vec2(87.f, 198.f), Vec2(0.f, -140.f), 87.f, 10, 0.1f, 1);
	// 점프 좌측 슈팅 line12	120x48	시작점(0,1108) 프레임 4개
	GetAnimator()->CreateReverseAnimation(L"JumpShootingLeftLeft", m_pImageLeft, Vec2(0.f, 1662.f),
		Vec2(180.f, 71.f), Vec2(-49.f, -62.f), 180, 4, 0.1f, 1);
	// 점프후 아래로 쏘는 총
	GetAnimator()->CreateReverseAnimation(L"JumpShootingDownLeft", m_pImageLeft, Vec2(69.f, 1821.f),
		Vec2(69.f, 164.f), Vec2(0.f, -5.f), 69, 5, 0.1f, 1);
	// 아래총 상태
	GetAnimator()->CreateAnimation(L"ShootingDownLeft", m_pImageLeft, Vec2(0.f, 1821.f),
		Vec2(69.f, 164.f), Vec2(0.f, -5.f), 69, 1, 0.1f, 1);
	//폭탄 던지기
	GetAnimator()->CreateReverseAnimation(L"ThrowLeft", m_pImageLeft, Vec2(0.f, 3525.f),
		Vec2(87.f, 87.f), Vec2(0.f, -30.f), 97.f, 6, 0.1f, 1);
	//위로 총
	GetAnimator()->CreateAnimation(L"UpperLeft", m_pImageLeft, Vec2(0.f, 1464.f),
		Vec2(87.f, 198.f), Vec2(0.f, -140.f), 97.f, 1, 0.1f, 1);

}


void CPlayer1::Grenade()
{
	//폭탄 이있을때만 작동하도록한다.
	if (m_Bomb > 0)
	{
		// 폭탄을 던지게 되면 폭탄의 갯수가 줄어 든다. 
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


	// 키입력에 따른 이동
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


	//상체
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

	//하체
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


	//상체 하체 분리
	if (IsPressed(KEY_TYPE::RIGHT))
	{
		GetRigidBody()->AddForce(Vec2(500.f, 0.f));
	}
	if (IsPressed(KEY_TYPE::LEFT))
	{
		GetRigidBody()->AddForce(Vec2(-500.f, 0.f));
	}

	if (IsTap(KEY_TYPE::G) && GetRigidBody()->IsGround()) //수류탄 투척
	{
		if (m_Bomb > 0)
		{
			if (m_fAccTime >= 0.1f)
			{
				nUpper = UPPERSTATE::THROWINGBOMB;
				// 미사일 쏘기			
				CBomb* pBomb = Instantiate<CBomb>(GetPos() + Vec2(0.f, -50.f), LAYER_TYPE::PLAYER_PROJECTILE);

				Vec2 vV = pBomb->GetRigidBody()->GetVelocity();
				vV.y = -500.f;
				vV.x = +500.f;
				pBomb->GetRigidBody()->SetVelocity(vV);
				pBomb->GetRigidBody()->SetGround(false);

				m_fAccTime = 0.f;
				//수류탄 사용시 하나씩 줄여준다. 
				Grenade();
			}
		}

	}
	else if (pUpper == UPPERSTATE::THROWINGBOMB && GetRigidBody()->IsGround() 
		&& GetAnimator()->getCurrentAnim()->IsFinish()		)
	{
		nUpper = UPPERSTATE::STAND;
	}

	//점프( 땅에 도달했을 경우에만 뛸수 있도록 설정)
	if (GetRigidBody()->IsGround())
	{
		if (IsTap(KEY_TYPE::SPACE))
		{
			Vec2 vV = GetRigidBody()->GetVelocity();
			vV.y = -500.f;
			GetRigidBody()->SetVelocity(vV);
			GetRigidBody()->SetGround(false);
			//상 하체 상태
			nUpper = UPPERSTATE::JUMP;	 // 상체
			nLower = LOWERSTATE::LJUMP; // 하체
		}
		//점프 땅에 도달후 취소시 서있는 자세
		else if (pLower == LOWERSTATE::LJUMP && GetRigidBody()->IsGround())
		{
			//상 하체 상태
			nUpper = UPPERSTATE::STAND;	 // 상체
			nLower = LOWERSTATE::LSTAND; // 하체
		}
	}
	




	// 상체 우측 run
	if (IsTap(KEY_TYPE::RIGHT) && GetRigidBody()->IsGround())
	{
		nLower = LOWERSTATE::LRUN; //하체 달리기모션
		pDirection = DIRECTION::RIGHT;
	}
	else if (IsRelease(KEY_TYPE::RIGHT) && pLower == LOWERSTATE::LRUN
		&& GetRigidBody()->IsGround())
	{
		nUpper = UPPERSTATE::STAND;	 // 상체
		nLower = LOWERSTATE::LSTAND; // 하체
	}




	// 상체 좌측 run
	if (IsTap(KEY_TYPE::LEFT) && GetRigidBody()->IsGround() && pLower != LOWERSTATE::LRUN)
	{
		nLower = LOWERSTATE::LRUN; //하체 달리기모션
		pDirection = DIRECTION::LEFT;
	}
	else if (IsRelease(KEY_TYPE::LEFT) && pLower == LOWERSTATE::LRUN
		&& GetRigidBody()->IsGround())
	{
		nUpper = UPPERSTATE::STAND;	 // 상체
		nLower = LOWERSTATE::LSTAND; // 하체
	}


	if (IsTap(KEY_TYPE::UP) && GetRigidBody()->IsGround())
	{
		nUpper = UPPERSTATE::UPPERGUN; //총 위로 들기
	}
	else if (IsRelease(KEY_TYPE::UP) && pUpper == UPPERSTATE::UPPERGUN
		&& GetRigidBody()->IsGround())
	{
		nUpper = UPPERSTATE::STAND;
	}


	//상체 관련 함수(총)
	if ((IsTap(KEY_TYPE::X)) && GetRigidBody()->IsGround())
	{
		if (pUpper == UPPERSTATE::UPPERGUN)
		{
			nUpper = UPPERSTATE::UPPERSHOOTING;
		}
		else //일반 상태 총
		{
			nUpper = UPPERSTATE::SHOOT; //상체
		}

	}
	else if (IsTap(KEY_TYPE::X) && !GetRigidBody()->IsGround() &&
		pUpper == UPPERSTATE::SHOOTINGDOWN && pLower == LOWERSTATE::LUNDERJUMP) //x 눌리고 공중상태에서 아래보면
	{
		nUpper = UPPERSTATE::SHOOTINGLOWER;
		//아래로 총쏘는 장면과 함께 아래로 총알 발사

	}
	else if (IsRelease(KEY_TYPE::X) && pUpper == UPPERSTATE::UPPERSHOOTING   //총위로 쏘는 동안 X키 release발생시
		&& GetRigidBody()->IsGround())
	{
		nUpper = UPPERSTATE::UPPERGUN;
	}
	else if (IsRelease(KEY_TYPE::X) && pUpper == UPPERSTATE::SHOOT
		&& GetRigidBody()->IsGround())
	{
		nUpper = UPPERSTATE::STAND;	
	}
	else if (IsRelease(KEY_TYPE::X) && pUpper == UPPERSTATE::SHOOTINGLOWER) //x키 풀리면 총 자세만 유지
	{
		nUpper = UPPERSTATE::SHOOTINGDOWN;
	}

	//아래총 상태
	if (pUpper == UPPERSTATE::JUMP && pLower == LOWERSTATE::LJUMP)
	{
		if (IsTap(KEY_TYPE::DOWN))
		{
			//슈팅 상태에서 아래버튼시 총을 아래로 내리도록 설정
			nUpper = UPPERSTATE::SHOOTINGDOWN;
			nLower = LOWERSTATE::LUNDERJUMP;
		}
	}


	//이전 상태가 아래 총이면 땅에 닿는 순간 스탠드 상태로 변경
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
	
	//현재 상하체 상태에 따라 애니메이션 구현
	if (trigerUpper())
	{
		PlayU(this, pUpper);
	}
	if (trigerLower())
	{
		PlayL(this, pLower);
	}

	//현재 상태를 이전 상태로 돌려준다.


	//현재 하체 이전 하체로 넘겨줌
	bLower = pLower;
	bUpper = pUpper;

	// 방향 제어
	bDirection = pDirection; 

	SetPos(vPos);

	CObject::tick();

}

//하체 애니메이션
void CPlayer1::PlayL(CObject* _object, LOWERSTATE _Lstate)
{
	
	if (_Lstate == LOWERSTATE::LSTAND) // 걷기
	{
		if(pDirection == DIRECTION::RIGHT)
		_object->GetAnimator()->PlayLower(L"LowerBody", true);
		else
		_object->GetAnimator()->PlayLower(L"LowerBodyLeft", true);
	}
	else if (_Lstate == LOWERSTATE::LRUN) //달리기
	{
		if (pDirection == DIRECTION::RIGHT)
		_object->GetAnimator()->PlayLower(L"Running", true);
		else
		_object->GetAnimator()->PlayLower(L"RunningLeft", true);
	}
	else if (_Lstate == LOWERSTATE::LJUMP) //점프
	{
		if (pDirection == DIRECTION::RIGHT)
			_object->GetAnimator()->PlayLower(L"JumpRunning", false);
		else
			_object->GetAnimator()->PlayLower(L"JumpRunningLeft", false);
	}
	else if (_Lstate == LOWERSTATE::LUNDERJUMP) //아래총점프
	{
		if (pDirection == DIRECTION::RIGHT)
			_object->GetAnimator()->PlayLower(L"Jumping", false);
		else
			_object->GetAnimator()->PlayLower(L"JumpingLeft", false);
	}

}

//상체 애니메이션
void CPlayer1::PlayU(CObject* _object, UPPERSTATE _Ustate)
{
	if (_Ustate == UPPERSTATE::STAND) // 서있기
	{
		if (pDirection == DIRECTION::RIGHT)
		_object->GetAnimator()->Play(L"UpperBody", true);
		else
		_object->GetAnimator()->Play(L"UpperBodyLeft", true);
	}
	else if (_Ustate == UPPERSTATE::SHOOT) //쏘기
	{

		if (pDirection == DIRECTION::RIGHT)
		_object->GetAnimator()->Play(L"Shooting", true);
		else
		_object->GetAnimator()->Play(L"ShootingLeft", true);
	}
	else if (_Ustate == UPPERSTATE::JUMP) //점프
	{
		if (pDirection == DIRECTION::RIGHT)
			_object->GetAnimator()->Play(L"UpperBodyJumping", false);
		else
			_object->GetAnimator()->Play(L"UpperBodyJumpingLeft", false);
	}
	else if (_Ustate == UPPERSTATE::UPPERGUN) //위로 총
	{
		if (pDirection == DIRECTION::RIGHT)
			_object->GetAnimator()->Play(L"Upper", true);
		else
			_object->GetAnimator()->Play(L"UpperLeft", true);
	}
	else if (_Ustate == UPPERSTATE::UPPERSHOOTING) //위로 총 쏘기
	{
		if (pDirection == DIRECTION::RIGHT)
			_object->GetAnimator()->Play(L"ShootingUpper", true);
		else
			_object->GetAnimator()->Play(L"ShootingUpperLeft", true);
	}
	else if (_Ustate == UPPERSTATE::SHOOTINGDOWN) //아래총 상태
	{
		if (pDirection == DIRECTION::RIGHT)
			_object->GetAnimator()->Play(L"ShootingDown", true);
		else
			_object->GetAnimator()->Play(L"ShootingDownLeft", true);
	}
	else if (_Ustate == UPPERSTATE::SHOOTINGLOWER) //아래총 쏘고 있는 상태
	{
		if (pDirection == DIRECTION::RIGHT)
			_object->GetAnimator()->Play(L"JumpShootingDown", false);
		else
			_object->GetAnimator()->Play(L"JumpShootingDownLeft", false);
	}
	else if (_Ustate == UPPERSTATE::THROWINGBOMB) //폭탄 던지기
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

//이동 관련 함수 
void CPlayer1::Move()
{

}




void CPlayer1::UAnimation()
{

}

void CPlayer1::LAnimation()
{

}





// 충돌 시작
void CPlayer1::CollisionBeginOverlap(CCollider* _pOhterCollider)
{
	_pOhterCollider->GetOwner();
}





//충돌이 끝난 상태
void CPlayer1::CollisionEndOverlap(CCollider* _pOhterCollider)
{

}




void CPlayer1::Shooting(SHOOTINGDIR _dir)
{
	if (m_fAccTime >= 0.4f)
	{
		// 미사일 쏘기			
		CBullet* pMissile = Instantiate<CBullet>(GetPos() + Vec2(-50.f, 0.f), LAYER_TYPE::PLAYER_PROJECTILE);

		pMissile->SetDir(Vec2(0.f, -1.f));

		m_fAccTime = 0.f;
	}

	if (_dir == SHOOTINGDIR::KEY0)
	{

	}
}
