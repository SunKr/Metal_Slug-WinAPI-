#pragma once
#include "CBody.h"


//�ٸ� �� ��� �ٸ��� �����̴� ���·� 
// �ٸ� ����
/*
1. ������ �ȱ�
2. ���� �ȱ�
3. ���� 
4. ���� ������
5. ���� ����
6. ���ֱ�� ����
*/


class CImage;


struct tAnimFrm
{
    Vec2    vLeftTop;   // �̹��� ������ �»�� �ȼ���ǥ
    Vec2    vSize;      // �»�����κ��� �߶� ���� ���� �ȼ� ����    
    Vec2    vOffset;    // ��� ��ġ ������
    float   fDuration;  // �ش� ������ �����ð�
};

class CLower :
    public CBody
{
private:

    CBody* m_pAnimator; //���� ��ü

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

    void Reset()
    {
        m_iCurFrm = 0;
        m_bFinish = false;
        m_fAccTime = 0.f;
    }

    bool IsFinish() { return m_bFinish; }


public:
    //�����Լ� ����
    virtual  void CreateAnimation(const wstring& _strName, CImage* _pImage
        , Vec2 _vLeftTop, Vec2 _vSize, Vec2 _vOffset
        , float _fStep, UINT _iFrmCount, float _fDuration, bool _bCamRelation = true);

    virtual CBody* FindAnimation(const wstring& _strKey);
    virtual void Play(const wstring& _strName, bool _bRepeat);


public:
    CLower();
    ~CLower();
};

