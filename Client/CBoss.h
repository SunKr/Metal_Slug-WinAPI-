#pragma once
#include "CObject.h"


class CImage;
class CPlayer1;

class CBoss :
    public CObject
{
private:
    CImage* m_pImage;
    CPlayer1* m_pPlayer;

    float        m_Speed;
    float        m_Time;
    float        m_DropRate = 0.2f;// 
    float        m_AtkRate = 2.0f;
    bool         isAtk;
    DIRECTION    m_Direction; //보스 움직이는 방향
    DIRECTION    cDirection;
    DIRECTION    bDirection;
    DIRECTION    nDirection;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    void DropBomb();

    void AddBomb();

public:
    // virtual void CollisionBeginOverlap(CCollider* _pOhterCollider) override;

    CBoss* Clone() { return new CBoss(*this); }



public:
    CBoss();
    CBoss(const CBoss& _mon);
    ~CBoss();
};






