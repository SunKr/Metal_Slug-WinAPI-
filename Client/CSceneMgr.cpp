#include "pch.h"
#include "CSceneMgr.h"

#include "CScene_Tool.h"
#include "Game_Scene.h"
//홈화면
#include "CScene_Home.h"
//캐릭터 선택창
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
	// 게임 장면
	m_arrScene[LOGO] = new Game_Scene;
	//홈화면 동적할당 위에 소멸자에서 나올때 홈화면 지운다. 
	m_arrScene[HOME] = new CScene_Home;
	//캐릭터 선택화면
	m_arrScene[SELECT] = new CScene_Select;
	
	ChangeScene(SCENE_TYPE::LOGO);
}

void CSceneMgr::tick()
{
	m_pCurScene->tick();
}

// 현재 장면에 있을때 렌더링하는 함수
void CSceneMgr::render(HDC _dc)
{
	m_pCurScene->render(_dc);
}


//화면 전환 할때 사용하는 함수
void CSceneMgr::ChangeScene(SCENE_TYPE _eNext)
{
	if (nullptr != m_pCurScene)
	{
		m_pCurScene->exit();
	}

	m_pCurScene = m_arrScene[_eNext];

	m_pCurScene->enter();
}