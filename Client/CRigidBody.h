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
    float   m_fFriction;        // �������� ũ��(�����̴°Ϳ� �ݴ����)
    float   m_fMaxSpeed;        // �߷��� �ƴ� �ִ� �ӷ� ����
    float   m_fMaxGravitySpeed; // �߷¿� ���� �߻��ϴ� �ִ� �ӷ� ����

    Vec2    m_vGravityAccel;    // �߷� ���ӵ�
    bool    m_bUseGravity;      // �߷� ����
    bool    m_bGround;          // ���� ���ִ��� Ȯ��
    
    float   m_elasticity;        // ź�� ��
    bool    m_IsElastic;         // ź�� ���� ����


public:
    virtual void tick() override;  


public:
    void SetElastic(float   _elasticity) { m_elasticity = _elasticity; }
    //ź�� ���� ���� ( ź�� ���� ���� ����)
    void SetElasticity(bool _elastic) { m_IsElastic = _elastic; }
    //��ü�� ���� �ش�. ���͸� ������Ų��. (ũ��+��������)
    void AddForce(Vec2 _vF) { m_vForce += _vF; }
    //���� �ӵ��� �ӵ��� �����ش�. 
    void AddVelocity(Vec2 _vVelocity) { m_vVelocity += _vVelocity; }
    // ���� �ӵ��� �������ش�.
    void SetVelocity(Vec2 _vVelocity) { m_vVelocity = _vVelocity; }
    // ���� �ӵ��� �˾� �´�. 
    Vec2 GetVelocity() { return m_vVelocity; }

    //���� ������ �������ش�. 
    void SetMass(float _fMass) { m_fMass = _fMass; }
    // ���� �ִ� �ӵ��� �������ش�. 
    void SetMaxSpeed(float _fMax) { m_fMaxSpeed = _fMax; }
    // ���� �ִ� �߷¼ӵ��� �������ش�.  
    void SetMaxGravitySpeed(float _fMax) { m_fMaxGravitySpeed = _fMax; }
    // ���� �߷��� �������ش�. 
    void SetGravity(bool _bSet) { m_bUseGravity = _bSet; }
    // ���� �߷� ���ӵ��� �������ش�. (�� + ����)
    void SetGravityAccel(Vec2 _vAccel) { m_vGravityAccel = _vAccel; }
    // ���� ������ �ƴ��� �������ش�. 
    void SetGround(bool _bGround) { m_bGround = _bGround; }
    
    //���� �ִ��� Ȯ�� �ϴ� �Լ�
    bool IsGround() { return m_bGround; }

public:
    CLONE(CRigidBody);

public:
    CRigidBody();
    ~CRigidBody();
};

