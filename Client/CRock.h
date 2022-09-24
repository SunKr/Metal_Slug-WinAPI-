#pragma once
#include "CObject.h"


class CRock :
    public CObject
{

private:
    CImage*     m_pRockImage;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    virtual void CollisionBeginOverlap(CCollider* _pOhterCollider) override;
    virtual void CollisionOverlap(CCollider* _pCollider) override;
    virtual void CollisionEndOverlap(CCollider* _pCollider) override;

    CRock* Clone() { return new CRock(*this); }

public:
    CRock();
    CRock(const CRock& _mon);
    ~CRock();
};

