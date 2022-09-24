#pragma once
#include "CEntity.h"
class CImage;



class CAnimator;

enum class MOTION
{
    STANDING,
    RIGHT,
    LEFT,

};



//��ü ���� Animation ����

class CAnimationLower :
    public CEntity
{
private:
    CAnimator* m_pAnimator;

    vector<tAnimFrm>    m_vecFrm;   // ��� ������ ����
    CImage* m_pImage;   // Animation Frame Image

    int                 m_iCurFrm;  // ���� ���� ��ų ������ �ε���
    float               m_fAccTime; // �����ð�

    bool                m_bCamRelation; // ī�޶� ����
    bool                m_bFinish;  // ��� �Ϸ�


public:
    void tick();
    void render(HDC _dc);

public:
    void Create(CImage* _pImage, Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset
        , float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation);

    void CreateReverse(CImage* _pImage, Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset, float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation);

    void Reset()
    {
        m_iCurFrm = 0;
        m_bFinish = false;
        m_fAccTime = 0.f;
    }

    bool IsFinish() { return m_bFinish; }
    int  GetCurFrm() { return m_iCurFrm; }

public:
    CAnimationLower();
    ~CAnimationLower();

    friend class CAnimator;
};

