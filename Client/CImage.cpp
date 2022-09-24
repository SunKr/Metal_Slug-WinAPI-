#include "pch.h"
#include "CImage.h"

#include "CEngine.h"



CImage::CImage()
	: m_hBit(0)
	, m_hDC(0)
	, m_iWidth(0)
	, m_iHeight(0)
	, m_pBit(nullptr)
{
}

CImage::~CImage()
{
	DeleteObject(m_hBit);
	DeleteDC(m_hDC);
}

int CImage::Load(const wstring& _strFilePath)
{
	m_hBit = (HBITMAP)LoadImageW(nullptr, _strFilePath.c_str(), IMAGE_BITMAP, 0, 0
		, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if (nullptr == m_hBit)
	{
		return E_FAIL;
	}
		
	// 비트맵 정보 확인
	BITMAP tBitInfo = {};
	GetObject(m_hBit, sizeof(BITMAP), &tBitInfo);

	m_iWidth = tBitInfo.bmWidth;
	m_iHeight = tBitInfo.bmHeight;
	//비트 관련 정보도 가져온다.
	m_pBit = tBitInfo.bmBits;

	int iErr = GetLastError();

	HDC hMainDC = CEngine::GetInst()->GetMainDC();
	m_hDC = CreateCompatibleDC(hMainDC);

	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_hDC, m_hBit);
	DeleteObject(hPrevBit);

	return S_OK;
}

int CImage::Create(UINT _iWidth, UINT _iHeight)
{
	// 새로 생성한 비트맵을 가리키는 전용 DC 생성
	// 새로 생성한 비트맵과 DC 를 서로 연결
	HDC hMainDC = CEngine::GetInst()->GetMainDC();

	m_hBit = CreateCompatibleBitmap(hMainDC, _iWidth, _iHeight);
	m_hDC = CreateCompatibleDC(hMainDC);

	if (0 == m_hBit || 0 == m_hDC)
		return E_FAIL;

	HBITMAP hDefaultBitmap = (HBITMAP)SelectObject(m_hDC, m_hBit);
	DeleteObject(hDefaultBitmap);

	// 비트맵 정보 확인
	BITMAP tBitInfo = {};
	GetObject(m_hBit, sizeof(BITMAP), &tBitInfo);

	m_iWidth = tBitInfo.bmWidth;
	m_iHeight = tBitInfo.bmHeight;

	return S_OK;
}


//픽셀 색 설정 함수
void CImage::SetPixelColor(int _x, int _y, tPixel _pixel)
{
	//메모리의 특성상 역수로 변경해야 한다. 
	_y = m_iHeight - (_y + 1);
	tPixel* pPixel = (tPixel*)m_pBit;
	pPixel += (m_iWidth * _y + _x);

	*pPixel = _pixel;
}


tPixel CImage::GetPixelColor(int _x, int _y)
{
	// 실제 비트맵 픽셀은 아랫줄 부터 시작하기 때문에,
		// 위에서부터로 계산하는 윈도우 좌표계랑 맞추어주기 위해서 행을 뒤집어서 접근한다.
	_y = m_iHeight - (_y + 1);

	tPixel* pPixel = (tPixel*)m_pBit;
	pPixel += (m_iWidth * _y + _x);
	return *pPixel;
}