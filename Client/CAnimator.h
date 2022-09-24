#pragma once
#include "CComponent.h"


//enum class ANIMATION_TYPE
//{
//    FULL,
//    LOWER,
//    UPPER,
//    END,
//};

class CAnimation;
class CAnimationLower; //��ü
class CEntity;
class CAnimation;
class CAnimationLower;

class CAnimator :
    public CComponent
{

private:
    //��ƼƼ ���� �迭 ����
    CEntity* m_arrCEntity[(UINT)ANIMATION_TYPE::END];

private:
    map<wstring, CAnimation*>           m_mapAnim;
    map<wstring, CAnimationLower*>      m_mapAnimLower;
    CAnimation*                         m_pCurAnim;
    CAnimationLower*                    m_pCurLowerAnim;

    bool                                m_bRepeat;      // �ݺ����
  

public:
    CAnimation* GetAnimation() const { return (CAnimation*)m_arrCEntity[(UINT)ANIMATION_TYPE::FULL]; }
    CAnimationLower* GetLower() const { return (CAnimationLower*)m_arrCEntity[(UINT)ANIMATION_TYPE::LOWER]; }
    


public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    // Animation��ü ����
    void CreateAnimation(const wstring& _strName, CImage* _pImage
        , Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset
        , float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation = true);
    // Animation ������ ��� ��ü
    void CreateLowerAnimation(const wstring& _strName, CImage* _pImage, Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset, float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation);
    // Animation �����
    void CreateReverseAnimation(const wstring& _strName, CImage* _pImage, Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset, float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation);

    void CreateReverseLowerAnimation(const wstring& _strName, CImage* _pImage, Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset, float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation);

    //ã��
    CAnimation* FindAnimation(const wstring& _strKey);
    CAnimationLower* FindLowerAnimation(const wstring& _strKey);

    //���
    void Play(const wstring& _strName, bool _bRepeat);
    void PlayLower(const wstring& _strName, bool _bRepeat);

    CAnimation* getCurrentAnim() {  return m_pCurAnim;  }
    
public:
    CLONE(CAnimator);

public:
    CAnimator();
    CAnimator(const CAnimator& _animator);
    ~CAnimator();
};

