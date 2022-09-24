#pragma once
#include "CObject.h"
#include "CAnimator.h"
#include "CResMgr.h"

class CImage;
class CMonster;
class CPlayer;



class CBackground :
    public CObject
{


private:
    
    CImage* m_pImage; //�̹���
    BGTYPE  m_BGType; //��� 


public:

    virtual void tick();
    virtual void render(HDC _dc);


public:
    virtual CBackground* Clone() { return new CBackground(*this); }  
 
public:
    //�θ� ������Ʈ���� ���� 
    virtual void GetBackground(CObject* _obj);


    virtual void setBGType(BGTYPE _etype)
    {
        m_BGType = _etype;
    }


public:
    CBackground();
    //CBackground(const wstring& _strKey, BGTYPE _eType);
    //��׶��� ���� ������

    //���� ������
   // CBackground();


    CBackground(const CBackground& _background);
    ~CBackground();



  


};

