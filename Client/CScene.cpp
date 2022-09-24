#include "pch.h"
#include "CScene.h"

#include "CEngine.h"
#include "CCamera.h"

#include "CObject.h"
#include "CTile.h"

#include "CResMgr.h"
#include "CBackground.h"
#include "CAnimator.h"

CScene::CScene()
	: m_iTileCol(0)
	, m_iTileRow(0)
{
}

CScene::~CScene()
{
	DeleteAllObject();	
}


void CScene::CreateTile(UINT _iCol, UINT _iRow)
{
	DeleteObject(LAYER_TYPE::TILE);

	m_iTileCol = _iCol;
	m_iTileRow = _iRow;

	for (UINT iRow = 0; iRow < _iRow; ++iRow)
	{
		for (UINT iCol = 0; iCol < _iCol; ++iCol)
		{
			CTile* pTile = new CTile;
			pTile->SetPos(Vec2( (float)(iCol * TILE_SIZE), (float)(iRow * TILE_SIZE)));
			AddObject(pTile, LAYER_TYPE::TILE);
		}
	}
}

void CScene::SetFocusedUI(CObject* _pUI)
{
	// Focused ó�� �Ϸ��� UI �� UI ���̾� ���;ȿ��� ã�Ƽ� �����
	vector<CObject*>::iterator iter = m_arrLayer[(UINT)LAYER_TYPE::UI].begin();
	for (; iter != m_arrLayer[(UINT)LAYER_TYPE::UI].end(); ++iter)
	{
		if (*iter == _pUI)
		{
			m_arrLayer[(UINT)LAYER_TYPE::UI].erase(iter);
			break;
		}
	}	

	// �ٽ� �� �ڷ� �ִ´�.
	m_arrLayer[(UINT)LAYER_TYPE::UI].push_back(_pUI);
}

void CScene::tick()
{	
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		for (UINT j = 0; j < m_arrLayer[i].size(); ++j)
		{
			m_arrLayer[i][j]->tick();
		}
	}
}

void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		if (i == (UINT)LAYER_TYPE::TILE)
			render_tile(_dc);
	
		else
		{
			vector<CObject*>::iterator iter = m_arrLayer[i].begin();
			for (; iter != m_arrLayer[i].end(); )
			{
				if ((*iter)->IsDead())
				{
					iter = m_arrLayer[i].erase(iter);
				}
				else
				{
					(*iter)->render(_dc);
					++iter;
				}
			}
		}
	}
}

void CScene::DeleteAllObject()
{
	for (UINT i = 0; i < (UINT)LAYER_TYPE::END; ++i)
	{
		DeleteObject((LAYER_TYPE)i);
	}
}

void CScene::DeleteObject(LAYER_TYPE _eType)
{	
	vector<CObject*>& vecObj = m_arrLayer[(UINT)_eType];

	for (UINT j = 0; j < vecObj.size(); ++j)
	{
		SAFE_DELETE(vecObj[j]);
	}	

	vecObj.clear();
}

void CScene::render_tile(HDC _dc)
{
	Vec2 vResolution = CEngine::GetInst()->GetResolution();
	Vec2 vCamLT = CCamera::GetInst()->GetLookAt() - (vResolution / 2.f);

	// ȭ��ȿ� ������ �ִ� Ÿ�� ����
	int iMaxCol = (int)(vResolution.x / (float)TILE_SIZE) + 1;
	int iMaxRow = (int)(vResolution.y / (float)TILE_SIZE) + 1;

	// ī�޶� �»�� ��ġ�� ���� �� ������ ���
	int iLTCol = (int)(vCamLT.x / (float)TILE_SIZE);
	int iLTRow = (int)(vCamLT.y / (float)TILE_SIZE);	

	vector<CObject*>& vecTile = m_arrLayer[(UINT)LAYER_TYPE::TILE];

	for (int j = 0; j < iMaxRow; ++j)
	{
		for (int i = 0; i < iMaxCol; ++i)
		{
			int iRow = iLTRow + j;
			int iCol = iLTCol + i;

			if (iRow < 0 || (int)GetTileRow() <= iRow
				|| iCol < 0 || (int)GetTileCol() <= iCol)
			{
				continue;
			}

			int iTileIdx = iRow * GetTileCol() + iCol;
			vecTile[iTileIdx]->render(_dc);
		}
	}	
}



