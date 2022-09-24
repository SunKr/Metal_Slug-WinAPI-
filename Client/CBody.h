#pragma once
#include "CComponent.h"



//ĳ���� �����ӿ� ���� ����ü ���� �ִϸ��̼� ����

class CBody :
    public CComponent
{
private:
    map<wstring, CBody*>        m_mapBodyAnim;  //�ٵ� �ִϸ��̼� ����
    CBody*                      m_bCurAnim;     //���� ��ü �ִϸ��̼�
    BODY_TYPE                   m_bodyType;     //���� �ٵ� Ÿ�� ����
    bool                        m_bRepeat;      // �ݺ����

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

