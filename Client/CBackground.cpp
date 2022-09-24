#include "pch.h"
#include "CBackground.h"
#include "CImage.h"
#include "CCollider.h"

#include "CMonster.h"
#include "CPlayer.h"
#include "CResMgr.h"
#include "CCamera.h"

#include "CAnimator.h"
#include "CRigidBody.h"

#include "CSceneMgr.h"
#include "CScene.h"

#include "CObject.h"
#include "CKeyMgr.h"

class CAnimator;

// 생성자 추가할 목록 component 
// collider가 있을 경우 collider추가
// 이미지의 경우 resouce 에서 가져온다. 
CBackground::CBackground()
	:m_pImage(nullptr)
	, m_BGType{}
{
	//백그라운드의 컴포넌트 애니메이터 추가
	AddComponent(new CAnimator);
	//기본적인 배경은 생성자를 통해서 설치 하도록한다.
	//해당하는 이미지 받아와서 map에 올린다.
	//m_pImage = CResMgr::GetInst()->
		//LoadImg(L"map", L"image\\main.bmp");

}


CBackground::CBackground(const CBackground& _background)
	: CObject(_background)
	, m_pImage(_background.m_pImage)
	, m_BGType(_background.m_BGType)
{
	
}

CBackground::~CBackground()
{

}

void CBackground::tick()
{


	CObject::tick();
}

void CBackground::render(HDC _dc)
{
	
	//카메라 위치를 가져온다. 
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	//메인 배경을 세팅할 경우에만 그려준다.
	if (m_BGType == BGTYPE::Map)
	{
		m_pImage = CResMgr::GetInst()->
			LoadImg(L"map", L"image\\map_edit.bmp");
		//로드한 이미지를 그려준다.
		TransparentBlt(_dc, (int)vPos.x
			, (int)vPos.y 
			, m_pImage->GetWidth(), m_pImage->GetHeight(), m_pImage->GetDC(), 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(), RGB(255, 0, 255));

	}
	else if (m_BGType == BGTYPE::Map1) //두번째 맵 불러 올때 
	{
		m_pImage = CResMgr::GetInst()->
			LoadImg(L"Map1", L"image\\Map1.bmp");
		TransparentBlt(_dc, (int)vPos.x
			, (int)vPos.y 
			, m_pImage->GetWidth(), m_pImage->GetHeight(), m_pImage->GetDC(), 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(), RGB(255, 0, 255));

	}
	

	CObject::render(_dc);

}

// 애니매이션 플레이 할 수 있도록 설정하는 함수
void CBackground::GetBackground(CObject* _obj)
{
	//일단 지역 변수를 통해서 애니메이션을 로드 받는다. 
	CImage* image;
	
	if (m_BGType == BGTYPE::map4_2)
	{
		//해당하는 이미지 받아와서 map에 올린다.
		m_pImage = CResMgr::GetInst()->
			LoadImg(L"mapAtlas", L"image\\map4_2.bmp");
		//받은 오브젝트 객체를 통해 animatio 제작한다.//3553.f, 140.f
		_obj->GetAnimator()->CreateAnimation(L"map4_2", m_pImage, Vec2(0.f, 0.f), Vec2(430.f, 272.f), Vec2(7106.f, 140.f), 430.f, 8, 0.1f);
		_obj->GetAnimator()->Play(L"map4_2", true);
	}
	else if (m_BGType == BGTYPE::map4_3)
	{
		m_pImage = CResMgr::GetInst()->
			LoadImg(L"mapAtlas1", L"image\\map4_3.bmp"); //3735.f, 156.f
		_obj->GetAnimator()->CreateAnimation(L"map4_3", m_pImage, Vec2(0.f, 0.f), Vec2(832.f, 304.f), Vec2(7000.f, 156.f), 832.f, 8, 0.1f);
		_obj->GetAnimator()->Play(L"map4_3", true);
	}
	
}



