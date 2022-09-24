#include "pch.h"
#include "CScene_Tool.h"

#include "CEngine.h"

#include "CKeyMgr.h"
#include "CCollisionMgr.h"
#include "CSceneMgr.h"
#include "CCamera.h"

#include "CTile.h"
#include "resource.h"

#include "CUIMgr.h"
#include "CPanelUI.h"
#include "CButton.h"

CScene_Tool::CScene_Tool()
    : m_eMode(TOOL_MODE::TILE)
{
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::enter()
{
	// 메뉴바를 메인 윈도우에 부착
	CEngine::GetInst()->AttachMenu();	

	CreateTile(10, 10);

    // UI 생성
    //CreateUI();
}

void CScene_Tool::exit()
{
	DeleteAllObject();
	CCollisionMgr::GetInst()->clear();

	// 메뉴바를 제거
	CEngine::GetInst()->DetachMenu();

    // UIMgr 클리어
    CUIMgr::GetInst()->clear();
}


void CScene_Tool::tick()
{
	CScene::tick();
	
    if (IsTap(KEY_TYPE::NUM_0))
        m_eMode = TOOL_MODE::NONE;
    if (IsTap(KEY_TYPE::NUM_1))
        m_eMode = TOOL_MODE::TILE;
    if (IsTap(KEY_TYPE::NUM_2))
        m_eMode = TOOL_MODE::OBJECT;
    if (IsTap(KEY_TYPE::NUM_2))
        m_eMode = TOOL_MODE::ANIMATION;
    

    switch (m_eMode)
    {
    case TOOL_MODE::TILE:
        TileMode();
        break;
    case TOOL_MODE::OBJECT:

        break;
    case TOOL_MODE::ANIMATION:

        break;    
    }

	/*if (IsTap(KEY_TYPE::ENTER))
	{
		SceneChange(SCENE_TYPE::LOGO);
	}*/
}


void CScene_Tool::TileMode()
{
    // 마우스 클릭 시 해당 타일의 이미지 인덱스를 증가시킨다.
    if (IsTap(KEY_TYPE::LBTN))
    {
        Vec2 vMousePos = CCamera::GetInst()->GetRealPos(CKeyMgr::GetInst()->GetMousePos());

        int iCol = (int)(vMousePos.x / 64.f);
        int iRow = (int)(vMousePos.y / 64.f);
        int iIdx = iRow * GetTileCol() + iCol;

        if (GetTileCol() <= (UINT)iCol || GetTileRow() <= (UINT)iRow
            || vMousePos.x < 0.f || vMousePos.y < 0.f)
        {
            return;
        }

        const vector<CObject*>& vecObj = GetObjects(LAYER_TYPE::TILE);
        ((CTile*)vecObj[iIdx])->AddImgIdx();
    }
}

void TileSaveFunc();
void TileLoadFunc();

void CScene_Tool::CreateUI()
{   

    Vec2 vResolution = CEngine::GetInst()->GetResolution();

    // PanelUI
    CPanelUI* pPanel = new CPanelUI;
    pPanel->SetScale(Vec2(400.f, 500.f));
    pPanel->SetPos(Vec2(vResolution.x - pPanel->GetScale().x, 0.f));

    // ButtonUI
    CButton* pButton = new CButton;
    pButton->SetScale(Vec2(100.f, 50.f));    
    pButton->SetPos(Vec2(50.f, 50.f));
    //pButton->SetCallBack(&TileSaveFunc);
    pButton->SetDeletage(this, (DELEGATE_FUNC) &CScene_Tool::TileSave);
    pPanel->AddChildUI(pButton);

    pButton = new CButton;
    pButton->SetScale(Vec2(100.f, 50.f));
    pButton->SetPos(Vec2(pPanel->GetScale().x - 50.f - pButton->GetScale().x, 50.f));
    //pButton->SetCallBack(&TileLoadFunc);
    pButton->SetDeletage(this, (DELEGATE_FUNC)&CScene_Tool::TileLoad);
    pPanel->AddChildUI(pButton);

    AddObject(pPanel, LAYER_TYPE::UI);


    CPanelUI* pClonePanel = pPanel->Clone();
    pClonePanel->SetPos(Vec2(pPanel->GetPos().x - 400.f, pPanel->GetPos().y));
    AddObject(pClonePanel, LAYER_TYPE::UI);
}

void CScene_Tool::TileSave()
{
    // open a file name
    OPENFILENAME ofn = {};

    wchar_t szFilePath[256] = {};

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFilePath;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 256;
    ofn.lpstrFilter = L"Tile\0*.tile\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
        
    if (false == GetSaveFileName(&ofn))
        return;

    // 파일 입출력
    FILE* pFile = nullptr;

    // 쓰기 모드로 열기
    _wfopen_s(&pFile, szFilePath, L"wb");

    if (nullptr == pFile)
        return;

    // 타일 가로 세로 개수
    UINT iCol = GetTileCol();
    UINT iRow = GetTileRow();

    fwrite(&iCol, sizeof(UINT), 1, pFile);
    fwrite(&iRow, sizeof(UINT), 1, pFile);
        
    const vector<CObject*>& vecTile = GetObjects(LAYER_TYPE::TILE);
    for (size_t i = 0; i < vecTile.size(); ++i)
    {
        CTile* pTile = (CTile*)vecTile[i];
        pTile->Save(pFile);
    }

    fclose(pFile);
}

void CScene_Tool::TileLoad()
{
    OPENFILENAME ofn = {};

    wchar_t szFilePath[256] = {};

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFilePath;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 256;
    ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (false == GetOpenFileName(&ofn))
        return;

    // 파일 입출력
    FILE* pFile = nullptr;

    // 쓰기 모드로 열기
    _wfopen_s(&pFile, szFilePath, L"rb");

    if (nullptr == pFile)
        return;

    // 타일 가로 세로 개수
    UINT iCol = 0;
    UINT iRow = 0;

    fread(&iCol, sizeof(UINT), 1, pFile);
    fread(&iRow, sizeof(UINT), 1, pFile);

    CreateTile(iCol, iRow);
    
    const vector<CObject*>& vecTile = GetObjects(LAYER_TYPE::TILE);
    for (size_t i = 0; i < vecTile.size(); ++i)
    {
        CTile* pTile = (CTile*)vecTile[i];
        pTile->Load(pFile);
    }

    fclose(pFile);
}











// ======================
// Tile Count Dialog Proc
// ======================
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:

        switch (wParam)
        {
        case IDOK:
            if (LOWORD(wParam) == IDOK)
            {
                // Edit Control 에 입력한 수치를 알아낸다.
                UINT iCol = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
                UINT iRow = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

                CScene* pScene = CSceneMgr::GetInst()->GetCurScene();
                if (nullptr == dynamic_cast<CScene_Tool*>(pScene))
                {
                    MessageBox(nullptr, L"에러", L"에러", MB_OK);
                }

                pScene->CreateTile(iCol, iRow);
            }
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;

        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
            break;
        }      

        break;
    }
    return (INT_PTR)FALSE;
}



// ================
// Button CallBack
// ================
void TileSaveFunc()
{
    // TileSave
    CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(CSceneMgr::GetInst()->GetCurScene());
    if (nullptr != pToolScene)
        pToolScene->TileSave();
}

void TileLoadFunc()
{
    CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(CSceneMgr::GetInst()->GetCurScene());
    if (nullptr != pToolScene)
        pToolScene->TileLoad();
}