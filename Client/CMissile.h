#pragma once
#include "CObject.h"

class CImage;

class CMissile :
    public CObject
{
private:
    CImage* m_pImage;
    float   m_fSpeed;
    Vec2    m_vDir;

public:   
    void SetDir(Vec2 _vDir) 
    {
        m_vDir = _vDir;
        m_vDir.Normalize();
    }

    Vec2 GetDir() { return m_vDir; }

    virtual void tick() override;
    virtual void render(HDC _dc) override;


public:
    CMissile* Clone() { return new CMissile(*this); }

public:
    CMissile();
    ~CMissile();
};

