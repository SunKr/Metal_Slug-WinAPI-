#include "pch.h"
#include "CGUI.h"
#include "CResMgr.h"

#include "CPlayer1.h"
#include "CScene.h"
#include "CSceneMgr.h"

#include "CTimeMgr.h"
class CPlayer1;


CGUI::CGUI()
	: m_pUIAtlas(nullptr)
	, pPlyaer(nullptr)
	, m_MainTime(60)
	, m_TimeAcc(0.f)
	, m_fade(0.f)
{
	m_pUIAtlas = CResMgr::GetInst()->LoadImg(L"GUI", L"Image\\MAINUI.bmp");
	m_UI = CResMgr::GetInst()->LoadImg(L"Push_Insert", L"Image\\PushStart_insert.bmp");
}



CGUI::CGUI(const CGUI& _ui)
	: CObject(_ui)
	, m_pUIAtlas(_ui.m_pUIAtlas)
	, pPlyaer(_ui.pPlyaer)
	, m_MainTime(_ui.m_MainTime)
	, m_TimeAcc(_ui.m_TimeAcc)
	, m_fade(_ui.m_fade)
{
	
}

CGUI::~CGUI()
{


}







void CGUI::tick()
{

	CObject::tick();
}

void CGUI::render(HDC _dc)
{

	//현재 렌더링 되고 있는 좌표를 카메라가 보고 있는 좌표로 가져와서 GUI가 카메라를 따라서 움직이도록한다.
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(CCamera::GetInst()->GetLookAt());

	m_fade += DT;
	if (m_fade >= 1.f)
	{
		// InsertCoin UI 깜밖이게 설정
		BLENDFUNCTION tFunc = {};
		tFunc.BlendOp = AC_SRC_OVER;
		tFunc.BlendFlags = 0;
		tFunc.AlphaFormat = AC_SRC_ALPHA;
		tFunc.SourceConstantAlpha = 0;
		AlphaBlend(_dc, (int)vPos.x  + 170
			, (int)vPos.y - 260
			, 234, 25
			, m_UI->GetDC(), 5, 17, 234, 25, tFunc);

	}

	else if(m_fade >= 0.f && m_fade <= 1.f)
	{
		// InsertCoin UI 깜밖이게 설정
		BLENDFUNCTION tFunc = {};
		tFunc.BlendOp = AC_SRC_OVER;
		tFunc.BlendFlags = 0;
		tFunc.AlphaFormat = AC_SRC_ALPHA;
		tFunc.SourceConstantAlpha = 255;
		AlphaBlend(_dc, (int)vPos.x + 170
			, (int)vPos.y - 260
			, 234, 25
			, m_UI->GetDC(), 5, 17, 234, 25, tFunc);

	}

	if (m_fade >= 2.f)
	{
		m_fade = 0.f;
	}


	//점수별로 캐릭터 처치지 돌아가도록 나중에 설정해야함****
	// Score
	TransparentBlt(_dc, (int)vPos.x - 290
		, (int)vPos.y - 285
		, 15, 22, m_pUIAtlas->GetDC(), 0, 200, 8, 8, RGB(255, 0, 255));

	//Bar UI
	TransparentBlt(_dc, (int)vPos.x -440
		, (int)vPos.y - 260
		, 180 , 32, m_pUIAtlas->GetDC(), 0, 0, 45, 8, RGB(255, 0, 255));

	//ARM BOMB UI
	TransparentBlt(_dc, (int)vPos.x - 250
		, (int)vPos.y - 290
		, 248, 68, m_pUIAtlas->GetDC(), 0, 8, 62, 17, RGB(255, 0, 255));
	
	//1UP = 
	TransparentBlt(_dc, (int)vPos.x - 425
		, (int)vPos.y - 225
		, 60, 22, m_pUIAtlas->GetDC(), 0, 26, 43, 16, RGB(255, 0, 255));

	// 2 
	TransparentBlt(_dc, (int)vPos.x - 365
		, (int)vPos.y - 225
		, 15, 22, m_pUIAtlas->GetDC(), 15, 218, 8, 16, RGB(255, 0, 255));

	// 현재 Scene 을 찾는다.
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	// Player1 Layer 를 가져온다.
	const vector<CObject*>& vecPlayer = pCurScene->GetObjects(LAYER_TYPE::PLAYER);

	SCORE _eScore = SCORE::END;
	//캐릭터 총기 탄약 소유 종류 체크
	//항상 for loop 안에서 돌려야 모든 vector 체크 가능 주의할것
	for (int i = 0; i < vecPlayer.size(); ++i)
	{
		
		//플레이어로 오브젝트 객체 다운캐스팅후에
		pPlyaer = (CPlayer1*)vecPlayer[i];
		// 플레이어 객체에서 무기 체게에 접근하여 일반 무기로 변경
		pPlyaer->setArmor(ARMOR_TYPE::MACHINE);


		// 만약 플레이어가 소유한 무기가 일반 총이라면 무한대를 표시해준다
		if (pPlyaer->getArmor() == ARMOR_TYPE::NORMAL)
		{
			//시작점(45,27) 무한대 UI
			TransparentBlt(_dc, (int)vPos.x - 200
				, (int)vPos.y - 251
				, 44, 21, m_pUIAtlas->GetDC(), 45, 27, 31, 15, RGB(255, 0, 255));
		}
		// 만약 플레이어가 MachineGun을 획득시 무한대를 숫자로 변경해준다.
		else if(pPlyaer->getArmor() == ARMOR_TYPE::MACHINE)
		{
			_eScore = CalculateNumber(pPlyaer->GetBulletCount(), DIGIT::HUNDRED_DIGIT);
			// 백 단위
			TransparentBlt(_dc, (int)vPos.x - 200
				, (int)vPos.y - 251
				, 16, 16, m_pUIAtlas->GetDC(), ((int)_eScore* 8), 218, 8, 16, RGB(255, 0, 255));
			
			_eScore = CalculateNumber(pPlyaer->GetBulletCount(), DIGIT::TEN_DIGIT);
			// 십 단위
			TransparentBlt(_dc, (int)vPos.x - 180
				, (int)vPos.y - 251
				, 16, 16, m_pUIAtlas->GetDC(), ((int)_eScore * 8), 218, 8, 16, RGB(255, 0, 255));
			_eScore = CalculateNumber(pPlyaer->GetBulletCount(), DIGIT::UNIT_DIGIT);
			// 일 단위
			TransparentBlt(_dc, (int)vPos.x - 160
				, (int)vPos.y - 251
				, 16, 16, m_pUIAtlas->GetDC(), ((int)_eScore * 8), 218, 8, 16, RGB(255, 0, 255));
		}

		//플레이어 Bomb 확인후 출력 폭탄의 개수는 최대 99개로 100개를 넘을 수 없다. 
		if (pPlyaer->GetBombCount() > 0)
		{
			_eScore = CalculateNumber(pPlyaer->GetBombCount(), DIGIT::TEN_DIGIT);
			// 십 단위
			TransparentBlt(_dc, (int)vPos.x - 90
				, (int)vPos.y - 251
				, 16, 16, m_pUIAtlas->GetDC(), ((int)_eScore * 8), 218, 8, 16, RGB(255, 0, 255));
			_eScore = CalculateNumber(pPlyaer->GetBombCount(), DIGIT::UNIT_DIGIT);
			// 일 단위
			TransparentBlt(_dc, (int)vPos.x - 70
				, (int)vPos.y - 251
				, 16, 16, m_pUIAtlas->GetDC(), ((int)_eScore * 8), 218, 8, 16, RGB(255, 0, 255));

		}
		else
		{
			_eScore = CalculateNumber(pPlyaer->GetBombCount(), DIGIT::UNIT_DIGIT);
			TransparentBlt(_dc, (int)vPos.x - 80
				, (int)vPos.y - 251
				, 16, 16, m_pUIAtlas->GetDC(), ((int)_eScore * 8), 218, 8, 16, RGB(255, 0, 255));
		}
	}



	//시간계산
	// 중앙부에 시간 표시ㅊㄹ
	if (m_MainTime > 0)
	{
		m_TimeAcc += DT; //1초 시간 제기
		if (m_TimeAcc >= 1.f) //1초를 넘으면 
		{
			--m_MainTime;
			m_TimeAcc = 0.f; //1초가 되었으면 0으로 다시 초기화 해준다. 
		}
		_eScore = CalculateNumber(m_MainTime, DIGIT::TEN_DIGIT);
		// 십 단위
		TransparentBlt(_dc, (int)vPos.x
			, (int)vPos.y - 265
			,64, 32, m_pUIAtlas->GetDC(), ((int)_eScore * 8), 218, 8, 16, RGB(255, 0, 255));

		_eScore = CalculateNumber(m_MainTime, DIGIT::UNIT_DIGIT);

		TransparentBlt(_dc, (int)vPos.x + 60
			, (int)vPos.y - 265
			, 64, 32, m_pUIAtlas->GetDC(), ((int)_eScore * 8), 218, 8, 16, RGB(255, 0, 255));


	
	}
	else
	{
		_eScore = CalculateNumber(m_MainTime, DIGIT::UNIT_DIGIT);
		TransparentBlt(_dc, (int)vPos.x + 20
			, (int)vPos.y - 265
			, 64, 32, m_pUIAtlas->GetDC(), ((int)_eScore * 8), 218, 8, 16, RGB(255, 0, 255));
	}


	CObject::render(_dc);
}



// 총알 갯수 연산 함수 
// 구할 총알의 자리수 설정
SCORE CGUI::CalculateNumber(int m_number, DIGIT _digit)
{
	// 처음에 받아 올 숫자 아머 최대치 200으로 설정
	int share = 0;
	SCORE _eNumber;


	if (DIGIT::HUNDRED_DIGIT == _digit)
	{
		// 100의 자리 숫자 몫
		_eNumber = (SCORE)(m_number / 100);
		return _eNumber;
	}
	else if (DIGIT::TEN_DIGIT == _digit)
	{
		// 10의 자리 숫자 몫
		_eNumber = (SCORE)((m_number % 100) / 10);
		return _eNumber;
	}
	else if (DIGIT::UNIT_DIGIT == _digit)
	{
		// 1의 자리 숫자 나머지 값
		_eNumber = (SCORE)((m_number % 10));
		return _eNumber;
	}
}

