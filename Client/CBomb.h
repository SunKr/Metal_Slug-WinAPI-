#pragma once
#include "CObject.h"
class CBomb :
    public CObject
{

private:
    CImage* GranadeImage;   //����ź Animation ���鶧 ����� �̹���
    CImage* Effect;
    int     GranadeCount;   //���� ����ź ����
    float   m_fSpeed;       //����ź ���ư��� �ӵ�
    Vec2    m_vDir;         // ����ź ����
    int     m_BoundCount = 0;
    bool    BombDelete = false; //��ź �浹 ����
public:


    int GetGranadeCount() { return GranadeCount; }
    void SetDir(Vec2 _vDir)  
    {  
        m_vDir = _vDir;
        m_vDir.Normalize();
    }

    Vec2 GetDir() { return m_vDir; }
    
public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;
public:
    virtual  void CollisionBeginOverlap(CCollider* _pOhterCollider) override;

public:
    CBomb* Clone() { return new CBomb(*this); }

public:
    CBomb();
    virtual ~CBomb();

};

