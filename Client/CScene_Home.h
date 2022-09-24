#pragma once
#include "CScene.h"

class CSound;

class CScene_Home :
    public CScene
{

private:
    //Ȩȭ���� ���� ��ġ:������ ȣ��� null�� �ʱ�ȭ �߽ɺο� ��ġ �ϵ��� �Ѵ�. 
    Vec2    m_vHomePos; 
    // Ȩȭ�� �̹����� ������ ��Ҥ�
    CImage* Home;

    CSound* pBGM;
    

public:
    virtual void tick() override;


    virtual void enter() override;


    virtual void exit() override;

    virtual void render(HDC _dc) override;

public:
    //������
    CScene_Home();
    //�Ҹ���
    ~CScene_Home();


};

