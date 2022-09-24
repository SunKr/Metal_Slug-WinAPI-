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
    
    CImage* m_pImage; //이미지
    BGTYPE  m_BGType; //배경 


public:

    virtual void tick();
    virtual void render(HDC _dc);


public:
    virtual CBackground* Clone() { return new CBackground(*this); }  
 
public:
    //부모 오브젝트에서 받은 
    virtual void GetBackground(CObject* _obj);


    virtual void setBGType(BGTYPE _etype)
    {
        m_BGType = _etype;
    }


public:
    CBackground();
    //CBackground(const wstring& _strKey, BGTYPE _eType);
    //백그라운드 복사 생성자

    //대입 생성자
   // CBackground();


    CBackground(const CBackground& _background);
    ~CBackground();



  


};

