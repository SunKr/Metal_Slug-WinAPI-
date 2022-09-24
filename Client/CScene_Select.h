#pragma once
#include "CScene.h"


enum class C_PLAYER
{
    MARCO,
    ERI,
    TARMA,
    FIO,
    END,
};

class CScene_Select :
    public CScene
{

private:
    //캐릭터 셀렉트 화면의 최종 위치
    Vec2 m_vSelectPos;
    //맵관련 이미지 이름으로 저장
    CImage* Select;
    //캐릭터 이미지
    CImage* Character;
    //마우스 위에 있는지 확인
    bool    m_bMouseOn;
    //플레이어 캐릭터 선택
    C_PLAYER e_Player;

public:
    virtual void tick() override;


    virtual void enter() override;


    virtual void exit() override;

    virtual void render(HDC _dc) override;

public:
    void switchCharacter(CImage* Character, C_PLAYER _character, HDC _dc, Vec2 _vPos);


public:

    CScene_Select();

    ~CScene_Select();
};


