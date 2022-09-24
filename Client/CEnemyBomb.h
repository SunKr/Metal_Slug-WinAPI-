#pragma once
#include "CObject.h"
class CEnemyBomb :
    public CObject
{

private:
    CImage* RBomb;   //����ź Animation ���鶧 ����� �̹���
    CImage* LBomb;   //����ź Animation ���鶧 ����� �̹���
    CImage* Effect;
    int     GranadeCount;   //���� ����ź ����
    float   m_fSpeed;       //����ź ���ư��� �ӵ�
    Vec2    m_vDir;         // ����ź ����
    int     m_BoundCount;
public:


    int GetGranadeCount() { return GranadeCount; }
    void SetDir(Vec2 _vDir)
    {
        m_vDir = _vDir;
        m_vDir.Normalize();
    }

    Vec2 GetDir() { return m_vDir; }

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

public:
    CEnemyBomb* Clone() { return new CEnemyBomb(*this); }

public:
    CEnemyBomb();
    virtual ~CEnemyBomb();


};

