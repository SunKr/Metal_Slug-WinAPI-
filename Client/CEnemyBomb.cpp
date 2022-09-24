#include "pch.h"
#include "CEnemyBomb.h"

#include "CResMgr.h"
#include "CSceneMgr.h"

#include "CBackgroundCollider.h"
#include "Cscene.h"

#include "CCollider.h"
#include "CRigidBody.h"

#include "CImage.h"


CEnemyBomb::CEnemyBomb()
	:RBomb(nullptr)
	,LBomb(nullptr)
	, GranadeCount(10)
	, m_fSpeed(0.f)
	, m_vDir()
{
	AddComponent(new CRigidBody);
	AddComponent(new CCollider);
	//AddComponent(new CAnimator);
	//우로 튀는 수류탄 이미지 가져온다. 
	RBomb = CResMgr::GetInst()->LoadImg(L"REnemyGranade", L"image\\REnemyGrenade.bmp");
	LBomb = CResMgr::GetInst()->LoadImg(L"LEnemyGranade", L"image\\LEnemyGrenade.bmp");
	//Effect = CResMgr::GetInst()LoadImg(L"Effect",  )
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
}

CEnemyBomb::~CEnemyBomb()
{


}


void CEnemyBomb::tick()
{

	// 미사일이 향하는 방향으로 이동한다.
	Vec2 vPos = GetPos();

	Ground_SET;

	//vPos.x += m_fSpeed * m_vDir.x * DT;
	//vPos.y += m_fSpeed * m_vDir.y * DT;

	SetPos(vPos);

	CObject::tick();
}

void CEnemyBomb::render(HDC _dc)
{
	//8 프레임 폭탄
	// 미사일 진행 방향에 따른 인덱스 계산
	UINT iWidth = RBomb->GetWidth() / 8;

	float fDot = m_vDir.Dot(Vec2(0.f, -1.f));
	float fAngle = acosf(fDot);

	// 각도가 180 를 넘을 때 보정하기 (양의 각도(작은 쪽) 로만 나오므로 더 큰 쪽 각도를 구하기 위함
	if (m_vDir.x < 0.f)
		fAngle = PI * 2 - fAngle;

	fAngle += PI / 16.f;

	// 인덱스가 0~7 을 넘어서 한바쿼 넘는 경우 다시 0으로
	int iImgIdx = (int)floor(fAngle / (PI / 4.f));
	if (iImgIdx >= 8)
	{
		iImgIdx = 0;
	}

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	TransparentBlt(_dc
		, (int)vPos.x - iWidth / 2
		, (int)vPos.y - RBomb->GetHeight() / 2
		, iWidth
		, RBomb->GetHeight()
		, RBomb->GetDC()
		, iImgIdx * iWidth
		, 0
		, iWidth
		, RBomb->GetHeight()
		, RGB(255, 0, 255));

	CObject::render(_dc);
}
