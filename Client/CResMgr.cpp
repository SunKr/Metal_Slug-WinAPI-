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
	// Image �ε�	
	LoadImg(L"PlayerImage", L"image\\Fighter.bmp");
	//LoadImg(L"BackGround1", L"image\\Map.bmp");
	//LoadImg(L"BackGround2", L"image\\Map1.bmp");

	//���� �ε�
	LoadSound(L"BGM_01", L"sound\\Stage.wav");
	LoadSound(L"intro", L"sound\\Game_MetalSlug__Sounds_GM_Intro.wav");
	LoadSound(L"MissionStart", L"sound\\Game_MetalSlug__Sounds_GM_mission-start.wav");

}

CImage* CResMgr::LoadImg(const wstring& _strKey, const wstring& _strRelativePath)
{
	// Ű������ Ž��
	CImage* pImage = FindImg(_strKey);
	if (nullptr != pImage)
	{
		// �ش�Ű�� �̹� �ε��Ȱ� ������ �ش� ���ҽ��� ��ȯ
		return pImage;
	}

	// �ش� Ű�� �ε��� �̹����� ����.
	
	// content ���� ��� + ����� = ���� ���
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	pImage = new CImage;
	if (FAILED(pImage->Load(strFilePath)))
	{
		MessageBox(nullptr, L"�̹��� �ε� ����", L"����", MB_OK);
		return nullptr;
	}

	pImage->SetKey(_strKey);
	pImage->SetRelativePath(_strRelativePath);
	m_mapImage.insert(make_pair(_strKey, pImage));

	return pImage;
}

CImage* CResMgr::CreateImg(const wstring& _strKey, UINT _iWidth, UINT _iHeight)
{
	// Ű������ Ž��
	CImage* pImage = FindImg(_strKey);
	if (nullptr != pImage)
	{
		MessageBox(nullptr, L"�ߺ� Ű �߻�", L"�̹��� ���� ����", MB_OK);
		return nullptr;
	}

	// �ش� Ű�� ������ �̹����� ����.
	pImage = new CImage;
	if (FAILED(pImage->Create(_iWidth, _iHeight)))
	{
		MessageBox(nullptr, L"�̹��� ���� ����", L"����", MB_OK);
		return nullptr;
	}

	pImage->SetKey(_strKey);	
	m_mapImage.insert(make_pair(_strKey, pImage));

	return pImage;
}

CImage* CResMgr::FindImg(const wstring& _strKey)
{
	map<wstring, CImage*>::iterator iter = m_mapImage.find(_strKey);

	// �̹� ������ Ű������ �ٸ� ���ҽ��� ���� ��ϵǾ� �־���.
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
		MessageBox(nullptr, L"Sound �ε� ����!!!", L"���ҽ� �ε� ����", MB_OK);
		delete pSound;
		return nullptr;
	}

	pSound->SetKey(_strKey);
	pSound->SetRelativePath(_strRelativePath);

	// map �� ���
	m_mapSound.insert(make_pair(_strKey, pSound));

	return pSound;
}