#pragma once
#include "CComponent.h"


// AI ���� 
// 1. �ٰŸ� AI
// 2. ���Ÿ� AI
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

