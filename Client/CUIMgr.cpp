#include "pch.h"
#include "CUIMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"

#include "CKeyMgr.h"

CUIMgr::CUIMgr()
	: m_pFocusedUI(nullptr)
	, m_pTargetUI(nullptr)
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::tick()
{
	//현재 씬이 무엇인지 가져온다.
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	//현재 씬에 접근해서 ui 오브젝트 모두 가져온다. 
	const vector<CObject*>& vecObj = pCurScene->GetObjects(LAYER_TYPE::UI);

	//반복문 돌면서 UI 에 접근
	for (int i = (int)vecObj.size() - 1; i >= 0; --i)
	{		
		//오브젝트포인터 ui 를 다운캐스팅 
		m_pTargetUI = FindTargetUI((CUI*)vecObj[i]);

		if (nullptr == m_pTargetUI)
			continue;

		if (IsTap(KEY_TYPE::LBTN))
		{
			m_pTargetUI->LBtnDown();

			// 만약 클릭된 UI의 최상위 부모 UI 로 접근
			m_pFocusedUI = m_pTargetUI->GetAncestorUI();

			// 해당 UI 를 FocusedUI 로 전환한다.
			pCurScene->SetFocusedUI(m_pFocusedUI);

			break;
		}
		else if (IsRelease(KEY_TYPE::LBTN))
		{
			if (m_pTargetUI->m_bLbtnPressed)
			{
				m_pTargetUI->LBtnClicked();
				m_pTargetUI->m_bLbtnPressed = false;			
			}			
		}
	}
}

CUI* CUIMgr::FindTargetUI(CUI* _pParentUI)
{
	CUI* pTargetUI = nullptr;

	static list<CUI*> queue;
	queue.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		CUI* pUI = queue.front();
		queue.pop_front();

		if (pUI->IsMouseOn())
		{
			if (nullptr != pTargetUI && IsRelease(KEY_TYPE::LBTN))
			{
				pTargetUI->m_bLbtnPressed = false;
			}

			pTargetUI = pUI;
		}
		else if (IsRelease(KEY_TYPE::LBTN))
		{
			pUI->m_bLbtnPressed = false;
		}



		for (size_t i = 0; i < pUI->m_vecChildUI.size(); ++i)
		{
			queue.push_back(pUI->m_vecChildUI[i]);
		}
	}

	return pTargetUI;
}
