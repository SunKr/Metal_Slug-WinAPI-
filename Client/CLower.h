#pragma once
#include "CBody.h"


//다리 의 경우 다리만 움직이는 형태로 
// 다리 종류
/*
1. 오른쪽 걷기
2. 왼쪽 걷기
3. 점프 
4. 점프 오른쪽
5. 점프 왼쪽
6. 서있기로 구성
*/


class CImage;


struct tAnimFrm
{
    Vec2    vLeftTop;   // 이미지 내에서 좌상단 픽셀좌표
    Vec2    vSize;      // 좌상단으로부터 잘라낼 가로 세로 픽셀 길이    
    Vec2    vOffset;    // 출력 위치 오프셋
    float   fDuration;  // 해당 프레임 유지시간
};

class CLower :
    public CBody
{
private:

    CBody* m_pAnimator; //현재 몸체

    vector<tAnimFrm>    m_vecFrm;   // 모든 프레임 정보
    CImage* m_pImage;   // Animation Frame Image

    int                 m_iCurFrm;  // 현재 노출 시킬 프레임 인덱스
    float               m_fAccTime; // 누적시간

    bool                m_bCamRelation; // 카메라 영향
    bool                m_bFinish;  // 재생 완료

public:

    void tick();
    void render(HDC _dc);


public:
    void Create(CImage* _pImage, Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset
        , float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation);

    void Reset()
    {
        m_iCurFrm = 0;
        m_bFinish = false;
        m_fAccTime = 0.f;
    }

    bool IsFinish() { return m_bFinish; }


public:
    //가상함수 모음
    virtual  void CreateAnimation(const wstring& _strName, CImage* _pImage
        , Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset
        , float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation = true);

    virtual CBody* FindAnimation(const wstring& _strKey);
    virtual void Play(const wstring& _strName, bool _bRepeat);


public:
    CLower();
    ~CLower();
};

