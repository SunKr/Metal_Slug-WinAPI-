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
class CAnimationLower; //하체
class CEntity;
class CAnimation;
class CAnimationLower;

class CAnimator :
    public CComponent
{

private:
    //엔티티 관련 배열 생성
    CEntity* m_arrCEntity[(UINT)ANIMATION_TYPE::END];

private:
    map<wstring, CAnimation*>           m_mapAnim;
    map<wstring, CAnimationLower*>      m_mapAnimLower;
    CAnimation*                         m_pCurAnim;
    CAnimationLower*                    m_pCurLowerAnim;

    bool                                m_bRepeat;      // 반복재생
  

public:
    CAnimation* GetAnimation() const { return (CAnimation*)m_arrCEntity[(UINT)ANIMATION_TYPE::FULL]; }
    CAnimationLower* GetLower() const { return (CAnimationLower*)m_arrCEntity[(UINT)ANIMATION_TYPE::LOWER]; }
    


public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    // Animation상체 위주
    void CreateAnimation(const wstring& _strName, CImage* _pImage
        , Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset
        , float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation = true);
    // Animation 정방향 재생 하체
    void CreateLowerAnimation(const wstring& _strName, CImage* _pImage, Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset, float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation);
    // Animation 역재생
    void CreateReverseAnimation(const wstring& _strName, CImage* _pImage, Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset, float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation);

    void CreateReverseLowerAnimation(const wstring& _strName, CImage* _pImage, Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset, float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation);

    //찾기
    CAnimation* FindAnimation(const wstring& _strKey);
    CAnimationLower* FindLowerAnimation(const wstring& _strKey);

    //재생
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

