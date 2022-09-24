#pragma once
#include "CObject.h"


//�ѽ�� ����
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
    KNIFE, //Į
    PISTOL, //��
    GRENADE, //����ź

};

enum class UPPERSTATE
{
    //�� �ֱ�
    //�� ���
    STAND,
    SHOOT,
    JUMP, //��ü ����
    UPPERGUN, //�� ���� ���
    UPPERSHOOTING, //���� �ѽ��
    SHOOTINGDOWN, //������ �Ʒ���
    SHOOTINGLOWER, //�Ʒ��� �ѽ����
    THROWINGBOMB, //��ź ������
};


enum class LOWERSTATE
{
    LSTAND, //��ü ���ֱ�
    LRUN,   //��ü �޸���
    LJUMP, //��ü ����
    LUNDERJUMP, //�Ʒ����� ���� ����
};

class CImage;
enum class ARMOR_TYPE;

class CPlayer1 :
    public CObject
{

private:
    CImage*         m_pImage;
    CImage*         m_pImageLeft;       //���� ����
    float           m_fSpeed;           //�����̴� �ӵ�
    float           m_fAccTime;         //������ �ð�  
    ARMOR_TYPE      eArmorType;         //�÷��̾ ������ amor
    int             m_BulletCount;      //�÷��̾ ������ Machine Gun �Ѿ� ��(�Ϲ����� ���ѹ߻� �����ϴ�)
    int             m_Bomb;             //�÷��̾ ������ Bomb
    MOTION_TYPE     beforeState; //���� ���
    MOTION_TYPE     pState;  //���� ���
    MOTION_TYPE     nState;

public:
    bool            m_knife;            // ������ ��� ���� ����
    bool            m_Atk;              // ���� ����
    bool            m_Die;              // �׾�����
    bool            m_Crounch;          // �ɱ� Ű�� ���� ��� ���� Ȯ��
    bool            m_IsJump;           // ���� ����
    bool            m_Item;             // ������ ����
    bool            CheckCollide;       // �浹 ���� ����
    bool            m_Switch = false;           // ����ġ ����
    bool            m_Pressed;          //������ �ִ��� ����

public:
    DIRECTION       pDirection; //�÷��̾��� ���� ����
    DIRECTION       bDirection; //�÷��̾��� ���� ����

    // ��ü 
    UPPERSTATE      bUpper;
    UPPERSTATE      pUpper;
    UPPERSTATE      nUpper;

    // ��ü
    LOWERSTATE      bLower;
    LOWERSTATE      pLower;
    LOWERSTATE      nLower;

public:
    //Į ���
    void Knife(bool _knife) { m_knife = _knife; }
    // ��ź ���
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
    //���� Ÿ�� �����ϴ� �Լ�
    void setArmor(ARMOR_TYPE _etype) { eArmorType = _etype; }
    // ������ ���� Ÿ�� ��������
    ARMOR_TYPE getArmor() {  return eArmorType;  }
    //�Ѿ� ����
    int         GetBulletCount() {  return m_BulletCount; }

    //��ź ����
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

