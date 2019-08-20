#pragma once


enum EMRenderType : int{
	eMR_Back,
	eMR_Map,
	eMR_Obj,
	eMR_UI,
	eMR_Cnt,
};

enum EMAnimType : int{

	eMA_Static,
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
	Gdiplus::Point lt;  //충돌안하면 안씀
	Gdiplus::Point rb; // 충돌안하면

	int delay;			// anim 출력 딜레이
				
	int z;				// z값

	int a0;				// 알파 0값
	int a1;				// 알파 1값

	std::string link;   // 링크 안씀
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
