#pragma once
#include "CScene.h"

class CSound;

class CScene_Home :
    public CScene
{

private:
    //홈화면의 최종 위치:생성자 호출시 null로 초기화 중심부에 위치 하도록 한다. 
    Vec2    m_vHomePos; 
    // 홈화면 이미지를 저장할 장소ㄴ
    CImage* Home;

    CSound* pBGM;
    

public:
    virtual void tick() override;


    virtual void enter() override;


    virtual void exit() override;

    virtual void render(HDC _dc) override;

public:
    //생성자
    CScene_Home();
    //소멸자
    ~CScene_Home();


};

