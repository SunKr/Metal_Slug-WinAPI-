#pragma once
#include "CObject.h"

class CBullet :
    public CObject
{
private:
    CImage* m_pImage;
    CImage* m_Explosion;
    float   m_fSpeed;
    Vec2    m_vDir;
    float   m_fAccTime;

    bool    m_NpcCollision;
    bool    m_EnemyCollision;

public:
    void SetDir(Vec2 _vDir)
    {
        m_vDir = _vDir;
        m_vDir.Normalize();
    }

    Vec2 GetDir() { return m_vDir; }

    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:

    virtual void CollisionBeginOverlap(CCollider* _pOhterCollider) ;




public:
    CBullet* Clone() { return new CBullet(*this); }

public:
    CBullet();
    ~CBullet();
};

