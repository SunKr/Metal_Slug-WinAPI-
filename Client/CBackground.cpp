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

// ������ �߰��� ��� component 
// collider�� ���� ��� collider�߰�
// �̹����� ��� resouce ���� �����´�. 
CBackground::CBackground()
	:m_pImage(nullptr)
	, m_BGType{}
{
	//��׶����� ������Ʈ �ִϸ����� �߰�
	AddComponent(new CAnimator);
	//�⺻���� ����� �����ڸ� ���ؼ� ��ġ �ϵ����Ѵ�.
	//�ش��ϴ� �̹��� �޾ƿͼ� map�� �ø���.
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
	
	//ī�޶� ��ġ�� �����´�. 
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(GetPos());

	//���� ����� ������ ��쿡�� �׷��ش�.
	if (m_BGType == BGTYPE::Map)
	{
		m_pImage = CResMgr::GetInst()->
			LoadImg(L"map", L"image\\map_edit.bmp");
		//�ε��� �̹����� �׷��ش�.
		TransparentBlt(_dc, (int)vPos.x
			, (int)vPos.y 
			, m_pImage->GetWidth(), m_pImage->GetHeight(), m_pImage->GetDC(), 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(), RGB(255, 0, 255));

	}
	else if (m_BGType == BGTYPE::Map1) //�ι�° �� �ҷ� �ö� 
	{
		m_pImage = CResMgr::GetInst()->
			LoadImg(L"Map1", L"image\\Map1.bmp");
		TransparentBlt(_dc, (int)vPos.x
			, (int)vPos.y 
			, m_pImage->GetWidth(), m_pImage->GetHeight(), m_pImage->GetDC(), 0, 0, m_pImage->GetWidth(), m_pImage->GetHeight(), RGB(255, 0, 255));

	}
	

	CObject::render(_dc);

}

// �ִϸ��̼� �÷��� �� �� �ֵ��� �����ϴ� �Լ�
void CBackground::GetBackground(CObject* _obj)
{
	//�ϴ� ���� ������ ���ؼ� �ִϸ��̼��� �ε� �޴´�. 
	CImage* image;
	
	if (m_BGType == BGTYPE::map4_2)
	{
		//�ش��ϴ� �̹��� �޾ƿͼ� map�� �ø���.
		m_pImage = CResMgr::GetInst()->
			LoadImg(L"mapAtlas", L"image\\map4_2.bmp");
		//���� ������Ʈ ��ü�� ���� animatio �����Ѵ�.//3553.f, 140.f
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



