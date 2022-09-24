#include "pch.h"
#include "CScene_Home.h"
#include "CBackground.h"
#include "CResMgr.h"
#include "CImage.h"
#include "CObject.h"
#include "CCamera.h"

#include "CKeyMgr.h"

#include "CSound.h"
#include "CSoundMgr.h"

CScene_Home::CScene_Home()
	:m_vHomePos(Vec2(0.f, 0.f))
	,Home(nullptr)
	,pBGM(nullptr)
{


	//홈화면 출력
	 Home = CResMgr::GetInst()->LoadImg(L"Home", L"image\\titleScene.bmp");

	 //pBGM = CResMgr::GetInst()->LoadSound(L"intro", L"sound\\Game_MetalSlug__Sounds_GM_Intro.wav");
}


CScene_Home::~CScene_Home()
{

}





//장면으로 들어 왔을때
void CScene_Home::enter()
{
	

}


//이장면에서 나갔을때
void CScene_Home::exit()
{



}


void CScene_Home::tick()
{


	//엔터를 누르면 장면이 전환되도록 설정한다. 
	if (IsTap(KEY_TYPE::ENTER))
	{
		SceneChange(SCENE_TYPE::SELECT);
	}
}


void CScene_Home::render(HDC _dc)
{
	//카메라 위치를 가져온다. 
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(m_vHomePos);
	

	//스트레치 블릿을 통해서 1000 X 600 만큼의 이미지 크기로 출력하도로고 설정해준다.
	TransparentBlt(_dc, (int)vPos.x, (int)vPos.y, 900,600,
		Home->GetDC(), 0, 0, Home->GetWidth(), Home->GetHeight(), SRCCOPY);




}
