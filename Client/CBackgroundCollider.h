#pragma once
#include "CObject.h"
class CBackgroundCollider :
    public CObject
{


private:
    //충돌배경 이미지를 받아 온다. 
    CImage* ColliderImage;

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;


 

public:
     CImage* GetImage() { return ColliderImage; }
 
public:


    CLONE(CBackgroundCollider);


    CBackgroundCollider();
    CBackgroundCollider(const CBackgroundCollider& _collider);
    ~CBackgroundCollider();
};

