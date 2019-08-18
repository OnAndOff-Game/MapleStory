#pragma once


enum EMRenderType : int{
	eMR_Back,
	eMR_Map,
	eMR_Obj,
	eMR_UI,
	eMR_Cnt,
};

enum EMAnimType : int{

	eMA_Standing,
	eMA_Moving,
	eMA_Jumping,
	eMA_Hit,
	eMA_Die,
	eMA_Attack,
	eMA_Skill,
	eMA_Chase,
	eMA_Cnt,
};

enum EMObjType : int{
	eMO_Obj,
	eMO_Player,
	eMO_Mob,
	eMO_PSkill,
	eMO_MSkill,
	eMO_Item,
	eMO_Cnt,
};

struct BatchElement
{
	Gdiplus::Point Pos;
	int SizeX;
	int SizeY;
	Gdiplus::Image* img;

	int z;
	float alpha;

	bool bFlip;

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

typedef struct SprData
{
	EMAnimType type;
	std::string path;
	std::string sprname;
	std::string name;
	int	cnt;
}SPRDATA, *LPSPRDATA;

typedef struct Img_Data
{
	std::string filename; // 
	int id;

	Gdiplus::Point imgsize; // x * y == 1 link

	Gdiplus::Point origin;
	Gdiplus::Point head;
	Gdiplus::Point lt;
	Gdiplus::Point rb;

	int delay;

	int z;

	int a0;
	int a1;

	std::string link;
}IMG_DATA, *LPIMG_DATA;

struct MobInfo
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
//
//struct skill
//{
//	std::string id; // 1 전사 2 마법사 3 궁수 4 도적
//
//};

struct RoadLine
{
	int layer;
	int group;
	int id;
	Gdiplus::Point line1;
	Gdiplus::Point line2;
	int prv;
	int nxt;
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
