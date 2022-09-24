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
    //ĳ���� ����Ʈ ȭ���� ���� ��ġ
    Vec2 m_vSelectPos;
    //�ʰ��� �̹��� �̸����� ����
    CImage* Select;
    //ĳ���� �̹���
    CImage* Character;
    //���콺 ���� �ִ��� Ȯ��
    bool    m_bMouseOn;
    //�÷��̾� ĳ���� ����
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


