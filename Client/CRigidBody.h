#pragma once
#include "CComponent.h"

class CRigidBody :
    public CComponent
{
private:
    Vec2    m_vForce;
    Vec2    m_vAccel;
    Vec2    m_vVelocity;

    float   m_fMass;
    float   m_fFriction;        // 마찰력의 크기(움직이는것에 반대방향)
    float   m_fMaxSpeed;        // 중력이 아닌 최대 속력 제한
    float   m_fMaxGravitySpeed; // 중력에 의해 발생하는 최대 속력 제한

    Vec2    m_vGravityAccel;    // 중력 가속도
    bool    m_bUseGravity;      // 중력 적용
    bool    m_bGround;          // 땅에 서있는지 확인
    
    float   m_elasticity;        // 탄성 힘
    bool    m_IsElastic;         // 탄성 가능 여부


public:
    virtual void tick() override;  


public:
    void SetElastic(float   _elasticity) { m_elasticity = _elasticity; }
    //탄성 여부 세팅 ( 탄성 가능 여부 세팅)
    void SetElasticity(bool _elastic) { m_IsElastic = _elastic; }
    //강체에 힘을 준다. 벡터를 누적시킨다. (크기+방향정보)
    void AddForce(Vec2 _vF) { m_vForce += _vF; }
    //현재 속도에 속도를 더해준다. 
    void AddVelocity(Vec2 _vVelocity) { m_vVelocity += _vVelocity; }
    // 현재 속도를 설정해준다.
    void SetVelocity(Vec2 _vVelocity) { m_vVelocity = _vVelocity; }
    // 현재 속도를 알아 온다. 
    Vec2 GetVelocity() { return m_vVelocity; }

    //현재 질량을 설정해준다. 
    void SetMass(float _fMass) { m_fMass = _fMass; }
    // 현재 최대 속도를 설정해준다. 
    void SetMaxSpeed(float _fMax) { m_fMaxSpeed = _fMax; }
    // 현재 최대 중력속도를 설정해준다.  
    void SetMaxGravitySpeed(float _fMax) { m_fMaxGravitySpeed = _fMax; }
    // 현재 중력을 설정해준다. 
    void SetGravity(bool _bSet) { m_bUseGravity = _bSet; }
    // 현재 중력 가속도를 설정해준다. (힘 + 방향)
    void SetGravityAccel(Vec2 _vAccel) { m_vGravityAccel = _vAccel; }
    // 현재 땅인지 아닌지 설정해준다. 
    void SetGround(bool _bGround) { m_bGround = _bGround; }
    
    //땅이 있는지 확인 하는 함수
    bool IsGround() { return m_bGround; }

public:
    CLONE(CRigidBody);

public:
    CRigidBody();
    ~CRigidBody();
};

