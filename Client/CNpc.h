#pragma once
#include "CObject.h"

enum class NPC_STATE
{
    NONE,
    BIND, //묶인 상태
    UNBIND, //푸는 상태
    FALL, //낙하
    LWALK,  //왼쪽으로 걷기
    ITEM,   //item 드랍
    SALUTE, //충성
    RUN,    //도망
};


class CImage;

class CNpc :
    public CObject
{

private:
    CImage*             m_NpcImage; //npc이미지 저장
    float               m_fAccTime;  // 시간초
    bool                m_binding; //묶여 있는지 여부
    bool                m_dropItem; //아이템 드롭 가능 여부




public:
    virtual void tick();
    void render(HDC _dc);

    virtual void CollisionBeginOverlap(CCollider* _pOhterCollider);

public:
    void Move();


public:

    CLONE(CNpc);

    CNpc();
    CNpc(const CNpc& _npc);
    ~CNpc();

};

