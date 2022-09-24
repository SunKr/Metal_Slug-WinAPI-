#include "pch.h"
#include "CBackgroundCollider.h"

#include "CResMgr.h"
#include "CCamera.h"
#include "CImage.h"
#include "CPlayer1.h"
#include "CCollider.h"

#include "CRigidBody.h"
#include "CScene.h"
#include "CSceneMgr.h"

CBackgroundCollider::CBackgroundCollider()
	:ColliderImage(nullptr)
{
	AddComponent(new CCollider);
	//ó���� �̹��� �޾ƿ´�. �̹��� �Ű������� �����Ѵ�.
	ColliderImage= CResMgr::GetInst()->LoadImg(L"map_collider", L"image\\map_collider1.bmp");

	

}

CBackgroundCollider::CBackgroundCollider(const CBackgroundCollider& _collider)
	:ColliderImage(_collider.ColliderImage)
{
	

}

CBackgroundCollider::~CBackgroundCollider()
{


}




void CBackgroundCollider::tick()
{


	CObject::tick();
}

void CBackgroundCollider::render(HDC _dc)
{

	//���� ��ġ�� �����´�. 
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	TransparentBlt(_dc, (int)vPos.x
		, (int)vPos.y
		, ColliderImage->GetWidth(), ColliderImage->GetHeight(), ColliderImage->GetDC(), 0, 0, ColliderImage->GetWidth(), ColliderImage->GetHeight(), RGB(255, 0, 255));

	CObject::render(_dc);
}



