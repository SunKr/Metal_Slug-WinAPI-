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
    FAR_ATK, //���Ÿ� Ÿ��
    NEAR_ATK, // �ٰŸ� Ÿ��
};

class CEnemy :
    public CObject
{
private:
    CImage*             m_pImage;
    CPlayer1*           m_Plyaer;
    float               m_fAccTime;  // �ð���
    int                 HP;          // ���� HP
    ENEMY_TYPE          _eType;      // �� �ٰŸ� �� Ÿ��
    ENEMYMOTION_TYPE    _eMotion;    // �� �ൿ ��� ����
    bool                IsDead;      //�׾����� ����
    float               walkSpeed;   // �ȴ� �ӵ�
    float               runSpeed;    // �޸��� �ӵ�
    DIRECTION                 _eDirection; // ���� �ൿ ������ ������
    DIRECTION                 m_Block;     // �ٸ� �������� �����̵��� �ϴ� Block
    float               m_Range;     // �̵� ���� ����

    Vec2                m_Location;     //���� ��ġ ����
    float               m_WallLocation = 0.f;

    bool                isDie = false; //�׾����� ����
    bool                IsCollide = false; // Į�� �浹 ����
    bool                m_triger; //�ִϸ��̼� ��ȯ ����


    bool                isSpot = false;


    int                 randNumber; //��������
    Vec2                rootPos;    //�ʱ� ������ ��ġ ��

    bool                enemyCollide = false;


    //�� ���� ǥ�� (����, ����, �̷�)
    ENEMY_STATE enemyState = ENEMY_STATE::IDLE;
    ENEMY_STATE nextEnemyState = ENEMY_STATE::NONE;
    ENEMY_STATE beforeEnemyState = ENEMY_STATE::NONE;


public:
    virtual void tick() override;
    virtual void CollisionBeginOverlap(CCollider* _pOhterCollider);

    bool triger(); //���� Ʈ����
    void PlayAnim(CEnemy* _object, ENEMY_STATE _estate);


public:
    void HPCheck();
    void GroundCheck();
    void Move();
    void Die();
    void Atk();
    void MoveFirePos();
public:
    // ����ź ��ô ���� Ȯ��
    void ScoutRangeCheck();

public:


public:
    Vec2             GetLocation()      { return m_Location; }
    ENEMYMOTION_TYPE GetMotion()        { return _eMotion; } //���� ĳ���Ͱ� ���ϴ��ൿ
    ENEMY_TYPE       GetEnemyType()     { return _eType; } //��, �ٰŸ� ĳ���ͼ���
    DIRECTION        GetDirection()     { return _eDirection; } // �� ����
    bool             IsDeadEnemy()      { return IsDead;  }
    int              GetHP()            { return HP;  }

public:
     CEnemy* Clone() { return new CEnemy(*this); }



public:
    CEnemy();
    CEnemy(const CEnemy& _mon);
    ~CEnemy();
};






