#pragma once

#include "CEntity.h"
#include "CCamera.h"

class CComponent;
class CCollider;
class CAnimator;
class CRigidBody;

class CObject :
    public CEntity
{
private:
    CComponent* m_arrComponent[(UINT)COMPONENT_TYPE::END];

   
    Vec2        m_vPos;
    Vec2        m_vScale;

    bool        m_bDead;


public:
    void        SetPos(Vec2 _vPos) { m_vPos = _vPos; }
    void        SetScale(Vec2 _vScale) { m_vScale = _vScale; }

    Vec2        GetPos() const { return m_vPos; }
    Vec2        GetScale() const { return m_vScale; }

    bool        IsDead() const { return m_bDead; }

    CCollider*  GetCollider() const { return (CCollider*)m_arrComponent[(UINT)COMPONENT_TYPE::COLLIDER]; }
    CAnimator*  GetAnimator() const { return (CAnimator*)m_arrComponent[(UINT)COMPONENT_TYPE::ANIMATOR]; }
    CRigidBody* GetRigidBody() const { return (CRigidBody*)m_arrComponent[(UINT)COMPONENT_TYPE::RIGIDBODY]; }
   
    void AddComponent(CComponent* _pComponent);
      

public:
    virtual void tick();
    virtual void render(HDC _dc);

    // 충돌 이벤트
    virtual void CollisionBeginOverlap(CCollider* _pOhterCollider) {};
    virtual void CollisionOverlap(CCollider* _pOhterCollider) {};
    virtual void CollisionEndOverlap(CCollider* _pOhterCollider) {};


public:
   // 배경일시 배경 선택하는 함수 
    virtual     void GetBackground(CObject* _obj) {};
    virtual     void setBGType(BGTYPE _etype) {};
   
    virtual     CComponent* GetColliderComponent() { return  m_arrComponent[(UINT)COMPONENT_TYPE::COLLIDER]; }


private:
    void SetDead() { m_bDead = true; }


public:
    //물체가 움직일때 사용
   // virtual void Move(Vec2 _pos) {};


public:
    virtual CObject* Clone() = 0;

public:
    CObject();    
    CObject(const CObject& _obj);
    virtual ~CObject();

    friend class CEventMgr;
};

