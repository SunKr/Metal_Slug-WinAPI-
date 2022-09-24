#pragma once
#include "CObject.h"

class CImage;
class CPlayer;

class CMonster :
    public CObject
{
private:
    CImage*     m_pImage;
    CPlayer*    m_pPlayer;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    virtual void CollisionBeginOverlap(CCollider* _pOhterCollider) override;

    CMonster* Clone() { return new CMonster(*this); }

public:
    CMonster();
    CMonster(const CMonster& _mon);
    ~CMonster();
};

