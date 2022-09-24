#include "pch.h"
#include "CRock.h"


#include "CComponent.h"
#include "CCollider.h"
#include "CCollisionMgr.h"

#include "CResMgr.h"
#include "CImage.h"
#include "CCamera.h"
#include "CResource.h"

#include "CPlayer1.h"
#include "CRigidBody.h"

class CCollider;

CRock::CRock()
	:m_pRockImage(nullptr)
{

	AddComponent(new CCollider);
	m_pRockImage = CResMgr::GetInst()->LoadImg(L"Rock", L"image\\rock.bmp");



	//GetCollider()->SetOffset(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(192.f, 135.f));
}

CRock::CRock(const CRock& _mon)
	:CObject(_mon)
	, m_pRockImage(_mon.m_pRockImage)
{


}

CRock::~CRock()
{

}
void CRock::tick()
{


	CObject::tick();
}

void CRock::render(HDC _dc)
{
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	BLENDFUNCTION tFunc = {};
	tFunc.BlendOp = AC_SRC_OVER;
	tFunc.BlendFlags = 0;
	tFunc.AlphaFormat = AC_SRC_ALPHA;
	tFunc.SourceConstantAlpha = 255;

	AlphaBlend(_dc, (int)vPos.x - 192/2
		, (int)vPos.y - 135/2
		, 192, 135
		, m_pRockImage->GetDC(), 0, 0, 192, 135, tFunc);

	CObject::render(_dc);
}

void CRock::CollisionBeginOverlap(CCollider* _pCollider)
{

}

void CRock::CollisionOverlap(CCollider* _pCollider)
{

}

void CRock::CollisionEndOverlap(CCollider* _pCollider)
{

}

