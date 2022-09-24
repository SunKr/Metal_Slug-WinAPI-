#pragma once
#include "CObject.h"
class CBomb :
    public CObject
{

private:
    CImage* GranadeImage;   //수류탄 Animation 만들때 사용할 이미지
    CImage* Effect;
    int     GranadeCount;   //현재 수류탄 숫자
    float   m_fSpeed;       //수류탄 날아가는 속도
    Vec2    m_vDir;         // 수류탄 방향
    int     m_BoundCount = 0;
    bool    BombDelete = false; //폭탄 충돌 여부
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

