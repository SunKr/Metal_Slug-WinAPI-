#include "pch.h"
#include "CSceneMgr.h"

#include "CScene_Tool.h"
#include "Game_Scene.h"
//Ȩȭ��
#include "CScene_Home.h"
//ĳ���� ����â
#include "CScene_Select.h"

CSceneMgr::CSceneMgr()
	: m_arrScene{}
	, m_pCurScene(nullptr)
{	
}

CSceneMgr::~CSceneMgr()
{
	for (int i = 0; i < SCENE_TYPE::END; ++i)
	{
		if(nullptr != m_arrScene[i])
			delete m_arrScene[i];
	}
}

void CSceneMgr::init()
{
	m_arrScene[TOOL] = new CScene_Tool;
	// ���� ���
	m_arrScene[LOGO] = new Game_Scene;
	//Ȩȭ�� �����Ҵ� ���� �Ҹ��ڿ��� ���ö� Ȩȭ�� �����. 
	m_arrScene[HOME] = new CScene_Home;
	//ĳ���� ����ȭ��
	m_arrScene[SELECT] = new CScene_Select;
	
	ChangeScene(SCENE_TYPE::LOGO);
}

void CSceneMgr::tick()
{
	m_pCurScene->tick();
}

// ���� ��鿡 ������ �������ϴ� �Լ�
void CSceneMgr::render(HDC _dc)
{
	m_pCurScene->render(_dc);
}


//ȭ�� ��ȯ �Ҷ� ����ϴ� �Լ�
void CSceneMgr::ChangeScene(SCENE_TYPE _eNext)
{
	if (nullptr != m_pCurScene)
	{
		m_pCurScene->exit();
	}

	m_pCurScene = m_arrScene[_eNext];

	m_pCurScene->enter();
}