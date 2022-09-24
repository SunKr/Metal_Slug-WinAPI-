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
	//��� Ƣ�� ����ź �̹��� �����´�. 
	RBomb = CResMgr::GetInst()->LoadImg(L"REnemyGranade", L"image\\REnemyGrenade.bmp");
	LBomb = CResMgr::GetInst()->LoadImg(L"LEnemyGranade", L"image\\LEnemyGrenade.bmp");
	//Effect = CResMgr::GetInst()LoadImg(L"Effect",  )
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
}

CEnemyBomb::~CEnemyBomb()
{


}


void CEnemyBomb::tick()
{

	// �̻����� ���ϴ� �������� �̵��Ѵ�.
	Vec2 vPos = GetPos();

	Ground_SET;

	//vPos.x += m_fSpeed * m_vDir.x * DT;
	//vPos.y += m_fSpeed * m_vDir.y * DT;

	SetPos(vPos);

	CObject::tick();
}

void CEnemyBomb::render(HDC _dc)
{
	//8 ������ ��ź
	// �̻��� ���� ���⿡ ���� �ε��� ���
	UINT iWidth = RBomb->GetWidth() / 8;

	float fDot = m_vDir.Dot(Vec2(0.f, -1.f));
	float fAngle = acosf(fDot);

	// ������ 180 �� ���� �� �����ϱ� (���� ����(���� ��) �θ� �����Ƿ� �� ū �� ������ ���ϱ� ����
	if (m_vDir.x < 0.f)
		fAngle = PI * 2 - fAngle;

	fAngle += PI / 16.f;

	// �ε����� 0~7 �� �Ѿ �ѹ��� �Ѵ� ��� �ٽ� 0����
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
