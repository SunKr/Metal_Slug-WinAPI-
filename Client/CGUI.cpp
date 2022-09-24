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

	//���� ������ �ǰ� �ִ� ��ǥ�� ī�޶� ���� �ִ� ��ǥ�� �����ͼ� GUI�� ī�޶� ���� �����̵����Ѵ�.
	Vec2 vPos = CCamera::GetInst()->GetRenderPos(CCamera::GetInst()->GetLookAt());

	m_fade += DT;
	if (m_fade >= 1.f)
	{
		// InsertCoin UI �����̰� ����
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
		// InsertCoin UI �����̰� ����
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


	//�������� ĳ���� óġ�� ���ư����� ���߿� �����ؾ���****
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

	// ���� Scene �� ã�´�.
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	// Player1 Layer �� �����´�.
	const vector<CObject*>& vecPlayer = pCurScene->GetObjects(LAYER_TYPE::PLAYER);

	SCORE _eScore = SCORE::END;
	//ĳ���� �ѱ� ź�� ���� ���� üũ
	//�׻� for loop �ȿ��� ������ ��� vector üũ ���� �����Ұ�
	for (int i = 0; i < vecPlayer.size(); ++i)
	{
		
		//�÷��̾�� ������Ʈ ��ü �ٿ�ĳ�����Ŀ�
		pPlyaer = (CPlayer1*)vecPlayer[i];
		// �÷��̾� ��ü���� ���� ü�Կ� �����Ͽ� �Ϲ� ����� ����
		pPlyaer->setArmor(ARMOR_TYPE::MACHINE);


		// ���� �÷��̾ ������ ���Ⱑ �Ϲ� ���̶�� ���Ѵ븦 ǥ�����ش�
		if (pPlyaer->getArmor() == ARMOR_TYPE::NORMAL)
		{
			//������(45,27) ���Ѵ� UI
			TransparentBlt(_dc, (int)vPos.x - 200
				, (int)vPos.y - 251
				, 44, 21, m_pUIAtlas->GetDC(), 45, 27, 31, 15, RGB(255, 0, 255));
		}
		// ���� �÷��̾ MachineGun�� ȹ��� ���Ѵ븦 ���ڷ� �������ش�.
		else if(pPlyaer->getArmor() == ARMOR_TYPE::MACHINE)
		{
			_eScore = CalculateNumber(pPlyaer->GetBulletCount(), DIGIT::HUNDRED_DIGIT);
			// �� ����
			TransparentBlt(_dc, (int)vPos.x - 200
				, (int)vPos.y - 251
				, 16, 16, m_pUIAtlas->GetDC(), ((int)_eScore* 8), 218, 8, 16, RGB(255, 0, 255));
			
			_eScore = CalculateNumber(pPlyaer->GetBulletCount(), DIGIT::TEN_DIGIT);
			// �� ����
			TransparentBlt(_dc, (int)vPos.x - 180
				, (int)vPos.y - 251
				, 16, 16, m_pUIAtlas->GetDC(), ((int)_eScore * 8), 218, 8, 16, RGB(255, 0, 255));
			_eScore = CalculateNumber(pPlyaer->GetBulletCount(), DIGIT::UNIT_DIGIT);
			// �� ����
			TransparentBlt(_dc, (int)vPos.x - 160
				, (int)vPos.y - 251
				, 16, 16, m_pUIAtlas->GetDC(), ((int)_eScore * 8), 218, 8, 16, RGB(255, 0, 255));
		}

		//�÷��̾� Bomb Ȯ���� ��� ��ź�� ������ �ִ� 99���� 100���� ���� �� ����. 
		if (pPlyaer->GetBombCount() > 0)
		{
			_eScore = CalculateNumber(pPlyaer->GetBombCount(), DIGIT::TEN_DIGIT);
			// �� ����
			TransparentBlt(_dc, (int)vPos.x - 90
				, (int)vPos.y - 251
				, 16, 16, m_pUIAtlas->GetDC(), ((int)_eScore * 8), 218, 8, 16, RGB(255, 0, 255));
			_eScore = CalculateNumber(pPlyaer->GetBombCount(), DIGIT::UNIT_DIGIT);
			// �� ����
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



	//�ð����
	// �߾Ӻο� �ð� ǥ�ä���
	if (m_MainTime > 0)
	{
		m_TimeAcc += DT; //1�� �ð� ����
		if (m_TimeAcc >= 1.f) //1�ʸ� ������ 
		{
			--m_MainTime;
			m_TimeAcc = 0.f; //1�ʰ� �Ǿ����� 0���� �ٽ� �ʱ�ȭ ���ش�. 
		}
		_eScore = CalculateNumber(m_MainTime, DIGIT::TEN_DIGIT);
		// �� ����
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



// �Ѿ� ���� ���� �Լ� 
// ���� �Ѿ��� �ڸ��� ����
SCORE CGUI::CalculateNumber(int m_number, DIGIT _digit)
{
	// ó���� �޾� �� ���� �Ƹ� �ִ�ġ 200���� ����
	int share = 0;
	SCORE _eNumber;


	if (DIGIT::HUNDRED_DIGIT == _digit)
	{
		// 100�� �ڸ� ���� ��
		_eNumber = (SCORE)(m_number / 100);
		return _eNumber;
	}
	else if (DIGIT::TEN_DIGIT == _digit)
	{
		// 10�� �ڸ� ���� ��
		_eNumber = (SCORE)((m_number % 100) / 10);
		return _eNumber;
	}
	else if (DIGIT::UNIT_DIGIT == _digit)
	{
		// 1�� �ڸ� ���� ������ ��
		_eNumber = (SCORE)((m_number % 10));
		return _eNumber;
	}
}

