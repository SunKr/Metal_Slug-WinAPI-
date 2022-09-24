#pragma once
#include "CObject.h"


class CImage;

class CTile :
    public CObject
{
private:
    CImage*     m_pTileAtlas;   // 타일 이미지 모음
    int         m_iImgIdx;      // 특정 타일




public:
    void SetImgIdx(int _iIdx) { m_iImgIdx = _iIdx; }
    void AddImgIdx();

public:
    virtual void tick() override;
    virtual void render(HDC _dc) override;

    virtual void Save(FILE* _pFile);
    virtual void Load(FILE* _pFile);


    CLONE(CTile);
public:
    CTile();
    ~CTile();
};

