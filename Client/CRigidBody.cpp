#include "pch.h"
#include "CRigidBody.h"

#include "CTimeMgr.h"

#include "CObject.h"

CRigidBody::CRigidBody()
	: CComponent(COMPONENT_TYPE::RIGIDBODY)
	, m_fMass(1.f) //질량
	, m_fFriction(300.f) //마찰 계수
	, m_fMaxSpeed(200.f) //중력이 아닌 최대 속력 제한
	, m_fMaxGravitySpeed(200.f) //중력에 의해 발생하는 최대 속력 제한
	, m_bUseGravity(false) //중력 사용 유무
	, m_bGround(false)	 //땅 확인 유무
	, m_elasticity(0.f)
	, m_IsElastic(false)  //탄성 유무
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::tick()
{
	// F = M x A
	m_vAccel = m_vForce / m_fMass;

	// 속도에 가속도를 더한다.
	m_vVelocity += m_vAccel * DT;

	// 중력 가속도 적용
	if (!m_bGround) 
	{
		m_vVelocity += m_vGravityAccel * DT;
	}
	else if ((m_bGround && m_IsElastic) || (!m_bGround && m_IsElastic)) //땅 이면서 탄성이 있다면
	{
		//땅에부딛히는 순간 (아래 방향은 없어지고)
		Vec2 vGravity = m_vGravityAccel;
		vGravity.Normalize();
		m_vVelocity = m_vVelocity - vGravity * m_vVelocity.Dot(vGravity);
		//반발계수 만큼 다시 위로 쏠수 있도록 설정해준다.
		if (m_elasticity <= 0.f)
		{
			m_elasticity = 0.f;
			m_IsElastic = false;
		}
		//탄성 계수 * 특정힘만큼 다시 튀어 오르게 한다.
		m_vVelocity = m_vVelocity + Vec2(50.f, -200.f) * m_elasticity;
		// 위로 탄성계수 만큼 속도가 발생되게 설정한다.

	}
	else //땅에 부딛히는 순간(아래 방향은 없어진다)
	{
		Vec2 vGravity = m_vGravityAccel;
		vGravity.Normalize();
		m_vVelocity -= vGravity * m_vVelocity.Dot(vGravity);
	}

	// 속도 제한 조건
	Vec2 vGravity = m_vGravityAccel;
	vGravity.Normalize();
	vGravity = vGravity * m_vVelocity.Dot(vGravity); // 속도를 중력방향으로 분해
	
	Vec2 vSideVelocity = m_vVelocity - vGravity;

	if (m_fMaxGravitySpeed < vGravity.Length())
	{
		vGravity.Normalize();
		vGravity *= m_fMaxGravitySpeed;
	}

	if (m_fMaxSpeed < vSideVelocity.Length())
	{
		vSideVelocity.Normalize();
		vSideVelocity *= m_fMaxSpeed;
	}

	m_vVelocity = vGravity + vSideVelocity;
	
	// 마찰력 조건(적용된 힘이 없고, 속도가 0 이 아니고, 땅 위에 있을 때)
	if (!m_vVelocity.IsZero() && m_bGround)
	{
		// 속도의 반대방향으로 마찰력을 적용
		Vec2 vFriction = -m_vVelocity;
		vFriction = vFriction.Normalize() * m_fFriction * DT * m_fMass;

		// 마찰력으로 인한 속도 감소량이 현재 속도보다 더 큰 경우
		if (m_vVelocity.Length() < vFriction.Length())
		{
			// 속도를 0 로 만든다.
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			// 속도에서 마찰력으로 인한 반대방향으로 속도를 차감한다.
			m_vVelocity += vFriction;
		}		
	}

	// 속도에 맞게 물체를 이동시킨다.
	// 현재 rigidbody 가진 물체에 특정 속도 만큼 움직여 준다.
	Vec2 vPos = GetOwner()->GetPos() + m_vVelocity * DT;
	GetOwner()->SetPos(vPos);
	
	//계속 힘이 추가 되지 않게 하기위해 마지막에 0으로 초기화 해준다.
	m_vForce = Vec2(0.f, 0.f);
}