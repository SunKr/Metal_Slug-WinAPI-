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
	CROUNCHING, //웅크리는중
	CROUNCH, //웅크림
	CROUNCHWALK, //웅크리고 걷기
	CROUNCHSHOOTING, //웅크리고 총
	CROUNCHKNIFE, //웅크리고 칼질
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
	HOME,//홈화면 설정
	SELECT, //캐릭터 설정창
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
	HOLLOW, // 투명 브러쉬
	BLACK,  // 검은 브러쉬
	GRAY,	// 회색 브러쉬
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
	UPPER, //상체
	LOWER, //하체
	END
};

// 플레이어가 보유한 총기류 
enum class ARMOR_TYPE
{
	NORMAL,
	MACHINE,
	END,
};

enum class LAYER_TYPE
{
	DEFAULT,
	MAIN,  //메인을 홈화면으로 설정
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
	ROCK, //돌
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


//animation 돌릴 백그라운드 타입
enum class BGTYPE
{
	// 배경 이름 설정
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


//적 행동 패턴 
enum class ENEMYMOTION_TYPE
{
	LDie, //좌측으로 죽으면
	RDie, //우측 으로 죽으면
	LRun, //좌측으로 달려 갈때
	RRun, //우측으로 달려 갈때
	LWalk, //좌측 걷기
	RWalk, //우측 걷기
	LThrow, //좌측으로 던지기
	RThrow, //우측으로 던지기
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

//적상태 표시
enum class ENEMY_STATE
{
	NONE = 0,
	IDLE,
	THROW,
	KNIFE,
	COUNTERKNIFE, //칼접는 상태
	KNIFEREVERSE,
	WALK,
	RUN,
	JUMP,
	SURPRISE,
	DIE
};


//방향 설정
enum class DIRECTION
{
	LEFT,
	RIGHT,
	END,
};