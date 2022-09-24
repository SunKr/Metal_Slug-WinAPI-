#pragma once


#define SINGLE(type) public:\
						static type* GetInst()\
						{\
							static type mgr;\
							return &mgr;\
						}\
						private:\
							type();\
							~type();

#define DT CTimeMgr::GetInst()->GetDeltaTime()

#define IsPressed(KEY) KEY_STATE::PRESS == CKeyMgr::GetInst()->GetKeyState(KEY)
#define IsTap(KEY) KEY_STATE::TAP == CKeyMgr::GetInst()->GetKeyState(KEY)
#define IsRelease(KEY) KEY_STATE::RELEASE == CKeyMgr::GetInst()->GetKeyState(KEY)

#define SAFE_DELETE(p) if(nullptr != p) delete p; p = nullptr;
#define CLONE(type) virtual type* Clone() override { return new type(*this); }

#define MAX_LAYER 16
#define PI 3.14159265f

#define TILE_SIZE 64

#define MAX_BACKGROUND 10



#define Ground_SET	    CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();\
						CImage* pImage = nullptr;\
						const vector<CObject*>& vecCollider = pCurScene->GetObjects(LAYER_TYPE::BACKGROUNDCOLLIDER);\
						for (int k = 0; k < vecCollider.size(); ++k)\
						{\
						pImage = ((CBackgroundCollider*)vecCollider[k])->GetImage();\
						}\
						if (pImage->GetPixelColor(this->GetPos().x, this->GetPos().y)\
						== tPixel(0, 255, 0, 255))\
						{\
						this->GetRigidBody()->SetGround(true);\
						}\
						else\
						{\
						this->GetRigidBody()->SetGround(false);\
						}\


enum class MOTION_TYPE
{
	NONE,
	STANDING,
	RUNNING,
	JUMPING,
	KNIFE,
	CROUNCHING, //��ũ������
	CROUNCH, //��ũ��
	CROUNCHWALK, //��ũ���� �ȱ�
	CROUNCHSHOOTING, //��ũ���� ��
	CROUNCHKNIFE, //��ũ���� Į��
	SHOOTING,
	SHOOTING_RUNNING,
	UPPER,
	UPPERSHOOTING,
	LOWERSHOOTING,
	LEFTSHOOTING,

	END,
};


enum SCENE_TYPE
{
	TOOL,
	LOGO,
	HOME,//Ȩȭ�� ����
	SELECT, //ĳ���� ����â
	START,
	STAGE_01,
	END,
};

enum class PEN_COLOR
{
	RED,
	GREEN,
	BLUE,
	END,
};

enum class BRUSH_COLOR
{
	HOLLOW, // ���� �귯��
	BLACK,  // ���� �귯��
	GRAY,	// ȸ�� �귯��
	END,
};

enum class COMPONENT_TYPE
{	
	ANIMATOR,	
	RIGIDBODY,	
	COLLIDER,
	AI,
	CBODY,
	END,
};


enum class BODY_TYPE
{
	UPPER, //��ü
	LOWER, //��ü
	END
};

// �÷��̾ ������ �ѱ�� 
enum class ARMOR_TYPE
{
	NORMAL,
	MACHINE,
	END,
};

enum class LAYER_TYPE
{
	DEFAULT,
	MAIN,  //������ Ȩȭ������ ����
	BACKGROUND,
	BACKGROUNDCOLLIDER,
	TILE,
	PLAYER,
	PLAYER1,
	ENEMY,
	NPC,
	PLAYER_PROJECTILE,
	ENEMY_PROJECTILE,
	GRANADE,
	MONSTER,
	ROCK, //��
	FORCE,

	GUI,
	UI = MAX_LAYER -1,
	END = MAX_LAYER,
};

enum class EVENT_TYPE
{
	CREATE_OBJECT, // first : Object Adress, second : Layer Type
	DELETE_OBJECT, // first : Object Adress, 
	SCENE_CHANGE,  // first : Scene Type

	END,
};


//animation ���� ��׶��� Ÿ��
enum class BGTYPE
{
	// ��� �̸� ����
	NONE,
	Map,
	Map1,
	map4_2,
	map4_3,
	END,
};

enum class ANIMATION_TYPE
{
	FULL,
	LOWER,
	UPPER,
	END,
};


enum class SCORE
{
	ZERO,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	END
};


enum class DIGIT
{
	HUNDRED_DIGIT,
	TEN_DIGIT,
	UNIT_DIGIT,
	END,
};


//�� �ൿ ���� 
enum class ENEMYMOTION_TYPE
{
	LDie, //�������� ������
	RDie, //���� ���� ������
	LRun, //�������� �޷� ����
	RRun, //�������� �޷� ����
	LWalk, //���� �ȱ�
	RWalk, //���� �ȱ�
	LThrow, //�������� ������
	RThrow, //�������� ������
	LSurprise,
	RSurprise,
	LKnife,
	RKnife,
	LKNIFEREVERSE,
	RKNIFEREVERSE,
	LJump,
	RJump,
	LIdle,
	RIdle,
	END
};

//������ ǥ��
enum class ENEMY_STATE
{
	NONE = 0,
	IDLE,
	THROW,
	KNIFE,
	COUNTERKNIFE, //Į���� ����
	KNIFEREVERSE,
	WALK,
	RUN,
	JUMP,
	SURPRISE,
	DIE
};


//���� ����
enum class DIRECTION
{
	LEFT,
	RIGHT,
	END,
};