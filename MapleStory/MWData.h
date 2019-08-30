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
	EMAnimType type;	// ��ο� Ÿ��
	std::string path;   // ��� ex) Object\acc1.img
	std::string sprname; // ���� ��Ī ex) woodMarble.artificiality / pv
	std::string name;	// �̸� ���� 2
	int	cnt;			// ���� 0 ��� = woodMarble.artificiality.2.0
}SPRDATA, *LPSPRDATA;

typedef struct Img_Data
{
	std::string filename; // ���� ��� + �̸� ex)  Object\acc1.img\woodMarble.artificiality.2.0.png
	int id;				  // png �տ� �ִ� ���� Sprdata�� cnt�� MAX ����

	Gdiplus::Point imgsize; // x * y == 1 link

	Gdiplus::Point origin; // ��ǥ �̰� ������ ���� ��ǥ�� ����ؼ� �־����
	Gdiplus::Point head; //�浹���ϸ� �Ⱦ�
	Gdiplus::Point leftTop;  //�浹���ϸ� �Ⱦ�
	Gdiplus::Point rightBottom; // �浹���ϸ�

	int delay;			// anim ��� ������
				
	int z;				// z��

	int beginAlpha;				// ���� 0��
	int endAlpha;				// ���� 1��

	std::string link;   // ��ũ �Ⱦ�
}IMG_DATA, *LPIMG_DATA;

struct MobData
{
	int acc; // ����
	bool bodyAttack; // ���� ����
	int category;
	int eva;//ȸ��
	int exp;//����ġ
	bool firstAttack; //���� ����
	int level;
	int maxHp;
	int maxMp;
	int speed; // �÷��̾��� �̵��ӵ��� 100%�϶��� ���ӵ��� �÷��̾�� ������ +, ������ -)
	int PADamge; // ���� ���� ������
	int MADamge; // ���� ���� ������
	int PDDamge; // ���� ��� ������?
	int MDDamge; // ���� ��� ������?
	int PDRate; //���� ��� ������?
	int MDRate; //���� ��� ������?
	int pushed; // �˹� �Ÿ�?
	char elemAttr[256]; //����? ����? 2 �ݰ� 3 ���� / I = ����, F = ��, L = ����, S = �� 
	int fs; // �̲�����
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
