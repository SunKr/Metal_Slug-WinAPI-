#include "pch.h"
#include "CMissile.h"

#include "CEngine.h"
#include "CTimeMgr.h"

#include "CResMgr.h"
#include "CImage.h"
#include "CCollider.h"

CMissile::CMissile()
	: m_pImage(nullptr)
	, m_fSpeed(400.f)	
{
	m_pImage = CResMgr::GetInst()->LoadImg(L"Missile_01", L"image\\missile.bmp");

	AddComponent(new CCollider);
	GetCollider()->SetScale(Vec2(10.f, 30.f));
	GetCollider()->SetOffset(Vec2(0.f, -10.f));
}

CMissile::~CMissile()
{
}

void CMissile::tick()
{
	// �̻����� ���ϴ� �������� �̵��Ѵ�.
	Vec2 vPos = GetPos();

	vPos.x += m_fSpeed * m_vDir.x * DT;
	vPos.y += m_fSpeed * m_vDir.y * DT;

	SetPos(vPos);

	CObject::tick();
}

void CMissile::render(HDC _dc)
{	
	// �̻��� ���� ���⿡ ���� �ε��� ���
	UINT iWidth = m_pImage->GetWidth() / 16;

	float fDot = m_vDir.Dot(Vec2(0.f, -1.f));
	float fAngle = acosf(fDot);

	// ������ 180 �� ���� �� �����ϱ� (���� ����(���� ��) �θ� �����Ƿ� �� ū �� ������ ���ϱ� ����
	if (m_vDir.x < 0.f)
		fAngle = PI * 2 - fAngle;

	fAngle += PI / 8.f;

	// �ε����� 0~7 �� �Ѿ �ѹ��� �Ѵ� ��� �ٽ� 0����
	int iImgIdx = (int)floor(fAngle / (PI / 4.f));
	if (iImgIdx >= 8)
	{
		iImgIdx = 0;
	}

	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	TransparentBlt(_dc
		, (int)vPos.x - iWidth / 2
		, (int)vPos.y - m_pImage->GetHeight() / 2
		, iWidth
		, m_pImage->GetHeight()
		, m_pImage->GetDC()
		, iImgIdx * iWidth
		, 0
		, iWidth
		, m_pImage->GetHeight()
		, RGB(255, 0, 255));

	CObject::render(_dc);
}

