#pragma once


enum EMRenderType : int{
	eMRenderType_BackGround,
	eMRenderType_Map,
	eMRenderType_Object,
	eMRenderType_UI,
	eMRenderType_Cnt,
};

enum EMAnimType : int{

	eMAnimType_Static,
	eMAnimType_Standing,
	eMAnimType_Moving,
	eMAnimType_Prone,
	eMAnimType_Jumping,
	eMAnimType_Ladder,
	eMAnimType_Rope,
	eMAnimType_Hit,
	eMAnimType_Die,
	eMAnimType_Attack,
	eMAnimType_Skill,
	eMAnimType_Chase,
	eMAnimType_Cnt,
};

enum EMObjType : int {
	eMObjType_Map,
	eMObjType_Obj,
	eMObjType_LadderRope,
	eMObjType_Player,
	eMObjType_Mob,
	eMObjType_PlayerSkill,
	eMObjType_MobSkill,
	eMObjType_Item,
	eMObjType_Cnt,
};

static const char* ANIM_TYPE[EMAnimType::eMAnimType_Cnt] = {
	"Static", "stand", "move", "prone", "jump", "ladder",
	"rope", "hit", "die", "attack", "skill", "chase" };

struct BatchElement
{
	Gdiplus::Point Pos;
	Gdiplus::Point Origin;
	int SizeX;
	int SizeY;
	Gdiplus::Image* img;

	int z;
	float alpha;
	float red;

	bool bFlip;

	Gdiplus::CachedBitmap* cachedImg;

	/*
	rotation
	proxyid;
	float u;
	float v;
	*/

};

typedef struct MTransform
{
	MTransform() : Scale(1), Rotation(0)
	{}

	Gdiplus::Point	Translation;
	float			Scale;
	float			Rotation;
}MTRASFORM;

typedef struct SpritesData
{
	EMAnimType type;	// 드로우 타입
	std::string path;   // 경로 ex) Object\acc1.img
	std::string sprname; // 파일 명칭 ex) woodMarble.artificiality / pv
	std::string name;	// 이름 숫자 2
	int	cnt;			// 갯수 0 결과 = woodMarble.artificiality.2.0
}SPRDATA, *LPSPRDATA;

typedef struct Img_Data
{
	std::string filename; // 파일 경로 + 이름 ex)  Object\acc1.img\woodMarble.artificiality.2.0.png
	int id;				  // png 앞에 있는 숫자 Sprdata의 cnt가 MAX 숫자

	Gdiplus::Point imgsize; // x * y == 1 link

	Gdiplus::Point origin; // 좌표 이거 없으면 중점 좌표를 계산해서 넣어야함
	Gdiplus::Point head; //충돌안하면 안씀
	Gdiplus::Point leftTop;  //충돌안하면 안씀
	Gdiplus::Point rightBottom; // 충돌안하면

	int delay;			// anim 출력 딜레이
				
	int z;				// z값

	int beginAlpha;				// 알파 0값
	int endAlpha;				// 알파 1값

	std::string link;   // 링크 안씀
}IMG_DATA, *LPIMG_DATA;

struct MobData
{
	int acc; // 명중
	bool bodyAttack; // 몸통 판정
	int category;
	int eva;//회피
	int exp;//경험치
	bool firstAttack; //선공 유무
	int level;
	int maxHp;
	int maxMp;
	int speed; // 플레이어의 이동속도가 100%일때의 상대속도로 플레이어보다 빠르면 +, 느리면 -)
	int PADamge; // 물리 공격 데미지
	int MADamge; // 마법 공격 데미지
	int PDDamge; // 물리 방어 데미지?
	int MDDamge; // 마법 방어 데미지?
	int PDRate; //물리 방어 딜레이?
	int MDRate; //마법 방어 딜레이?
	int pushed; // 넉백 거리?
	char elemAttr[256]; //상태? 약점? 2 반감 3 약점 / I = 얼음, F = 불, L = 전기, S = 독 
	int fs; // 미끄러짐
};

struct RoadLine
{
	int layer;
	int group;
	int id;
	Gdiplus::Point startLine;
	Gdiplus::Point endLine;
	int prev;
	int next;
};

struct MRoadGroup
{
	int layer;
	int num;

	std::vector<int> line;

	Gdiplus::Point colpt1;
	Gdiplus::Point colpt2;

	int Begin;
	int End;
};

struct akt
{
	int atkafter;
	Gdiplus::Rect range;
	   
};

struct effect
{
};
