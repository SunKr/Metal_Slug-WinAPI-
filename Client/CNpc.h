#pragma once
#include "CObject.h"

enum class NPC_STATE
{
    NONE,
    BIND, //���� ����
    UNBIND, //Ǫ�� ����
    FALL, //����
    LWALK,  //�������� �ȱ�
    ITEM,   //item ���
    SALUTE, //�漺
    RUN,    //����
};


class CImage;

class CNpc :
    public CObject
{

private:
    CImage*             m_NpcImage; //npc�̹��� ����
    float               m_fAccTime;  // �ð���
    bool                m_binding; //���� �ִ��� ����
    bool                m_dropItem; //������ ��� ���� ����




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

