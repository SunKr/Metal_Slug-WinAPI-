#pragma once
#include "CObject.h"
#include "CImage.h"
#include "CPlayer1.h"

class CPlayer1;

//ȭ�鿡 �׷��� UI ���� 
class CGUI :
    public CObject
{



private:
    CImage* m_pUIAtlas;   // UI �̹��� ����
    CImage* m_UI;
    //int         m_iImgIdx;      // Ư�� Ÿ��

    //�÷��̾� ������ ��ü �޾ƿ��� ����
    CPlayer1* pPlyaer;


    float   m_fDuration; // UI ���� �ð�
    float   m_fAccTime; // �����ð�
    int     m_MainTime; // Main ȭ�鿡 ��µǴ� �ʴ� �ð�
    float   m_TimeAcc; //���� �ð�
    float     m_fade; //���̵� insert
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

