#pragma once
#include "CResource.h"




class CImage :
    public CResource
{
private:
    HBITMAP     m_hBit;
    HDC         m_hDC;

    UINT        m_iWidth;
    UINT        m_iHeight;

    void*       m_pBit;

private:
    virtual int Load(const wstring& _strFilePath) override;
    virtual int Create(UINT _iWidth, UINT _iHeight);


public:
    HDC GetDC() { return m_hDC; }
    UINT GetWidth() { return m_iWidth; }
    UINT GetHeight() { return m_iHeight; }
    void SetPixelColor(int _x, int _y, tPixel _pixel);
    tPixel GetPixelColor(int _x, int  _y);

public:
    CImage();
    ~CImage();

    friend class CResMgr;
};

