
#include "CAnimation.h"
class CLowerBody :
    public CAnimation
{
    CAnimator* m_pAnimator;

    vector<tAnimFrm>    m_vecFrmLower;   // 모든 프레임 정보
    CImage*             m_pImageLower;   // Animation Frame Image

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


    friend class CAnimator;

public:
    CLowerBody();
    ~CLowerBody();

};
