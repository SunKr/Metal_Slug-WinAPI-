#pragma once

class CObject;
class CImage;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,
};

struct tCamEffectInfo
{
	float		fAccTime;	// ���� ���� �ð�
	float		fDuration;	// ����Ʈ �� ����ð�
	CAM_EFFECT	eEffect;	// ī�޶� ȿ�� Ÿ��
};




class CCamera
{
	SINGLE(CCamera);
private:
	Vec2					m_vResolution;	// ȭ�� �ػ�
	Vec2					m_vLook;		// ���� ī�޶� �����ִ� ��ǥ
	Vec2					m_vDiff;		// ȭ�� �ػ� �߽� ��ǥ�� ���� ī�޶� Look ���� ����

	CObject*				m_pTargetObj;

	// veil
	CImage*					m_pVeil;		// ������ �뵵 BitmapImage ����
	float					m_fAlpha;		// ���� ����
	
	list<tCamEffectInfo>	m_CamEffectInfo;
		
	//Plyer ī�޶�  ��ȯ����
	bool					summon;//ĳ���� ī�޶� ��ȯ ����
	float					m_fAccTime;
	float					m_CamSpeed;

public:
	void init(); 
	void tick();	
	void render(HDC _dc);

public:
	//��ȯ ���� ����
	void setSummon(bool _summon)
	{
		summon = _summon;
	}
	//��ȯ���� �˷���
	const bool getSummon()
	{
		return summon;
	}


public:
	Vec2 GetLookAt() { return m_vLook; }
	void SetLookAt(Vec2 _vlook) { m_vLook = _vlook; }
	Vec2 GetRenderPos(Vec2 _vRealPos) { return _vRealPos - m_vDiff; }
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }

	void SetTargetObject(CObject* _pObj) { m_pTargetObj = _pObj; }
	CObject* GetTargetObject() {return m_pTargetObj;}
	void SetCameraEffect(CAM_EFFECT _type, float _fDuration)
	{
		tCamEffectInfo info = {};
		info.eEffect = _type;
		info.fDuration = _fDuration;		
		m_CamEffectInfo.push_back(info);
	}
};

