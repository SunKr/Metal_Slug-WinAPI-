#pragma once
#include "CScene.h"
#include "CComponent.h"
#include "CObject.h"


class Game_Scene :
    public CScene
{

private:
    float   m_fAccTime;
public:    
    virtual void tick() override;


    virtual void enter() override;
    virtual void exit() override;

public:
    Game_Scene();
    ~Game_Scene();

    friend class CBackGround;
};

