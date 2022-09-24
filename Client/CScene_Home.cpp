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


	//Ȩȭ�� ���
	 Home = CResMgr::GetInst()->LoadImg(L"Home", L"image\\titleScene.bmp");

	 //pBGM = CResMgr::GetInst()->LoadSound(L"intro", L"sound\\Game_MetalSlug__Sounds_GM_Intro.wav");
}


CScene_Home::~CScene_Home()
{

}





//������� ��� ������
void CScene_Home::enter()
{
	

}


//����鿡�� ��������
void CScene_Home::exit()
{



}


void CScene_Home::tick()
{


	//���͸� ������ ����� ��ȯ�ǵ��� �����Ѵ�. 
	if (IsTap(KEY_TYPE::ENTER))
	{
		SceneChange(SCENE_TYPE::SELECT);
	}
}


void CScene_Home::render(HDC _dc)
{
	//ī�޶� ��ġ�� �����´�. 
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(m_vHomePos);
	

	//��Ʈ��ġ ���� ���ؼ� 1000 X 600 ��ŭ�� �̹��� ũ��� ����ϵ��ΰ� �������ش�.
	TransparentBlt(_dc, (int)vPos.x, (int)vPos.y, 900,600,
		Home->GetDC(), 0, 0, Home->GetWidth(), Home->GetHeight(), SRCCOPY);




}
