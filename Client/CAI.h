#pragma once
#include "CComponent.h"


// AI 구현 
// 1. 근거리 AI
// 2. 원거리 AI
// 3. NPC   AI

class CAI :
    public CComponent
{


private:


public:
    virtual void tick() override;



public:

    CLONE(CAI);

    CAI();
    ~CAI();
};

