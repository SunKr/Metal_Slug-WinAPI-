#include "pch.h"
#include "Item.h"

#include "CCollider.h"
#include "CResMgr.h"

#include "CComponent.h"
#include "CAnimator.h"
#include "CBullet.h"

Item::Item()
	:m_Item(nullptr)
{

	AddComponent(new CCollider);
	AddComponent(new CAnimator);

	GetCollider()->SetOffset(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(0.f, 0.f));

	//������ �����´�.
	m_Item = CResMgr::GetInst()->LoadImg(L"Item", L"image\\item.bmp");

	//�ڽ�
	GetAnimator()->CreateAnimation(L"BoxDestroy", m_Item, Vec2(0.f, 0.f),
		Vec2(138.f, 147.f), Vec2(0.f, 0.f), 138.f, 1, 1.0f);
	// �ڽ� �������� Animation
	GetAnimator()->CreateAnimation(L"BoxDestroy", m_Item, Vec2(0.f, 147.f),
		Vec2(138.f, 147.f), Vec2(0.f, 0.f), 138.f, 12, 0.1f);
	// ������
	GetAnimator()->CreateAnimation(L"BoxDestroy", m_Item, Vec2(0.f, 294.f),
		Vec2(66.f, 60.f), Vec2(0.f, 0.f), 66.f, 1, 1.0f);
	// ������ ȹ��� 
	GetAnimator()->CreateAnimation(L"BoxDestroy", m_Item, Vec2(0.f, 354.f),
		Vec2(138.f, 147.f), Vec2(0.f, 0.f), 138.f, 7, 1.0f);

}

Item::Item(const Item& _item)
	: CObject(_item)
	, m_Item(_item.m_Item)
{

}

Item::~Item()
{

}



void Item::tick()
{

}

void Item::CollisionBeginOverlap(CCollider* _pOhterCollider)
{
	//�Ѿ˰� �ε����� �Ǵ� ��� ���ε� Ǭ��. 
	if (dynamic_cast<CBullet*>(_pOhterCollider->GetOwner()))
	{

	}
}
