#pragma once
#include "CObject.h"

class CImage;

class Item :
    public CObject
{

private:
    CImage* m_Item;


public:
    virtual void tick() override;
    void CollisionBeginOverlap(CCollider* _pOhterCollider);
  






    CLONE(Item);


public:

    Item();
    Item(const Item& _item);
    ~Item();

    
};

