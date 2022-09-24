#include "pch.h"
#include "CScene_Select.h"

#include "CCamera.h"
#include "CResMgr.h"
#include "CKeyMgr.h"
#include "CImage.h"

#include "CSound.h"
#include "CSoundMgr.h"


CScene_Select::CScene_Select()
	:m_vSelectPos{}
	, Select(nullptr)
	, Character(nullptr)
	, m_bMouseOn(false)
	, e_Player{}
{

	//생성자에서 카메라 위치및 파일을 로딩해준다. 

	//카메라 위치를 가져온다. 
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(m_vSelectPos);
	//셀렉트 관련 사진 가져온다.
	Character = CResMgr::GetInst()->LoadImg(L"Select", L"image\\charactersSelect.bmp");
	Select = CResMgr::GetInst()->LoadImg(L"SelectScene", L"image\\selectScene.bmp");

}

CScene_Select::~CScene_Select()
{

}





void CScene_Select::tick()
{
	//카메라 위치를 가져온다. 
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(m_vSelectPos);
	//마우스 온 체크
	Vec2 vmPos = CKeyMgr::GetInst()->GetMousePos();

	//범위 내에 있는지? 체크
	// if (범위안에 들어온다면)
	//MARCO
	if (vPos.x + 44 <= vmPos.x && vmPos.x <= vPos.x + 245
		&& vPos.y + 188 <= vmPos.y && vmPos.y <= vPos.y + 515)
	{
		m_bMouseOn = true;
		e_Player = C_PLAYER::MARCO;
	}
	//Eri
	else if (vPos.x + 248 <= vmPos.x && vmPos.x <= vPos.x + 449
		&& vPos.y + 188 <= vmPos.y && vmPos.y <= vPos.y + 515)
	{
		m_bMouseOn = true; 
		e_Player = C_PLAYER::ERI;
	}
	else if (vPos.x + 452 <= vmPos.x && vmPos.x <= vPos.x + 653
		&& vPos.y + 188 <= vmPos.y && vmPos.y <= vPos.y + 515)
	{
		m_bMouseOn = true;
		e_Player = C_PLAYER::TARMA;
	}
	else if (vPos.x + 656 <= vmPos.x && vmPos.x <= vPos.x + 857
		&& vPos.y + 188 <= vmPos.y && vmPos.y <= vPos.y + 515)
	{
		m_bMouseOn = true;
		e_Player = C_PLAYER::FIO;
	}
	else
	{
		m_bMouseOn = false;
		e_Player = C_PLAYER::END;
	}

	//마우스로 캐릭터 선택시 
	//Marco만 선택가능하도록 설정
	if (IsPressed(KEY_TYPE::LBTN) && m_bMouseOn && (e_Player == C_PLAYER::MARCO))
	{
		SceneChange(SCENE_TYPE::LOGO);
	}

}

void CScene_Select::enter()
{
	//처음에 캐릭터 선택창에 진입하면 선택창 렌더링하도록 설계
	Select = CResMgr::GetInst()->FindImg(L"SelectScene");


	Character = CResMgr::GetInst()->FindImg(L"Select");

	//Sound Test
	CSound* pBGM1 = CResMgr::GetInst()->FindSound(L"intro");
	if (nullptr != pBGM1)
	{
		//pBGM->Play(true);		
		pBGM1->PlayToBGM();
		pBGM1->SetPosition(0.f);
	}


}

void CScene_Select::exit()
{



}



void CScene_Select::render(HDC _dc)
{
	//카메라 위치를 가져온다. 
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(m_vSelectPos);

	TransparentBlt(_dc, (int)vPos.x
		, (int)vPos.y
		, 900, 600,
		Select->GetDC(), 0, 0, Select->GetWidth(),
		Select->GetHeight(), RGB(255, 0, 255));


	if (m_bMouseOn == true && e_Player == C_PLAYER::MARCO)
	{
		switchCharacter(Character, C_PLAYER::MARCO, _dc, vPos);
	}
	else if (m_bMouseOn == true && e_Player == C_PLAYER::ERI)
	{
		switchCharacter(Character, C_PLAYER::ERI, _dc, vPos);
	}
	else if (m_bMouseOn == true && e_Player == C_PLAYER::TARMA)
	{
		switchCharacter(Character, C_PLAYER::TARMA, _dc, vPos);
	}
	else if (m_bMouseOn == true && e_Player == C_PLAYER::FIO)
	{
		switchCharacter(Character, C_PLAYER::FIO, _dc, vPos);
	}
	else
	{
		switchCharacter(Character, C_PLAYER::END, _dc, vPos);
	}
	

	
}



void CScene_Select::switchCharacter(CImage* Character, C_PLAYER _character, HDC _dc, Vec2 _vPos)
{

	switch (_character)
	{
		case C_PLAYER::MARCO:
		{
			//Marco On
			TransparentBlt(_dc, (int)_vPos.x + 44, (int)_vPos.y + 189, 201, 326,
				Character->GetDC()
				, 0, 20, 64, 120, RGB(255, 0, 255));
			//Eri Off
			TransparentBlt(_dc, (int)_vPos.x + 248, (int)_vPos.y + 189, 201, 326,
				Character->GetDC()
				, 64, 260, 64, 120, RGB(255, 0, 255));
			//Tarma Off
			TransparentBlt(_dc, (int)_vPos.x + 452, (int)_vPos.y + 189, 201, 326,
				Character->GetDC()
				, 128, 260, 64, 120, RGB(255, 0, 255));
			//Fio Off
			TransparentBlt(_dc, (int)_vPos.x + 656, (int)_vPos.y + 189, 201, 326,
				Character->GetDC()
				, 192, 260, 64, 120, RGB(255, 0, 255));
			//P1 On
			TransparentBlt(_dc, (int)_vPos.x + 99, (int)_vPos.y + 125, 98, 54,
				Character->GetDC()
				, 0, 0, 26, 19, RGB(255, 0, 255));

			break;
		}
		case C_PLAYER::ERI:
		{
			//Marco Off
			TransparentBlt(_dc, (int)_vPos.x + 44, (int)_vPos.y + 189, 201, 326,
				Character->GetDC()
				, 0, 260, 64, 120, RGB(255, 0, 255));
			//Eri
			TransparentBlt(_dc, (int)_vPos.x + 248, (int)_vPos.y + 189, 201, 326,
				Character->GetDC()
				, 64, 20, 64, 120, RGB(255, 0, 255));
			//Tarma Off
			TransparentBlt(_dc, (int)_vPos.x + 452, (int)_vPos.y + 189, 201, 326,
				Character->GetDC()
				, 128, 260, 64, 120, RGB(255, 0, 255));
			//Fio Off
			TransparentBlt(_dc, (int)_vPos.x + 656, (int)_vPos.y + 189, 201, 326,
				Character->GetDC()
				, 192, 260, 64, 120, RGB(255, 0, 255));
			//P1 On
			TransparentBlt(_dc, (int)_vPos.x + 300, (int)_vPos.y + 125, 98, 54,
				Character->GetDC()
				, 0, 0, 26, 19, RGB(255, 0, 255));

			break;
		}
		case C_PLAYER::TARMA:
		{
			//Marco Off
			TransparentBlt(_dc, (int)_vPos.x + 44, (int)_vPos.y + 189, 201, 326,
				Character->GetDC()
				, 0, 260, 64, 120, RGB(255, 0, 255));
			//Eri Off
			TransparentBlt(_dc, (int)_vPos.x + 248, (int)_vPos.y + 189, 201, 326,
				Character->GetDC()
				, 64, 260, 64, 120, RGB(255, 0, 255));
			//Tarma On
			TransparentBlt(_dc, (int)_vPos.x + 452, (int)_vPos.y + 189, 201, 326,
				Character->GetDC()
				, 128, 20, 64, 120, RGB(255, 0, 255));
			//Fio Off
			TransparentBlt(_dc, (int)_vPos.x + 656, (int)_vPos.y + 189, 201, 326,
				Character->GetDC()
				, 192, 260, 64, 120, RGB(255, 0, 255));
			//P1 On
			TransparentBlt(_dc, (int)_vPos.x + 501, (int)_vPos.y + 125, 98, 54,
				Character->GetDC()
				, 0, 0, 26, 19, RGB(255, 0, 255));
			break;
		}
		case C_PLAYER::FIO:
		{
			//Marco Off
			TransparentBlt(_dc, (int)_vPos.x + 44, (int)_vPos.y + 189, 201, 326,
				Character->GetDC()
				, 0, 260, 64, 120, RGB(255, 0, 255));
			//Eri Off
			TransparentBlt(_dc, (int)_vPos.x + 248, (int)_vPos.y + 189, 201, 326,
				Character->GetDC()
				, 64, 260, 64, 120, RGB(255, 0, 255));
			//Tarma Off
			TransparentBlt(_dc, (int)_vPos.x + 452, (int)_vPos.y + 189, 201, 326,
				Character->GetDC()
				, 128, 260, 64, 120, RGB(255, 0, 255));
			//Fio On
			TransparentBlt(_dc, (int)_vPos.x + 656, (int)_vPos.y + 189, 201, 326,
				Character->GetDC()
				, 192, 20, 64, 120, RGB(255, 0, 255));
			//P1 On
			TransparentBlt(_dc, (int)_vPos.x + 709, (int)_vPos.y + 125, 98, 54,
				Character->GetDC()
				, 0, 0, 26, 19, RGB(255, 0, 255));
			break;
		}
		default:
		{
			// Marco
			TransparentBlt(_dc, (int)_vPos.x + 44, (int)_vPos.y + 189, 201, 326,
				Character->GetDC()
				, 0, 260, 64, 120, RGB(255, 0, 255));
			//Eri
			TransparentBlt(_dc, (int)_vPos.x + 248, (int)_vPos.y + 189, 201, 326,
				Character->GetDC()
				, 64, 260, 64, 120, RGB(255, 0, 255));
			//Tarma
			TransparentBlt(_dc, (int)_vPos.x + 452, (int)_vPos.y + 189, 201, 326,
				Character->GetDC()
				, 128, 260, 64, 120, RGB(255, 0, 255));
			//Fio
			TransparentBlt(_dc, (int)_vPos.x + 656, (int)_vPos.y + 189, 201, 326,
				Character->GetDC()
				, 192, 260, 64, 120, RGB(255, 0, 255));
			break;
		}
	}
}

