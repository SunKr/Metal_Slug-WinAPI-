#pragma once
#include "CObject.h"


class CImage;
class CPlayer1;


enum class BLOCK_DIR
{
    LEFT,
    RIGHT,
};

enum class ENEMY_TYPE
{
    FAR_ATK, //원거리 타입
    NEAR_ATK, // 근거리 타입
};

class CEnemy :
    public CObject
{
private:
    CImage*             m_pImage;
    CPlayer1*           m_Plyaer;
    float               m_fAccTime;  // 시간초
    int                 HP;          // 현재 HP
    ENEMY_TYPE          _eType;      // 원 근거리 적 타입
    ENEMYMOTION_TYPE    _eMotion;    // 적 행동 모션 상태
    bool                IsDead;      //죽었는지 여부
    float               walkSpeed;   // 걷는 속도
    float               runSpeed;    // 달리는 속도
    DIRECTION                 _eDirection; // 적의 행동 방향을 설정ㄴ
    DIRECTION                 m_Block;     // 다른 방향으로 움직이도록 하는 Block
    float               m_Range;     // 이동 범위 설정

    Vec2                m_Location;     //현재 위치 설정
    float               m_WallLocation = 0.f;

    bool                isDie = false; //죽었느지 여부
    bool                IsCollide = false; // 칼과 충돌 여부
    bool                m_triger; //애니매이션 변환 여부


    bool                isSpot = false;


    int                 randNumber; //랜덤숫자
    Vec2                rootPos;    //초기 설정된 위치 값

    bool                enemyCollide = false;


    //적 상태 표시 (과거, 현재, 미래)
    ENEMY_STATE enemyState = ENEMY_STATE::IDLE;
    ENEMY_STATE nextEnemyState = ENEMY_STATE::NONE;
    ENEMY_STATE beforeEnemyState = ENEMY_STATE::NONE;


public:
    virtual void tick() override;
    virtual void CollisionBeginOverlap(CCollider* _pOhterCollider);

    bool triger(); //상태 트리거
    void PlayAnim(CEnemy* _object, ENEMY_STATE _estate);


public:
    void HPCheck();
    void GroundCheck();
    void Move();
    void Die();
    void Atk();
    void MoveFirePos();
public:
    // 수류탄 투척 범위 확인
    void ScoutRangeCheck();

public:


public:
    Vec2             GetLocation()      { return m_Location; }
    ENEMYMOTION_TYPE GetMotion()        { return _eMotion; } //현재 캐릭터가 취하는행동
    ENEMY_TYPE       GetEnemyType()     { return _eType; } //원, 근거리 캐릭터설정
    DIRECTION        GetDirection()     { return _eDirection; } // 적 방향
    bool             IsDeadEnemy()      { return IsDead;  }
    int              GetHP()            { return HP;  }

public:
     CEnemy* Clone() { return new CEnemy(*this); }



public:
    CEnemy();
    CEnemy(const CEnemy& _mon);
    ~CEnemy();
};






