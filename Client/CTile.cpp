#include "pch.h"
#include "CTile.h"

#include "CResMgr.h"
#include "CImage.h"

#include "CKeyMgr.h"
#include "CCamera.h"

CTile::CTile()
	: m_pTileAtlas(nullptr)
	, m_iImgIdx(0)
{
	m_pTileAtlas = CResMgr::GetInst()->LoadImg(L"TileAtlas", L"Image\\TILE.bmp");
}

CTile::~CTile()
{
}

void CTile::AddImgIdx()
{
	++m_iImgIdx;

	int iMaxCol = m_pTileAtlas->GetWidth() / TILE_SIZE;
	int iMaxRow = m_pTileAtlas->GetHeight() / TILE_SIZE;

	if (iMaxCol * iMaxRow <= m_iImgIdx)
	{
		m_iImgIdx = 0;
	}
}

void CTile::tick()
{
	if (IsTap(KEY_TYPE::RIGHT))
	{
		AddImgIdx();
	}
}

void CTile::render(HDC _dc)
{
	if (nullptr == m_pTileAtlas || m_iImgIdx == -1)
		return;

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());

	int iMaxCol = m_pTileAtlas->GetWidth() / TILE_SIZE;
	int iMaxRow = m_pTileAtlas->GetHeight() / TILE_SIZE;

	int iRow = m_iImgIdx / iMaxCol;
	int iCol = m_iImgIdx % iMaxCol;

	if (iMaxRow <= iRow)
	{
		return;
	}

	TransparentBlt(_dc
		, (int)vRenderPos.x, (int)vRenderPos.y
		, TILE_SIZE, TILE_SIZE
		, m_pTileAtlas->GetDC()
		, TILE_SIZE * iCol, TILE_SIZE * iRow
		, TILE_SIZE, TILE_SIZE
		, RGB(255, 0, 255));
}

void CTile::Save(FILE* _pFile)
{
	SaveImageRef(m_pTileAtlas, _pFile);

	fwrite(&m_iImgIdx, sizeof(int), 1, _pFile);
}

void CTile::Load(FILE* _pFile)
{
	LoadImageRef(&m_pTileAtlas, _pFile);

	fread(&m_iImgIdx, sizeof(int), 1, _pFile);
}