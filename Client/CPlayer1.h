#pragma once
#include "CObject.h"


//총쏘는 방향
enum class SHOOTINGDIR
{
    KEY0,
    KEY45,
    KEY90,
    KEY135,
    KEY180,
    KEY225,
    KEY270,
    KEY315,
};

enum class PROJECTILETYPE
{
    NONE,
    KNIFE, //칼
    PISTOL, //총
    GRENADE, //수류탄

};

enum class UPPERSTATE
{
    //서 있기
    //총 쏘기
    STAND,
    SHOOT,
    JUMP, //상체 점프
    UPPERGUN, //총 위로 들기
    UPPERSHOOTING, //위로 총쏘기
    SHOOTINGDOWN, //점프후 아래총
    SHOOTINGLOWER, //아래로 총쏘는중
    THROWINGBOMB, //폭탄 던지기
};


enum class LOWERSTATE
{
    LSTAND, //하체 서있기
    LRUN,   //하체 달리기
    LJUMP, //하체 점프
    LUNDERJUMP, //아래총을 위한 점프
};

class CImage;
enum class ARMOR_TYPE;

class CPlayer1 :
    public CObject
{

private:
    CImage*         m_pImage;
    CImage*         m_pImageLeft;       //좌측 방향
    float           m_fSpeed;           //움직이는 속도
    float           m_fAccTime;         //축적된 시간  
    ARMOR_TYPE      eArmorType;         //플레이어가 소유한 amor
    int             m_BulletCount;      //플레이어가 소유한 Machine Gun 총알 수(일반총은 무한발사 가능하다)
    int             m_Bomb;             //플레이어가 소유한 Bomb
    MOTION_TYPE     beforeState; //이전 모션
    MOTION_TYPE     pState;  //현재 모션
    MOTION_TYPE     nState;

public:
    bool            m_knife;            // 나이프 사용 가능 여부
    bool            m_Atk;              // 공격 상태
    bool            m_Die;              // 죽었는지
    bool            m_Crounch;          // 앉기 키를 누른 경우 여부 확인
    bool            m_IsJump;           // 점프 상태
    bool            m_Item;             // 아이템 여부
    bool            CheckCollide;       // 충돌 여부 판정
    bool            m_Switch = false;           // 스위치 여부
    bool            m_Pressed;          //눌려져 있느지 여부

public:
    DIRECTION       pDirection; //플레이어의 방향 설정
    DIRECTION       bDirection; //플레이어의 방향 설정

    // 상체 
    UPPERSTATE      bUpper;
    UPPERSTATE      pUpper;
    UPPERSTATE      nUpper;

    // 하체
    LOWERSTATE      bLower;
    LOWERSTATE      pLower;
    LOWERSTATE      nLower;

public:
    //칼 사용
    void Knife(bool _knife) { m_knife = _knife; }
    // 폭탄 사용
    void Grenade();



public:
    

    virtual void tick() override;

   
    
    virtual void render(HDC _dc) override;

    void Move();

    void PlayL(CObject* _object, LOWERSTATE _Lstate);
    void PlayU(CObject* _object, UPPERSTATE _Ustate);

    bool trigerUpper();

    bool trigerLower();


    void UAnimation();

    void LAnimation();

    virtual  void CollisionBeginOverlap(CCollider* _pOhterCollider) override;

    virtual void CollisionEndOverlap(CCollider* _pOhterCollider) override;

    void Shooting(SHOOTINGDIR _dir);


    
public:
    //무기 타입 세팅하는 함수
    void setArmor(ARMOR_TYPE _etype) { eArmorType = _etype; }
    // 소유한 무기 타입 가져오기
    ARMOR_TYPE getArmor() {  return eArmorType;  }
    //총알 개수
    int         GetBulletCount() {  return m_BulletCount; }

    //폭탄 개수
    void        SetBombCount(int _Bomb) { m_Bomb = _Bomb; }
    int         GetBombCount() {  return m_Bomb; }

public:
    CLONE(CPlayer1);


public:
    CPlayer1();
    ~CPlayer1();

    void ImageAnimation();


    friend class CBackgroundCollider;

};

