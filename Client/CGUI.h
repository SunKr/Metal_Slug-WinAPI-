#pragma once
#include "CObject.h"
#include "CImage.h"
#include "CPlayer1.h"

class CPlayer1;

//화면에 그래픽 UI 생성 
class CGUI :
    public CObject
{



private:
    CImage* m_pUIAtlas;   // UI 이미지 모음
    CImage* m_UI;
    //int         m_iImgIdx;      // 특정 타일

    //플레이어 포인터 객체 받아오는 변수
    CPlayer1* pPlyaer;


    float   m_fDuration; // UI 유지 시간
    float   m_fAccTime; // 누적시간
    int     m_MainTime; // Main 화면에 출력되는 초당 시간
    float   m_TimeAcc; //축적 시간
    float     m_fade; //페이드 insert
public:
    virtual void tick();
    virtual void render(HDC _dc);

    SCORE CalculateNumber(int m_number, DIGIT _digit);


    CLONE(CGUI);

public:
    CGUI();
    CGUI(const CGUI& _ui);
    ~CGUI();

};

