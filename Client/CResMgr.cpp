#include "pch.h"
#include "CResMgr.h"

#include "CPathMgr.h"

#include "CResource.h"
#include "CImage.h"
#include "CSound.h"
#include "CResMgr.h"

CResMgr::CResMgr()
{

}

CResMgr::~CResMgr()
{
	Safe_Del_Map(m_mapImage);
}

void CResMgr::init()
{
	// Image 로딩	
	LoadImg(L"PlayerImage", L"image\\Fighter.bmp");
	//LoadImg(L"BackGround1", L"image\\Map.bmp");
	//LoadImg(L"BackGround2", L"image\\Map1.bmp");

	//사운드 로딩
	LoadSound(L"BGM_01", L"sound\\Stage.wav");
	LoadSound(L"intro", L"sound\\Game_MetalSlug__Sounds_GM_Intro.wav");
	LoadSound(L"MissionStart", L"sound\\Game_MetalSlug__Sounds_GM_mission-start.wav");

}

CImage* CResMgr::LoadImg(const wstring& _strKey, const wstring& _strRelativePath)
{
	// 키값으로 탐색
	CImage* pImage = FindImg(_strKey);
	if (nullptr != pImage)
	{
		// 해당키로 이미 로딩된게 있으면 해당 리소스를 반환
		return pImage;
	}

	// 해당 키로 로딩된 이미지가 없다.
	
	// content 폴더 경로 + 상대경로 = 최종 경로
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	pImage = new CImage;
	if (FAILED(pImage->Load(strFilePath)))
	{
		MessageBox(nullptr, L"이미지 로딩 실패", L"에러", MB_OK);
		return nullptr;
	}

	pImage->SetKey(_strKey);
	pImage->SetRelativePath(_strRelativePath);
	m_mapImage.insert(make_pair(_strKey, pImage));

	return pImage;
}

CImage* CResMgr::CreateImg(const wstring& _strKey, UINT _iWidth, UINT _iHeight)
{
	// 키값으로 탐색
	CImage* pImage = FindImg(_strKey);
	if (nullptr != pImage)
	{
		MessageBox(nullptr, L"중복 키 발생", L"이미지 생성 실패", MB_OK);
		return nullptr;
	}

	// 해당 키로 생성된 이미지가 없다.
	pImage = new CImage;
	if (FAILED(pImage->Create(_iWidth, _iHeight)))
	{
		MessageBox(nullptr, L"이미지 생성 실패", L"에러", MB_OK);
		return nullptr;
	}

	pImage->SetKey(_strKey);	
	m_mapImage.insert(make_pair(_strKey, pImage));

	return pImage;
}

CImage* CResMgr::FindImg(const wstring& _strKey)
{
	map<wstring, CImage*>::iterator iter = m_mapImage.find(_strKey);

	// 이미 동일한 키값으로 다른 리소스가 먼저 등록되어 있었다.
	if (iter != m_mapImage.end())
	{
		return iter->second;
	}

	return nullptr;
}


CSound* CResMgr::FindSound(const wstring& _strKey)
{
	map<wstring, CSound*>::iterator iter = m_mapSound.find(_strKey);

	if (iter == m_mapSound.end())
		return nullptr;

	return (CSound*)iter->second;
}

CSound* CResMgr::LoadSound(const wstring& _strKey, const wstring& _strRelativePath)
{
	CSound* pSound = FindSound(_strKey);

	if (nullptr != pSound)
		return pSound;

	pSound = new CSound;

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;
	HRESULT hr = pSound->Load(strFilePath.c_str());

	if (FAILED(hr))
	{
		MessageBox(nullptr, L"Sound 로딩 실패!!!", L"리소스 로딩 실패", MB_OK);
		delete pSound;
		return nullptr;
	}

	pSound->SetKey(_strKey);
	pSound->SetRelativePath(_strRelativePath);

	// map 에 등록
	m_mapSound.insert(make_pair(_strKey, pSound));

	return pSound;
}