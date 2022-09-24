#pragma once
#include "CComponent.h"



//캐릭터 움직임에 따라서 상하체 구분 애니메이션 제작

class CBody :
    public CComponent
{
private:
    map<wstring, CBody*>        m_mapBodyAnim;  //바디 애니메이션 저장
    CBody*                      m_bCurAnim;     //현재 몸체 애니메이션
    BODY_TYPE                   m_bodyType;     //현재 바디 타입 종류
    bool                        m_bRepeat;      // 반복재생

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:


    virtual  void CreateAnimation(const wstring& _strName, CImage* _pImage
        , Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset
        , float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation = true) {};

    virtual CBody* FindAnimation(const wstring& _strKey) {};
    virtual void Play(const wstring& _strName, bool _bRepeat) {};

public:
    CLONE(CBody);

public:
    CBody();
    CBody(const CBody& _animator);
    ~CBody();

};

