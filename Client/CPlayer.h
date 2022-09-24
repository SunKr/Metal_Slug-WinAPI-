#pragma once
#include "CObject.h"


enum class PLAYER_STATE
{
    STANDING,
};

class CImage;

class CPlayer :
    public CObject
{
private:
    float               m_fSpeed;
    float               m_fAccTime;
    PLAYER_STATE        pBeforeState;
    PLAYER_STATE        pState;// 플레이어 

public:
    virtual void tick() override;   

    virtual void CollisionBeginOverlap(CCollider* _pOtherCollider) override;

public:
    virtual CPlayer* Clone() { return new CPlayer(*this); }

public:
    CPlayer();
    ~CPlayer();
};

