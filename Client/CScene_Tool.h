#pragma once
#include "CScene.h"
#include "CAnimator.h"


enum class TOOL_MODE
{
    TILE,
    OBJECT,
    ANIMATION,
    NONE,
};

class CScene_Tool :
    public CScene
{
private:
    TOOL_MODE   m_eMode;

private:
    void TileMode();
    void CreateUI();


public:    
    virtual void tick() override;
    virtual void enter() override;
    virtual void exit() override;

public:
    void TileSave();
    void TileLoad();

public:
    CScene_Tool();
    ~CScene_Tool();
};

